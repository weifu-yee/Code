#include <stdio.h>
#include <iostream>
using namespace std;

#include "../inc/openfile.h"
FILE* openfile(void){
    FILE* inf;
    inf = fopen("../file/graph1.txt", "r");   
    if( !inf){
        printf("The file does not be found!\n"),  exit(1);
    }
    char c,_n;
    int i = 0;
    while( !feof( inf)){
        int j = 0;
        do{
            fscanf(inf,"%c",&c);
            cout<<c;
        } while( !fscanf(inf,"%[\n]",&_n) );
        cout<<endl;
    }
    fclose(inf);
    return inf;
}