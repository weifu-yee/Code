#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>


int rdd(){
    srand( (unsigned) time( NULL));
    int arr[4] = {0};
    int num, cnt = 0;
    while(cnt <4){
        do{
            num = rand() % 10 + 1;
        }while(arr[0] == 0 && num == 1
            || num == arr[0]
            || num == arr[1]
            || num == arr[2]
            || num == arr[3]);
        arr[cnt++] = num;
    }
    for( int i = 0; i < 4; ++i){
        printf("%d",arr[i] - 1);
        if(i == 3)
            puts("\n");
    }

    return 0;
}

int main(){
    char cmd;
    while(1){
        rdd();
        Sleep(1000);
    }
    return 0;
}