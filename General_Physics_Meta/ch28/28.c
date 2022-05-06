#include "D:\Code\General_Physics_Meta\physical_constants.h"
#include <stdio.h>
#include <stdlib.h>

int q1(FILE* file){

}
int main(){
    FILE* file = fopen( "D:\Code\General_Physics_Meta\ch28\value.txt", "r");
    
    printf("%d\t",q1(&file));
    printf("%d\t",q2(&file));
    printf("%d\t",q3(&file));
    printf("%d\t",q4(&file));
    printf("%d\t",q5(&file));
    printf("%d\t",q6(&file));

    fclose( file);
    return 0;
}