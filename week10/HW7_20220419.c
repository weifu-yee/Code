#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    int number;
    char name[10];
    int score;
    struct student* next;
}STU;

int main(){
    FILE *input = fopen("input.txt","r");
    STU *head;
    head = malloc (sizeof (STU));
    // head -> next = malloc (sizeof (STU));
    STU *current;
    current = head;
    while(1){
        if (fscanf(input,"%d %s %d",current -> number,current -> name,current -> score) != EOF){
        current = current -> next;
        current -> next = malloc (sizeof (STU));
        }else{
            free(current -> next);
            current -> next = NULL;
        }
    }




    printf("Press '1' to show the arrangement by number!\n");
    printf("Press '2' to show the arrangement by name!\n");
    printf("Press '3' to show the arrangement by score!\n");
    printf("Please press ");
}

