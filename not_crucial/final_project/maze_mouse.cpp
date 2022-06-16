#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~FILE~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
FILE* file(){
    FILE* inf = fopen("D:/Code/final_project/input.txt","r");
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
    struct _Connect* next;
}_Connect;
typedef struct _Stack{
    _Vertex* node;
    _Stack* next;
}_Stack;
typedef struct _CurrLast{
    _Connect* curr;
    _Vertex* last;
}_CurrLast;
typedef struct _Vehicle{
    _Vertex* driver;        //the driver's vertex;
    int face;       //determine the direction;
}_Vehicle;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Global Variables~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vertex* vertex[20][20];    //the map's vertex which input;
int X_width, Y_width;       //X,Y width
_Stack* top = NULL;       //the top of stack;
int Fuel_consumption = 0;       //To compute the fuel consumption;

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Functions~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
_Vertex* Adjacency_List();      //construct adjacency list
void make_connect(int i,int j);     //make junction
void make_connect_loop();     //loop to make junction
void show();        //print the graph
void run(_Vertex* start);       //run from the start;
void push(_Connect* curr);      //push into stack;
void Ver_push(_Vertex* curr);
_CurrLast pop(_Vertex* last);
void PrintStack();
void forward(_Vehicle*);
void backward(_Vehicle*);
void turnright(_Vehicle*);
void turnleft(_Vehicle*);

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~Function wrappers~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
void drive(int t,_Vehicle* car) {  
    void (*drive[])(_Vehicle*) = {
        forward,
        backward,
        turnright,
        turnleft
    };
    t %= 4;
    (*drive[t])(car);
    return;
}

//~ ~ ~ ~ ~ ~ ~ ~ ~ ~main~ ~ ~ ~ ~ ~ ~ ~ ~ ~//
int main(){
    _Vertex* start = Adjacency_List();
    make_connect_loop();
    show();
    run(start);
    printf("\nFuel_consumption: %d \n",Fuel_consumption);
    PrintStack();
    return 0;
}

_Vertex* Adjacency_List(){
    FILE* inf = file();
    int i = 0;
    _Vertex* start;
    while( !feof( inf)){
        int j = 0;
        X_width = 0;
        char _n;
        do{
            _Vertex* new_vertex = (_Vertex*) malloc( sizeof( _Vertex));
            vertex[i][j] = new_vertex;
            new_vertex->x = j;
            new_vertex->y = i;
            new_vertex->visited = false;
            fscanf(inf,"%c",&(new_vertex->value));
            if( new_vertex->value == '2')   start = new_vertex;
            new_vertex->connect = NULL;
            j++, X_width++;
        } while( !fscanf(inf,"%[\n]",&_n) );
        i++, Y_width++;
    }
    fclose(inf);
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
    return start;
}

void make_connect(int i,int j){
    int x_add[4] = {1,0,-1,0}, y_add[4] = {0,1,0,-1};
    for( int k = 0; k < 4; k++){
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
                vertex[i][j]->connect = New;
        }
    }
}

void make_connect_loop(){
    for(int i = 0; i < Y_width; i++)
        for(int j = 0; j < X_width; j++)
            make_connect(i,j);
}

void show(){
    system("CLS");
    for( int i = 0; i < Y_width; i++){
        for( int j = 0; j < X_width; j++){
            if(vertex[i][j]->value == '0')
                printf("X");
            if(vertex[i][j]->value == '1')
                printf("-");
            if(vertex[i][j]->value == '2')
                printf("o");
        }
        printf("\n");
    }
    Sleep(50);
}

void run(_Vertex* start){
    int gotcha = 0;
    _Connect* curr = start->connect;
    _Vertex* last = start;
    start->visited = true;
    Ver_push(start);
    while( !gotcha){
        if( curr){
            if( curr->self->visited == false)
                push( curr);
            else if( curr && curr->self->x == 8 && curr->self->y == 8){
                gotcha = 1;
                break;
            }
            curr = curr->next;
        }else{
            _CurrLast CL = pop(last);
            curr = CL.curr;
            last = CL.last;
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

// _Connect* pop(){
//     if( !top)   return NULL;
//     bool self_push_or_not = false;
//     if(top->node->visited == false)        self_push_or_not = true;
//     top->node->value = '2';
//     top->node->visited = true;
//     last->value = '1';
//     last = top->node;
//     _Vertex* self_ = top->node;
//     _Stack* to_free;
//     to_free = top;
//     top = top->next;
//     free(to_free);
//     if(self_push_or_not)        self_push(self_);
//     _Connect* next_curr = top->node->connect;
//     return next_curr;
// }

_CurrLast pop(_Vertex* last){
    if( !top)   return {NULL,NULL};
    top->node->value = '2';
    bool visited_or_not = false;
    if(top->node->visited == true)
        visited_or_not = true;
    top->node->visited = true;
    last->value = '1';
    bool same_or_not = true;
    if(last != top->node){
        last = top->node;
        same_or_not = false;
    }
    _Vertex* self_ = top->node;
    _Connect* next_curr = top->node->connect;
    if(visited_or_not){     //if the pop-ed vertex hadn't been visited, won't truely pop it;
        _Stack* To_free;
        To_free = top;
        top = top->next;
        free(To_free);
    }
    if(!same_or_not){       //if the pop-ed vertex is curr itself, won't show it;
        show();
    }
    _CurrLast CurrLast = {next_curr,last};
    Fuel_consumption ++;
    return CurrLast;
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

void forward(_Vehicle*){
    return;
}

void backward(_Vehicle*){
    return;
}

void turnright(_Vehicle*){
    return;
}

void turnleft(_Vehicle*){
    return;
}

