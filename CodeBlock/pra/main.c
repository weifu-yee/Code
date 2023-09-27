#include <stdio.h>
#include <stdlib.h>

struct node{
    int value;
    struct node* next;
};

int main(){
    char ch;
    int num;
    struct node* head = malloc(sizeof(struct node));
    struct node* current = head;

    do{
        scanf("%c %d",&ch,&num);
        if (ch == 'q'){
            printf("%d",current -> value);
            return 0;
        }else{
            current -> value = num;
            current -> next = malloc(sizeof(struct node));
            current = current -> next;
        }
    }while(ch == 'a');

    return 0;

}
