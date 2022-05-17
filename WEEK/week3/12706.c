#include <stdio.h>
#include <stdlib.h>

int main(){
    int H;
    scanf("%d",&H);
    for(int i = 1;i <= H;i++){
       for(int j = 1;j <= i;j++){
           printf("*");
       }
       printf("\n");
    }
    return 0;
}
