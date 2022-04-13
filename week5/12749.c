#include <stdio.h>
#include <stdlib.h>

int main(){
    int primennn[1000] = {0};
    int prime[1000] = {0};
    int first = 0,breakkk = 1;

    for (int i=2 ;i<1000;i++){         //建立質數庫
            int if_prime = 1;
        for (int j =2;j<i;j++){
            if(!(i%j)){
                if_prime = 0;
                break;
            }
        }
        if (if_prime){
            primennn[i] = 1;
        }

    }
    int a =0;
    for (int i =0;i < 1000;i++){
        if (primennn[i]){
            prime[a] = i;
            a++;
        }
    }

    int N;
    scanf("%d",&N);
    while(breakkk){
        for(int j =0;j < a;j++){
            if (!(N % prime[j])){
                    if (first){
                        printf("*");
                    }
                printf("%d",prime[j]);
                first = 1;
                N /= prime[j];
                break;
            }
            else if (prime[j] >= N){
                breakkk = 0;
            break;
            }
        }
    }





    return 0;
}
