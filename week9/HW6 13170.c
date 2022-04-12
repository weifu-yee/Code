#include <stdio.h>
int main() {
    char arr[30];
    scanf("%s",arr);
    int i = 0,pn = 1,temp = 0,sum = 0;
    while(1){
        if (*(arr+i) >= 48 && *(arr+i) <= 57){
            temp *= 10 , temp += (pn)? (*(arr+i) - 48) : (48 - *(arr+i));
        }else{
            sum += temp , temp = 0 , pn = (*(arr+i) == 43)? 1 : 0 ;
            if (*(arr+i) == '\0') break;
        }
        i++;
    }
    printf("%d",sum);
    return 0;
}