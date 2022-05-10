#include <stdio.h>
#include <stdlib.h>

int main(){
    int stack[1000];
    int top = -1 , tmp;
    char X;
    while(scanf("%c",&X) != EOF){
        if( X >= 48 && X <= 57){
            top ++;
            stack[top] = X - 48;
        }else if( X == 42 || X == 43 || X == 45 || X == 47){
            tmp = stack[top];
            top --;
            stack[top] = ((X == '+')? stack[top] + tmp : (X == '-')?stack[top] - tmp : (X == '*')?stack[top] * tmp : stack[top] / tmp );
        }else{
            break;
        }

    }
    printf("%d",stack[top]);
    return 0 ;

}
