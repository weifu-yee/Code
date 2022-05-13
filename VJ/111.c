#include <stdio.h>
#include <stdlib.h>

int main()
{
    int v[100],n,count[100]={0},i,j,a=0;
    char c;
    for(int i=0; i<100; i++)
    {
        v[i]=i;
    }

    while((scanf("%d%c", &n,&c) == 2)){
        for(int i=0;i<100;i++){
            if(n == v[i]){
                count[i] ++;
                break;
            }
        }
        if (c == '\n')     break;
    }

    for(i = 0;i < 100;i++){
        if(count[i] > a){
            a = count[i];            
        }
    }
    j = 0;
    for(i = 0;i < 100;i ++){
        if(count[i] == a){
            printf(j?" %d":"%d",i);
            j = 1;
        }
    }
    printf("\n");
    return 0;
}