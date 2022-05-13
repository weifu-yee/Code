#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void posfix(char Y[]);
char* infix_to_pos(char X[]);
void pop(char stack[],int top,char value);

int main(){
    char X[1000];
    scanf("%s",X);
    posfix( infix_to_pos(X ));
    return 0;
}

void posfix(char Y[]){
    int stack[1000];
    int top = -1, j = 0, tmp;
    while(1){
        if( Y[j] >= 48 && Y[j] <= 57)   stack[++ top] = Y[j] - 48;
        else if( Y[j] == 42 || Y[j] == 43 || Y[j] == 45 || Y[j] == 47 || Y[j] == 94){
            tmp = stack[top --];
            switch( Y[j]){
            case '+':   stack[top] = stack[top] + tmp;  break;   
            case '-':   stack[top] = stack[top] - tmp;  break;   
            case '*':   stack[top] = stack[top] * tmp;  break;   
            case '/':   stack[top] = stack[top] / tmp;  break;   
            case '^':   stack[top] = pow( stack[top], tmp);  break;
            }
        }else   break;
        j ++;
    }
        printf((!top)?"%d":"\tThe expression isn't complete !\n",stack[top]);
}

char* infix_to_pos(char X[]){
    int count = 0;
    while( X[count])    count ++;
    char stack[count], Y[count];
    X[count] = ')';
    X[count +1] = '\0';
    int i = 0,topS = -1,topY = -1;
    while( X[i]){
        switch( X[i]){
        case '^' :
            Y[++ topY] = stack[topS -2];
            Y[++ topY] = stack[--topS];
            topS--;
            break;
        case '*' :
            if(stack[topS] == '')
            pop(stack,top,X[i]);
            break;
        case '/' :break;
        case '+' :break;
        case '-' :break;
        default: 
            stack[++ top] = X[i];
        }
    }
    return Y;
}

