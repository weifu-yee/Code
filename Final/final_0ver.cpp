#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~FILE~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
FILE* file(){
    FILE* inf = fopen("D:/Code/Final/input1.txt","r");
    return inf;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Structures~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
typedef struct _Vertex{
    char value;
    int x;
    int y;
    bool visited;
    struct _Connect* connect;
}_Vertex;
typedef struct _Connect{
    struct _Vertex* self;
    int face;       //describe this vertex is what direction of the vertex which belong;
    struct _Connect* next;
}_Connect;
typedef struct _Stack{
    _Vertex* node;
    _Stack* next;
}_Stack;
typedef struct _Vehicle{
    _Vertex* driver;        //the driver's vertex;
    int face;       //determine the direction;
}_Vehicle;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Global Variables~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vertex* vertex[20][20];    //the map's vertex which input;
int X_width, Y_width;       //X,Y width
_Stack* top = NULL;       //the top of stack;
int Fuel_consumption = 0;       //To compute the fuel consumption;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function declaration~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vehicle* Adjacency_List();      //construct adjacency list
void make_connect(int i,int j);     //make junction
void make_connect_loop();     //loop to make junction
int axis_addition(int axis, int initial, int face);
void show();        //print the graph
void update_car(bool curr_last,_Vehicle* car);
void run(_Vehicle* start);       //run from the start;
void push(_Connect* curr);      //push into stack;
void Ver_push(_Vertex* curr);
void pop(_Connect** curr_ptr,_Vertex** last_ptr);
void PrintStack();
bool forward(int* car_face,int* new_x,int* new_y);
bool backward(int* car_face,int* new_x,int* new_y);
bool turnright(int* car_face,int* new_x,int* new_y);
bool turnleft(int* car_face,int* new_x,int* new_y);
bool check_drive(bool offset_or_not,int car_face,int* new_x,int* new_y,int dir,int ofs);
void car_offset(int* new_x,int* new_y,int car_face,int ofs);
void Verify_drive(int t,int X,int Y,int face);

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function wrappers~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
bool drive(int t,_Vehicle* car){
    bool (*drive[])(int* car_face,int* new_x,int* new_y) = {
        forward,
        backward,
        turnright,
        turnleft
    };
    int car_face = car->face;
    int new_x = car->driver->x;
    int new_y = car->driver->y;
    if( !(*drive[t])(&car_face,&new_x,&new_y))       return false;  //if can't drive;
    update_car(false,car);          //if can drive;
    car->driver = vertex[new_y][new_x];
    car->face = car_face;
    update_car(true,car);
    return true;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~main~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
int main1(){
    _Vehicle* start = Adjacency_List();
    //printf("driver:(%d,%d)\tface to:%d",start->driver->x,start->driver->y,start->face);
    make_connect_loop();
    show();
    run(start);
    printf("\nFuel_consumption: %d \n",Fuel_consumption);
    PrintStack();
    return 0;
}

int main(){
    _Vehicle* start = Adjacency_List();
    make_connect_loop();
    Verify_drive(0,1,10,0);
    show();
    system("Pause");
    update_car(true,start);
    show();system("Pause");
    update_car(false,start);
    show();
    return 0;
}

_Vehicle* Adjacency_List(){
    FILE* inf = file();
    int i = 0;
    _Vehicle* start = (_Vehicle*) malloc( sizeof( _Vehicle));
    char _n;        //To recieve '\n' and do nothing;
    int two_or_three = 3;
    while( !feof( inf)){
        int j = 0;
        X_width = 0;
        do{
            _Vertex* new_vertex = (_Vertex*) malloc( sizeof( _Vertex));
            vertex[i][j] = new_vertex;
            new_vertex->x = j;
            new_vertex->y = i;
            new_vertex->visited = false;
            fscanf(inf,"%c",&(new_vertex->value));
            if( two_or_three && new_vertex->value == '2'){
                if( two_or_three != 2){
                    start->driver = new_vertex;
                    start->face = 1;        //defaut of lay vehicle face to right;
                }
                two_or_three --;
            }else if( two_or_three == 1){
                start->face = 0;
                two_or_three = 0;       //defaut of stand vehicle face to up;
            }
            new_vertex->connect = NULL;
            j++, X_width++;
        } while( !fscanf(inf,"%[\n]",&_n) );
        i++, Y_width++;
    }
    fclose(inf);
    return start;
    // printf("\nX:%d \tY:%d\n",X_width,Y_width);
    // for(int i = 0; i < Y_width; i++){
    //     for(int j = 0; j < X_width; j++){
    //         _Connect* curr = vertex[i][j]->connect;
    //         printf("(%d,%d)",vertex[i][j]->x,vertex[i][j]->y);
    //         printf("%c",vertex[i][j]->value);
    //         while(curr){
    //             printf("->(%d,%d)",curr->self->x,curr->self->y);
    //             curr = curr->next;
    //         }
    //     }
    //     printf("\n");
    // }
}
void make_connect(int i,int j){
    int x_add[4] = {0,1,0,-1}, y_add[4] = {-1,0,1,0};
    for( int k = 3; k >= 0; k--){
        if(vertex[i][j]->value == '0')    continue;
        int new_i = axis_addition(1, i, k);
        int new_j = axis_addition(0, j, k);
        if(new_i<0 || new_i>=Y_width || new_j<0 || new_j>=X_width)    continue;
        switch( vertex[new_i][new_j]->value){
            case '0':     break;
            case '2':   ;
            case '1':   ;
                _Connect* new_connect = (_Connect*) malloc( sizeof( _Connect));
                new_connect->next = vertex[i][j]->connect;
                new_connect->self = vertex[new_i][new_j];
                new_connect->face = k;
                vertex[i][j]->connect = new_connect;
        }
    }
}
void make_connect_loop(){
    for(int i = 0; i < Y_width; i++)
        for(int j = 0; j < X_width; j++)
            make_connect(i,j);
}
int axis_addition(int axis, int initial, int face){
    int axis_add[2][4] = {0,1,0,-1,  -1,0,1,0};
    return (initial + axis_add[axis][face]);
}
void show(){
    system("CLS");
    for( int i = 0; i < Y_width; i++){
        for( int j = 0; j < X_width; j++){
            if(vertex[i][j]->value == '0')
                printf("X");
            else if(vertex[i][j]->value == '1')
                printf("-");
            else if(vertex[i][j]->value == '2')
                printf("o");
            else if(vertex[i][j]->value == '3')
                printf("$");
        }
        printf("\n");
    }
    Sleep(50);
}
void update_car(bool curr_last,_Vehicle* car){
    int i = car->driver->y;
    int j = car->driver->x;
    int k = car->face;
    if( curr_last){         //true = curr;
        vertex[i][j]->value = '3';
        for(int l = 0;l < 2;l ++){
            car_offset(&j,&i,k,2);
            vertex[i][j]->value = '2';
        }
        car_offset(&j,&i,k,1);
        vertex[i][j]->value = '2';
        for(int l = 0;l < 2;l ++){
            car_offset(&j,&i,k,0);
            vertex[i][j]->value = '2';
        }
    }else{          //false = last;
        vertex[i][j]->value = '1';
        for(int l = 0;l < 2;l ++){
            car_offset(&j,&i,k,2);
            vertex[i][j]->value = '1';
        }
        car_offset(&j,&i,k,1);
        vertex[i][j]->value = '1';
        for(int l = 0;l < 2;l ++){
            car_offset(&j,&i,k,0);
            vertex[i][j]->value = '1';
        }
    }
    return;
}
void run(_Vehicle* start){
    int gotcha = 0;
    _Connect* curr = start->driver->connect;
    _Vertex* last = start->driver;
    start->driver->visited = true;
    Ver_push(start->driver);
    int t = 0;
    while( !gotcha){
        if( drive(t,start)){
            if( curr->self->visited == false)
                push( curr);
            else if( curr && curr->self->x == 8 && curr->self->y == 8){
                gotcha = 1;
                break;
            }
            curr = curr->next;
        }else{
            pop( &curr, &last);
            if( !curr)      gotcha = -1;
        }
    }
    printf("\ngotcha:%d\n",gotcha);
}
void push(_Connect* curr){
    _Stack* new_stack = (_Stack*) malloc( sizeof( _Stack));
    new_stack->next = top;
    top = new_stack;
    new_stack->node = curr->self;
    Fuel_consumption --;
}
void Ver_push(_Vertex* node){
    _Stack* new_stack = (_Stack*) malloc( sizeof( _Stack));
    new_stack->next = top;
    top = new_stack;
    new_stack->node = node;
    Fuel_consumption --;
}
void pop(_Connect** curr_ptr,_Vertex** last_ptr){
    if( !top){
        *curr_ptr = NULL;
        return;
    }
    top->node->value = '2';
    bool visited_or_not = false;
    if(top->node->visited == true)
        visited_or_not = true;
    top->node->visited = true;
    (*last_ptr)->value = '1';
    bool same_or_not = true;
    if(*last_ptr != top->node){
        *last_ptr = top->node;
        same_or_not = false;
    }
    *curr_ptr = top->node->connect;
    if(visited_or_not){     //if the pop-ed vertex hadn't been visited, won't truely pop it;
        _Stack* To_free;
        To_free = top;
        top = top->next;
        free(To_free);
    }
    if(!same_or_not){       //if the pop-ed vertex is curr itself, won't show it;
        show();
    }
    Fuel_consumption ++;
    return;
}
void PrintStack(){
    int numOFstack = 0;
        if(!top){
            printf("No~");
            return;
        }
        printf("\nSTACK:(%d,%d)\n",top->node->x,top->node->y);
        top = top->next;
        while(top){
            for(int i = 0; i < numOFstack; i ++)    printf(" ");
            printf("->(%d,%d)\n",top->node->x,top->node->y);
            top = top->next;
            numOFstack ++;
        }
        for(int i = 0; i < numOFstack; i ++)    printf(" ");
        printf("->NULL\n");
        return;
}
bool forward(int* car_face,int* new_x,int* new_y){
    if( !check_drive(false,*car_face,new_x,new_y,0,0) )       return false;
    int new_x_prime = *new_x;
    int new_y_prime = *new_y;
    if( !check_drive(true,*car_face,&new_x_prime,&new_y_prime,0,1) )       return false;
    car_offset(new_x,new_y,*car_face,0);
    return true;
}
bool backward(int* car_face,int* new_x,int* new_y){
    check_drive(true,*car_face,new_x,new_y,2,2);
    if( !check_drive(true,*car_face,new_x,new_y,2,2) )       return false;
    if( !check_drive(true,*car_face,new_x,new_y,2,1) )       return false;
    return true;
}
bool turnright(int* car_face,int* new_x,int* new_y){
    if( !check_drive(true,*car_face,new_x,new_y,1,1) )       return false;
    if( !check_drive(true,*car_face,new_x,new_y,1,2) )       return false;
    if( !check_drive(true,*car_face,new_x,new_y,1,2) )       return false;
    return true;
}
bool turnleft(int* car_face,int* new_x,int* new_y){
    if( !check_drive(false,*car_face,new_x,new_y,3,0) )       return false;
    if( !check_drive(true,*car_face,new_x,new_y,3,2) )       return false;
    if( !check_drive(true,*car_face,new_x,new_y,3,2) )       return false;
    return true;
}
bool check_drive(bool offset_or_not,int car_face,int* new_x,int* new_y,int dir,int ofs){
    int direction = ( car_face + dir ) % 4;
    if( offset_or_not)     car_offset(new_x,new_y,car_face,ofs);
    _Connect* temp = vertex[*new_y][*new_x]->connect;
    while( temp && temp->face < direction){
        temp = temp->next;
    }
    if( !temp || temp->face > direction)      return false;
    return true;
}
void car_offset(int* new_x,int* new_y,int car_face,int ofs){
    int offset = ( car_face + ofs ) % 4;
    *new_x = axis_addition(0,*new_x,offset);
    *new_y = axis_addition(1,*new_y,offset);
}
void Verify_drive(int t,int X,int Y,int face){
    _Vehicle car = {vertex[Y][X],face};
    printf("drive[%d]--(%d,%d) face to: %d \t~",t,X,Y,face);
    if( drive(t,&car)){
        printf("Yes");
    }else{
        printf("No");
    }
    return;
}
