#include<stdio.h>
#include <stdio.h>
int main()  {
    int a , b , low , high  ;
    scanf("%d%d",&a,&b);
    if (a < b){
        low = a;
        high = b;
    }
    else if (a > b){
        low = b;
        high = a;
    }

    if (low < 3)
        low = 2;

    int i = low,v = 0;
    while(i <= high){
      int j = 2;
      int c = 1;
      while(j < i){
        if (i % j == 0){
                c = 0;
            }
        j ++;
        }

            if (c != 0){

                    if (v){
                printf(" ");
                }
            v=1;
            printf("%d",i);

            }
      i ++;

    }

    return 0;
}
