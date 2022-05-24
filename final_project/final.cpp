#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

typedef struct _Vertex{
    int value;
    int x;
    int y;
    bool visited;
    struct _Connect* connect;
}_Vertex;

typedef struct _Connect{
    struct _Vertex* self;
    struct _Vertex* next;
}_Connect;

_Vertex* vertex[50][50];
int X_width, Y_width;

void Adjacency_List();
void make_connect(int i,int j);

int main(){
    Adjacency_List();
    return 0;
}

void Adjacency_List(){
    FILE* inf = fopen("D:/Code/final_project/input1.txt","r");
    int i = 0;
    while( !feof( inf)){
        int j = 0;
        X_width = 0;
        do{
            _Vertex* new_vertex = (_Vertex*) malloc( sizeof( _Vertex));
            vertex[i][j] = new_vertex;
            new_vertex->x = j;
            new_vertex->y = i;
            new_vertex->visited = false;
            fscanf(inf,"%1d",&(new_vertex->value));
            new_vertex->connect = NULL;
            make_connect(i,j);
            j++, X_width++;
        } while( !fscanf(inf,"%[\n]") );
        i++, Y_width++;
    }
    fclose(inf);
    return;

    // printf("\nX:%d \tY:%d\n",X_width,Y_width);
    // for(int i = 0; i < Y_width; i++){
    //     for(int j = 0; j < X_width; j++){
    //             printf("(%d,%d):",vertex[i][j]->x,vertex[i][j]->y);
    //             if(vertex[i][j]->value != 2561){
    //                 printf("%d ",vertex[i][j]->value);
    //             }else printf("\nddd\t x = %d, y = %d\n",vertex[i][j]->x,vertex[i][j]->y);
    //     }
    //     printf("\n");
    // }
}

void make_connect(int i,int j){
    int x_add[] = {1,0,-1,0}, y_add[] = {0,1,0,-1};
    for( int k = 0; k < 4; k++){
        int new_i = i + y_add[k], new_j = j + x_add[k];
        if(new_i<0 || new_i>Y_width || new_j<0 || new_j>X_width)    continue;
        switch( vertex[new_i][new_j]->value){
            case 0:     break;
            case 2:
            case 1:
                _Connect* curr = vertex[i][j]->connect;
                while(curr)     curr = curr->self->connect;
                curr->connect = vertex[new_i][new_j];
        }
    }
}