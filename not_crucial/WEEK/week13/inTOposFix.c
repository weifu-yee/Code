#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void posfix(char Y[]);
char* infix_to_pos(char X[]);
int count_X(char X[]);
void push(char stack[],int* top,char value);
char pop(char stack[],int* top);

int main(){
    char X[1000];
    scanf("%s",X);
    posfix( infix_to_pos(X ));
    return 0;
}

void posfix(char Y[]){
    printf("%s",Y);
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
    printf("\t~ ~ ");
    printf((!top)?"%d":"\tThe expression isn't complete !\n",stack[top]);
}

char* infix_to_pos(char X[]){
    int count = count_X(X);
    char stack[count], Y[count];
    X[count] = ')';
    X[count +1] = '\0';
    printf("\t---X:%s---\n",X);

    int i = 0,topS = -1,topY = -1,w = 1;
    push( stack, &topS, '(');
    while( X[i]){
        printf("---X[i]:%c---",X[i]);
        switch( X[i]){
        case '+' :
        case '-' :
            while(w){
                switch( stack[topS]){
                case '+' :
                case '-' :    
                case '*' :    
                case '/' :    
                case '^' :
                    push( Y, &topY, pop(stack,&topS));
                    break;
                default :
                    w = 0;
                }
            }
        case '*' :
        case '/' :
            w = 1;
            while(w){
                switch( stack[topS]){    
                case '*' :    
                case '/' :    
                case '^' :
                    push( Y, &topY, pop(stack,&topS));
                    break;
                default :
                    w = 0;
                }
            }
        case '^' :
            if( stack[topS] == '^')     push( Y, &topY, pop(stack,&topS));
        case '(' :
            push(stack,&topS,X[i]);
            break;
        case ')' :
            while( stack[topS] != '(')      push( Y, &topY, pop(stack,&topS));
                topS --;
            break;
        default: 
            push( Y, &topY, X[i]);
        }
        i++;
        printf("\t---stack:%s---",stack);
        printf("\t---Y:%s---\n",Y);
    }
    // char* YY = (char*) malloc(count* sizeof( char));
    // YY = Y;
    //printf("%s",YY);
    /*while( X[i]){
        switch( X[i]){
        case '^' :
            push(stack,topS,X[i]);
            break;
        case '*' :
        case '/' :
            if(stack[topS] == '^'){
                temp = pop(stack,topS);
                push(Y,topY,temp);
            }
            push(stack,topS,X[i]);
            break;
        case '+' :
        case '-' :
            while(stack[topS] == '^' || stack[topS] == '*' || stack[topS] == '-'){
                temp = pop(stack,topS);
                push(Y,topY,temp);
            }
            push(stack,topS,X[i]);
            break;
        case '(' :break;
        case ')' :break;
        default: 
            stack[++ top] = X[i];
        }
        i++;
    }*/
    
    char* Y_ptr = Y;
    Y[topY + 1] = '\0';
    printf("\t###Y_ptr:%s---\n",Y_ptr);
    return Y_ptr;
}

int count_X(char X[]){
    int count = 0;
    while(X[count])     count++;
    return count;
}

void push(char stack[],int* top,char value){
    stack[++ (*top)] = value;
}

char pop(char stack[],int* top){
    return stack[(*top)--];
}