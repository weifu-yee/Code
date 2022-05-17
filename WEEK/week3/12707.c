#include <stdio.h>
#include <stdlib.h>

int main(){
    int H;
    scanf("%d",&H);
    for(int i = 1;i < H;i++){
        for(int j=i;j<H;j++)
            printf(" ");
        for(int j=1;j<=(i*2)-1;j++)
            printf("*");
        printf("\n");
    }
    for(int k=1;k<=H*2-1;k++)
    printf("*");

    return 0;

}

