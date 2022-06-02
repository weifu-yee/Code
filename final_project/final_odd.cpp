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
_Vertex* vertex[20][20];
int X_width, Y_width;
void Adjacency_List();
void make_connect(int i,int j);
void show();

int main(){
    Adjacency_List();
    show();
    return 0;
}

void Adjacency_List(){
    FILE* inf = fopen("D:/Code/final_project/input1.txt","r");
    int i = 0;
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
            new_vertex->connect = NULL;
            j++, X_width++;
        } while( !fscanf(inf,"%[\n]",&_n) );
        i++, Y_width++;
    }
    for(int i = 0; i < Y_width; i++){
        for(int j = 0; j < X_width; j++){
            make_connect(i,j);
        }
    }
    fclose(inf);
    // printf("\nX:%d \tY:%d\n",X_width,Y_width);
    // for(int i = 0; i < Y_width; i++){
    //     for(int j = 0; j < X_width; j++){
    //         _Connect* curr = vertex[i][j]->connect;
    //         printf("(%d,%d):",vertex[i][j]->x,vertex[i][j]->y);
    //         printf("%c ",vertex[i][j]->value);
    //         while(curr){
    //             printf("->(%d,%d)",curr->self->x,curr->self->y);
    //             curr = curr->next;
    //         }
    //     }
    //     printf("\n");
    // }
}

void make_connect(int i,int j){
    int x_add[4] = {1,0,-1,0}, y_add[4] = {0,1,0,-1};
    for( int k = 0; k < 4; k++){
        int new_i = i + y_add[k], new_j = j + x_add[k];
        if(new_i<0 || new_i>=Y_width || new_j<0 || new_j>=X_width)    continue;
        switch( vertex[new_i][new_j]->value){
            case '0':     break;
            case '2':   ;
            case '1':   ;
                _Connect* curr = vertex[i][j]->connect;
                _Connect* rear = vertex[i][j]->connect;
                int n = 0;
                while(curr){        //triversal curr to NULL
                    curr = curr->next;
                    if(n)   rear = rear->next;
                    n++;
                }
                curr = (_Connect*) malloc( sizeof( _Connect));
                curr->self = vertex[new_i][new_j];
                curr->next = NULL;
                if(n == 0)      vertex[i][j]->connect = curr;
                else        rear->next = curr;
        }
    }
}

void show(){
    system("CLS");
    for( int i = 0; i < Y_width; i++){
        for( int j = 0; j < X_width; j++){
            printf("%c",vertex[i][j]->value);
        }
        printf("\n");
    }
    Sleep(100);
}