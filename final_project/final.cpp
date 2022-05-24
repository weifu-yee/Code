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
    struct _Vertex* connect;
}_Vertex;

_Vertex* vertex[50][50];

void Adjacency_List();
void make_connect(int i,int j);

int main(){
    Adjacency_List();
    return 0;
}

void Adjacency_List(){
    FILE* inf = fopen("D:/Code/final_project/input1.txt","r");
    int X_width = 0, Y_width = 0;
    int i = 0;
    while( !feof( inf)){
        int j = 0;
        X_width = 0;
        do{
            _Vertex* new_vertex = (_Vertex*) malloc( sizeof( _Vertex));
            vertex[i][j] = new_vertex;
            new_vertex->x = j;
            new_vertex->y = i;
            new_vertex->connect = NULL;
            fscanf(inf,"%1d",&(new_vertex->value));
            //printf((j == 14)?"%d \n":"%d ",vertex[i][j]->value);
            //make_connect(i,j);
            j++, X_width++;
        }while( !fscanf(inf,"%[\n]") );
        i++, Y_width++;
    }
    fclose(inf);

    printf("\nX:%d \tY:%d\n",X_width,Y_width);
    for(int i = 0; i < Y_width; i++){
        for(int j = 0; j < X_width; j++){
                //printf("(%d,%d):",vertex[i][j]->x,vertex[i][j]->y);
                //if(vertex[i][j]->value != 2561){
                    printf("%d ",vertex[i][j]->value);
                //}else printf("\nddd\t x = %d, y = %d\n",vertex[i][j]->x,vertex[i][j]->y);
        }
        printf("\n");
    }
}

void make_connect(int i,int j){

}