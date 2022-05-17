#include <stdio.h>
#include <stdlib.h>

int main(){
    int ch;
    scanf("%c",&ch);
    if (ch>=48&&ch<=57){
        printf("Number %c",ch);
    }
    else if (ch>=65&&ch<=90){
        printf("%c",ch+32);
    }
    else if (ch>=97&&ch<=122){
        printf("%c",ch-32);
    }
    return 0;
}
