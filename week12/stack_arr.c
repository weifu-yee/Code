#include<stdio.h>
#include<stdlib.h>

char stack[1000];
int top = -1;

int push(int x){
    top ++;
    stack[top] = x;
    //printf("push x");
    return 0;
}
int pop(int x){
    if(top >= -1){
        if(stack[top] == x){
            top --;
            //printf("e");
            return 0;
        }else{
            return 1;
        }
    }else{
//        printf("8");
        return 1;
    }
}

int main(){
    char str[1000];
    scanf("%s",&str[0]);
    int i = 0,right = 0;
//printf("\nright:%d\n",right);
    while((str[i] != '\0') && (!right)){
        switch(str[i]){
        case '{':
            push(1);
            break;
        case '[':
            push(2);
            break;
        case '(':
            push(3);
            break;
        case '}':
            right = pop(1);
            break;
        case ']':
            right = pop(2);
            break;
        case ')':
            right = pop(3);
            break;
        }
        i++;
    }
    //printf("\nright:%d\n",right);
    printf(((top == -1)&&(right == 0))?"balanced":"not balanced");

    return 0;

}