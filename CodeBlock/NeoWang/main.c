#include <stdio.h>
#include <stdlib.h>
char array[30][30];

int main(){
    FILE *input;
    input = fopen("D:/Code/final_project/input1.txt","r");
    char k;
    for(int j=0;j<15;j++){
        for(int i=0;i<15;i++){
            fscanf(input,"%c",&array[i][j]);
            fscanf(input,"\n",&k);

        }
    }


    for(int j=0;j<15;j++){
        for(int i=0;i<15;i++){
                printf("%c",array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
