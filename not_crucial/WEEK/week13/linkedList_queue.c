#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node *next;
}node;

typedef struct queue{
    node* front;
    node* rear;
    int count;
}queue;

void enqueue(queue* q){
    node* newnode = (node*)malloc(sizeof( node));
    newnode->next = NULL;
    if (q->count)   q->rear->next = newnode;
    else     ;
    q->rear = newnode;
    printf("Please input a number!\n");
    scanf("\t%d",&newnode->data);
    q->front = (q->count)?q->front: newnode;
    q->count ++;
}

int dequeue(queue* q){
    if( !q->count)  return 0;
    printf("front is : %d\n",q->front->data);
    node* tmp = q->front;
    q->front = q->front->next;
    free(tmp);
    q->count --;
    return 1;
}

int main(){
    char cmd;
    queue* q = (queue*)malloc(sizeof( queue));
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    int www = 1;
    while(www){
        printf("\tKey a command?\n");
        scanf("\t%c",&cmd);
        switch( cmd){
        case '1':
            enqueue(q);
            break;
        case '2':
            www = dequeue(q);
            break;
        case 'q':
            www = 0;
        }
    }
    return 0;

}
