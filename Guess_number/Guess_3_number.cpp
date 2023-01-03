#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>


int* RNG(int* arr){     //to generate random number
    int num, cnt = 0;
    for(int i = 0; i < 3; i++)      arr[i] = -1;
    while(cnt < 3){
        do{
            num = rand() % 10;
        }while( cnt == 0 && num == 0 || num == arr[0] || num == arr[1] || num == arr[2]);
        arr[cnt++] = num;
    }
    int* arrptr = arr;
    return arrptr;
}
bool answer( int* arr, int* num){
    for(int i = 0; i < 3; i ++){
        if(arr[i] != num[i])        return false;
    }
    return true;
}
bool check(int *num){
    if(num[0] == 0)     return false;
    for(int i = 0; i < 3; i ++){
        for(int j = i + 1; j < 3; j ++){
            if(num[i] == num[j])        return false;
        }
    }
    return true;
}
void run( int* arr){
    int num[3];
    int A, B;       int cnt = 0;    bool f = false;
    //printf("\"%d%d%d%d\"\n",arr[0],arr[1],arr[2],arr[3]);
    printf("Please input 3 numbers to start the game!\n");
    do{
        f = true;
        A = 0, B = 0;       cnt ++;
        printf("    Guess(%d):\t",cnt);
        fflush(stdin);
        if( scanf("%1d%1d%1d",&num[0],&num[1],&num[2]) != 3){
            fflush(stdin);
            printf("\t~ ~ ~\"Number\" please!~ ~ ~\n");
            cnt --;
            continue;
        }
        if( !check(num)){
            printf("\t~ ~ ~numbers can't be repeated & first number can't be '0'~ ~ ~\n");
            cnt --;
            continue;
        }
        for(int i = 0; i < 3; i ++){
            if(num[i] == arr[i]){   A++;        continue;}
            for(int j = 0; j < 3; j ++){
                if(num[i] == arr[j]){   B++;        continue;}
            }
        }
        printf("You're input is---------->'%d%d%d' ~ ~ '%dA %dB'\n",num[0],num[1],num[2],A,B);
    }while(!answer(arr, num));
    puts("");
    for(int k = 0; k < 30; k ++){    printf("-");   Sleep(30);}
    printf("B I N G O !");
    for(int k = 0; k < 30; k ++){    printf("-");   Sleep(30);}
    puts("");
    printf("\n>> The answer is '%d%d%d'!",arr[0],arr[1],arr[2]);
    Sleep(1000);
    printf("\n>> Use '%d' times to find out!\n",cnt);
    Sleep(1000);
    return;
}

int main(){
    srand( (unsigned) time( NULL) + getpid());
    int arr[3];
    char cmd;
    do{
        system("CLS");
        run( RNG( arr));
        fflush(stdin);
        printf("\n~Press any key not 'q' to restart!\n");
        cmd = getch();
    }while(cmd != 'q');
    printf("\nB Y E  B Y E >_<\n");
    return 0;
}