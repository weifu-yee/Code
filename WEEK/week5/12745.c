#include <stdio.h>
#include <stdlib.h>

int main() {
    int n,jz =0;
    scanf("%d",&n);
    for (int i =1;i<=n;i++){
    jz += i;
    }

    printf("%d",jz);
    return 0;


}

