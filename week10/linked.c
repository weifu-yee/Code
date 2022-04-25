#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int num;
    struct node* next;
}Node;

int main(){
    int n;

    struct node* head , *new_node = NULL;
    head = (Node *) malloc(sizeof(Node));
    // NODE *new_node = (NODE *) malloc(sizeof(NODE));
    scanf("%d",&n);
    head->num = n;
    Node *current = head;

    while(1){
        
        scanf("%d",&n);
        if(n == 0)
            //free(current -> next);
            //current -> next = NULL;
            break;
        current -> num = n;
        new_node = (Node *) malloc(sizeof(Node));
        current -> next = new_node;
        current = current -> next;
        
    }
    current = head;
    printf("ddd");
    while(head -> next != NULL){
        printf("%d\n",head -> num);
        head = head -> next; 
    }
    return 0;
}