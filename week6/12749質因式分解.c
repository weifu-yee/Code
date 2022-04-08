#include<stdio.h>
int main(){
    int n, first=1;
    scanf("%d",&n);
    for (int i=2; i<=n; i++){
        if (!(n%i)){
            if (first){
                printf("%d",i);
                first=0;
            }else{
                printf("*%d",i);
            }
            n/=i;
            i-=1;
        }
    }
    return 0;
}