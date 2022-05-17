#include<stdio.h>
#include <stdio.h>
#include <string.h>


int main() {

    int N ,smaller = 0, now;
    //scanf("%d",N);
    int arr[1000] = {0},brr[1000] = {0};

    scanf("%d",&N);
    for(int i = 0;i < N ;i++){
        scanf("%d",&arr[i]);
    }

    for(int i = 0;i < N ;i++){
        smaller = 0 ;
        for(int j = 0;j < N ;j++){
            if (smaller <= arr[j]){
                smaller = arr[j];
                now = j;
            }
        }
        arr[now] = 0;
        brr[i] = smaller;
    }

        printf("%d",brr[N-1]);
        for (int i = N-2;i >= 0;i--){
        printf(" %d",brr[i]);
    }


    return 0;
}
