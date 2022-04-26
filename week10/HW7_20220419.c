#include <stdio.h>
#include <stdlib.h>

typedef struct student{
    int number;
    char name[10];
    int score;
    struct student* next;
}STU;

void visit(STU* n);

int main(){
    FILE *input = fopen("input.txt","r");
    // STU *head = NULL, *New = NULL;
    // int num, score, nop = 0;
    // char name[10] = {0};
    int num;
    fscanf(input,"%d",&num);

    printf("%d",num);
    fclose(input);
    return 0;
}
//     while(1){
//         fscanf(input,"%d %s %d",&num,name,&score);
//         printf("%d %s %d",num,name,score);
//         if (fscanf(input,"%d",&num) == EOF){
//             break;
//         }
//         New = (STU*) malloc( sizeof( STU));
//         New->number = num;
//         char* aa = New->name;
//         aa = name;
//         New->score = score;
//         New->next = head;
//         head = New;
//         nop ++;
//     }

//     STU* arr1[nop];
//     STU* arr2[nop];
//     STU* arr3[nop];

//     STU* n = head;
//     for( int i = 0; i < nop; i++){
//         arr1[i] = n;
//         arr2[i] = n;
//         arr3[i] = n;
//         n = n->next;
//     }
//     for( int i = 0; i < nop; i++){
//         printf("%d\t",arr1[i]->number);
//     }




//     printf("Press '1' to show the arrangement by number!\n");
//     printf("Press '2' to show the arrangement by name!\n");
//     printf("Press '3' to show the arrangement by score!\n");
//     printf("Please press ");
// }

// void visit(STU* n){
//     while(n != NULL){
//         printf("%d %s %d",(n->number),n->name,(n->score));
//         n = n->next;
//     }
// }
