#include <stdio.h>
#include <stdlib.h>
typedef struct student{
    int number;
    char *name;
    int score;
    struct student* next;
}STU;

void visitlist(STU* n);
STU* bubblesort(STU* head,int nop);

int main(){
    FILE *input = fopen("input.txt","r");
    STU *head = NULL, *new_stu = NULL;
    int num, score, nop=0, temp=0;
    char name[10];
    while( fscanf(input,"%d%s%d",&num,name,&score) == 3){
        new_stu = (STU*) malloc( sizeof( STU));
        new_stu->number = num;
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
    head = bubblesort(head,nop);
    //visitlist(head);

    STU* arr1[nop];
    STU* arr2[nop];
    STU* arr3[nop];

    STU* n = head;
    for( int i = 0; i < nop; i++){
        arr1[i] = n;
        arr2[i] = n;
        arr3[i] = n;
        n = n->next;
    }
    for( int i = 0; i < nop; i++){
        if( arr1[i]->number ){}
    }
    printf("Press '1' to show the arrangement by rollNumber!\n");
    printf("Press '2' to show the arrangement by studentName!\n");
    printf("Press '3' to show the arrangement by score!\n");
    printf("Please press command!\n");
    char cmd;
    int while_boo = 1;
    do{printf("\n-----");
        scanf("%c",&cmd);
        if(cmd == '1'){
            printf("[1]\n");
            visitlist(head);
        }else if(cmd == '2'){
            printf("[2]\n");
        }else if(cmd == '3'){
            printf("[3]\n");
        }else if(cmd == 'q'){
            printf("[q]\n");
            while_boo = 0;
        }else if(cmd == '0'){

        }else{
            printf("[defaut]\n");
            printf("This command is not valid!\n");
        }
        cmd = '0';
    }while(while_boo);
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
STU* bubblesort(STU* head,int nop){
    STU *temp = head;
    for(int i = nop - 1; i > 0; i--){
        STU  *prev = head, *curr = head;
        for( int j=0; j< i && curr->next; j++){
            if( curr->number > curr->next->number){
                temp = curr->next;
                curr->next = temp->next;
                temp->next = curr;
                if( curr == head){
                    head = temp;
                    prev = temp;
                }
                else{
                    prev->next = temp;
                    prev = prev->next;
                }
            }else{
                curr = curr->next;
                if( j!= 0){
                    prev = prev->next;
                }
            }
        }
    }
    return head;
}
