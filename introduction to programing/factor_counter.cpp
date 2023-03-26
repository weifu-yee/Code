#include <stdio.h>

int main(){
    //estblish a prime number array
    int prime[2000] = {0};
    int prime_number = 0;
    for(int i = 2; i < 2000; i++){
        if(prime[i] == 0){
            prime_number++;
            for(int j = i + i; j < 2000; j += i){
                prime[j] = 1;
            }
        }
    }
    int n;
    scanf("%d",&n);
    for(int i = 0; i < n; i++){
        //to find out the most factor number in the range use the prime number array
        int l;  int r;
        scanf("%d %d",&l,&r);
        int max = 0;
        int max_number = 0;
        for(int j = l; j <= r; j++){
            int factor = 0;
            for(int k = 0; k <= j; k++){
                if( prime[k] != 0){ //###
                    if(j%k==0){ //###
                        factor ++;
                    }
                }
            }
            if(factor > max){
                max = factor;
                max_number = j;
            }
        }
        printf("%d\n",max_number);
    }
    return 0;
}