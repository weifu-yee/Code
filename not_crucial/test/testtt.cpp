#include <stdio.h>

int is_prime(int n){
    if(n == 1){
        return 0;
    }
    for(int i = 2; i * i <= n; i ++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

int is_prime(){
    int n;
    scanf("%d",&n);
    if(n == 1){
        return 0;
    }
    for(int i = 2; i * i <= n; i ++){
        if(n % i == 0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
// want to find a ^ b
    for(int i = 1; i <= 100; i ++){
        for(int j = 1; j <= 100; j ++){
            if(is_prime(i) && is_prime(j)){
                a = i;
                b = j;
                c = a ^ b;
                if(is_prime(c)){
                    d = a;
                    e = b;
                    f = c;
                }
            }
        printf("%d %d %d, %d %d %d",a,b,c,d,e,f);
        }
    }

    //justfy if odd
    if(a % 2 == 1){
        printf("%d %d %d",a,b,c);
    }
}
