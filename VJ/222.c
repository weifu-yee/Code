#include "stdio.h"
#include "stdlib.h"

int main(){
    int arr[50] = {0}, n, arr_n, change_n, i = 0;
    scanf("%d%d",&arr_n,&n);
    for(i = 0; i < arr_n; i++)     arr[i + n] = i + 1;
    for(i = 0; i < n; i++){
        scanf("%d",&change_n);
        arr[n -1 -i] = arr[change_n + n - 1];
        arr[change_n + n - 1] = 0;
    }
    for(i = 0; i < arr_n + n; i++)     printf((arr[i])?"%d\n":"",arr[i]);
    return 0;
}