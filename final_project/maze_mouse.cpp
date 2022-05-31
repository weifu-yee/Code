#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

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

_Vertex* vertex[20][20];
int X_width, Y_width;       //X,Y width
_Stack* top = NULL;       //the top of stack;
_Vertex* last;

_Vertex* Adjacency_List();      //construct adjacency list
void make_connect(int i,int j);     //make junction
void show();        //print the graph
void run(_Vertex* start);
void push(_Connect* curr);
_Connect* pop();

int main(){
    _Vertex* start = Adjacency_List();
    for(int i = 0; i < Y_width; i++)
        for(int j = 0; j < X_width; j++)
            make_connect(i,j);
    show();
    run(start);
    return 0;
}

_Vertex* Adjacency_List(){
    FILE* inf = fopen("D:/Code/final_project/input.txt","r");
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

void show(){
    system("CLS");
    for( int i = 0; i < Y_width; i++){
        for( int j = 0; j < X_width; j++){
            if(vertex[i][j]->value == '0')
                printf("X");
            if(vertex[i][j]->value == '1')
                printf(" ");
            if(vertex[i][j]->value == '2')
                printf("o");
        }
        printf("\n");
    }
    Sleep(100);
}

void run(_Vertex* start){
    int gotcha = 0;
    _Connect* curr = start->connect;
    last = start;
    start->visited = true;
    //push(curr);
    while( !gotcha){
        if( curr){
            if( curr->self->visited == false)
                push( curr);
            else if( curr && curr->self->x == 8 && curr->self->y == 8)     gotcha = 1;
            else       curr = curr->next;
        }else{
            curr = pop();
            show();
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
    curr->self->visited = true;
}

_Connect* pop(){
    if( !top)   return NULL;
    top->node->value = '2';
    top->node->visited = true;
    last->value = '1';
    last = top->node;
    _Connect* curr = top->node->connect;
    _Stack* temp;
    temp = top;
    top = top->next;
    free(temp);
    return curr;
}