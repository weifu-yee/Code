#include <stdio.h>

int main(){
    int n;
    char string[30];
    scanf("%s",string);

    int i = 0;
    int temp = 0 , sum = 0;
    int am =1;
    while(string[i] != '\0'){
        if (string[i] == 43){
            if (am){sum += temp;}
                else{sum -= temp;}
            am = 1;
            temp = 0;

        }else if (string[i] == 45){
            if (am){sum += temp;}
                else{sum -= temp;}
            am = 0;
            temp = 0;
        }else{
            temp *= 10;
            temp += string[i] - 48;
        }
        i ++;
    }
    if (temp){
        if (am)
            sum += temp;
        else
            sum -= temp;
    printf("%d",sum);
    }


    return 0;
}
