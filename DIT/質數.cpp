#include<stdio.h>
#include<stdlib.h>

int main(){
    int a, k = 2;
    scanf("%d", &a);
    if(a <= 1){
        printf("No");
        return 0;
    }
    while(1){
        if( !(a % k)){
            printf("No");
            return 0;
        }
        if( k > a/2){
            printf("Yes");
            return 0;
        }
        k ++;
    }
}