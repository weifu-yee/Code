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

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function assignments~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vehicle* Adjacency_List();      //construct adjacency list
void make_connect(int i,int j);     //make junction
void make_connect_loop();     //loop to make junction
int axis_addition(int axis, int initial, int face);
void show();        //print the graph
void run(_Vehicle* start);       //run from the start;
void push(_Connect* curr);      //push into stack;
void Ver_push(_Vertex* curr);
void pop(_Connect** curr_ptr,_Vertex** last_ptr);
void PrintStack();
bool forward(_Vehicle*);
bool backward(_Vehicle*);
bool turnright(_Vehicle*);
bool turnleft(_Vehicle*);
bool check_drive(bool bo,int* direction,_Vehicle** curr,int* new_x,int* new_y,int t1,int t2);
void Verify_drive(int t,int X,int Y,int face);

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function wrappers~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
bool drive(int t,_Vehicle* car){ 
    bool T_or_F; 
    bool (*drive[])(_Vehicle*) = {
        forward,
        backward,
        turnright,
        turnleft
    };
    t %= 4;
    T_or_F = (*drive[t])(car);
    return T_or_F;
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
    Verify_drive(3,13,5,0);
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
        int new_i = i + y_add[k], new_j = j + x_add[k];
        if(vertex[i][j]->value == '0')    continue;
        if(new_i<0 || new_i>=Y_width || new_j<0 || new_j>=X_width)    continue;
        switch( vertex[new_i][new_j]->value){
            case '0':     break;
            case '2':   ;
            case '1':   ;
                _Connect* New = (_Connect*) malloc( sizeof( _Connect));
                New->next = vertex[i][j]->connect;
                New->self = vertex[new_i][new_j];
                New->face = k;
                vertex[i][j]->connect = New;
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
bool forward(_Vehicle* curr){
    int direction = (curr->face) % 4;
    int new_x = curr->driver->x;
    int new_y = curr->driver->y;
    if( !check_drive(false,&direction,&curr,&new_x,&new_y,0,0) )       return false;
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,1,0) )       return false;
    return true;
}
bool backward(_Vehicle* curr){
    int direction = ( (curr->face) + 2) % 4;
    int new_x = axis_addition(0,curr->driver->x,direction);
    int new_y = axis_addition(1,curr->driver->y,direction);
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,2,2) )       return false;
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,1,2) )       return false;
    return true;
}
bool turnright(_Vehicle* curr){
    int direction = ( (curr->face) + 1) % 4;
    int new_x = axis_addition(0,curr->driver->x,direction);
    int new_y = axis_addition(1,curr->driver->y,direction);
    if( !check_drive(false,&direction,&curr,&new_x,&new_y,1,1) )       return false;
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,2,1) )       return false;
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,2,1) )       return false;
    return true;
}
bool turnleft(_Vehicle* curr){
    int direction = ( (curr->face) + 3) % 4;
    int new_x = curr->driver->x;
    int new_y = curr->driver->y;
    if( !check_drive(false,&direction,&curr,&new_x,&new_y,2,3) )       return false;
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,2,3) )       return false;
    if( !check_drive(true,&direction,&curr,&new_x,&new_y,2,3) )       return false;
    return true;
}
bool check_drive(bool bo,int* direction,_Vehicle** curr,int* new_x,int* new_y,int t1,int t2){
    *direction = ( ( (*curr)->face) + t1 ) % 4;
    if( bo){
        *new_x = axis_addition(0,*new_x,*direction);
        *new_y = axis_addition(1,*new_y,*direction);
    }
    _Connect* temp = vertex[*new_y][*new_x]->connect;
    int dir2 = ( ( (*curr)->face) + t2 ) % 4;
    while( temp && temp->face < dir2){
        temp = temp->next;
    }
    if( !temp || temp->face > dir2)      return false;
    return true;
}
void Verify_drive(int t,int X,int Y,int face){
    _Vehicle car = {vertex[Y][X],face};
    if( drive(t,&car)){
        printf("Yes");
    }else{
        printf("No");
    }
    return;
}
