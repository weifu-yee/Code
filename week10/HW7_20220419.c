#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct student{
    int number;
    char *name;
    int score;
    struct student* next;
}STU;

void visitlist(STU* n);

int main(){
    FILE *input = fopen("input.txt","r");
    STU *head = NULL, *new_stu = NULL;
    int num, score, nop=0, temp=0;
    char name[10];
    //char* name_ptr = &name;
    // fscanf(input,"%d",&num);
    // fscanf(input,"%s",name);
    // fscanf(input,"%d",&score);
    while( fscanf(input,"%d%s%d",&num,name,&score) == 3){
        new_stu = (STU*) malloc( sizeof( STU));
        new_stu->number = num;
        printf("%s\n",name);
        char* new_name = malloc( 10*sizeof( char));
        for( int i = 0; i < 10; i++){
            *(new_name + i) = *(name + i);
        }
        new_stu->name = new_name;
        new_stu->score = score;
        new_stu->next = head;
        head = new_stu;
        nop ++;
    }
        visitlist(head);
        printf("%d",nop);
    // }

    // STU* arr1[nop];
    // STU* arr2[nop];
    // STU* arr3[nop];

    // STU* n = head;
    // for( int i = 0; i < nop; i++){
    //     arr1[i] = n;
    //     arr2[i] = n;
    //     arr3[i] = n;
    //     n = n->next;
    // }
    // for( int i = 0; i < nop; i++){
    //     printf("%d\t",arr1[i]->number);
    // }
    // printf("Press '1' to show the arrangement by rollnumber!\n");
    // printf("Press '2' to show the arrangement by name!\n");
    // printf("Press '3' to show the arrangement by score!\n");
    // printf("Please press ");

    // printf("%d\n",num);
    // printf("%s\n",name_ptr);
    // printf("%d\n",score);
    fclose(input);
    return 0;
}

void visitlist(STU* n){
    while(n != NULL){
        printf("%d %s %d\n",n->number,n->name,n->score);
        n = n->next;
    }
}
