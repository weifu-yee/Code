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
        char* new_name = malloc( 10*sizeof( char));     //含字串結尾最多10個
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
    for( int i = 0; i < nop; i++){      //建立3個陣列 記錄指標指向linked list
        arr1[i] = n;
        arr2[i] = n;
        arr3[i] = n;
        n = n->next;
    }
    
    STU* stuptr_temp;
    int a,b;        //另存兩個變數以比較英文排序(考慮大小寫)
    for( int i = 0; i < nop -1; i++){
        for( int j = 0; j < nop -1 -i; j++){
            int k;
            for( k = 0; k < 9; k++){        //名字不超過9個字母，最多往下比到9個
                a = *(arr2[j]->name + k) - 65;      //大寫小寫轉換為相同數字比較
                a = ((a-25)>0)? a-32 : a;           //~
                b = *(arr2[j+1]->name + k) - 65;    //~
                b = ((b-25)>0)? b-32 : b;           //~
                if( a > b ){
                    stuptr_temp = arr2[j];
                    arr2[j] = arr2[j+1];
                    arr2[j+1] = stuptr_temp;
                    break;        
                }else if( a < b )   break;
            }
            if(k == 9){
                if( arr2[j]->number > arr2[j+1]->number){
                    stuptr_temp = arr2[j];
                    arr2[j] = arr2[j+1];
                    arr2[j+1] = stuptr_temp;
                }
            }
        }
    }
    for( int i = 0; i < nop -1; i++){
        for( int j = 0; j < nop -1 -i; j++){
            if( arr3[j]->score > arr3[j+1]->score){
                    stuptr_temp = arr3[j];
                    arr3[j] = arr3[j+1];
                    arr3[j+1] = stuptr_temp;
            }else if(arr3[j]->score == arr3[j+1]->score){       //分數一樣比學號
                if( arr3[j]->number > arr3[j+1]->number){
                    stuptr_temp = arr3[j];
                    arr3[j] = arr3[j+1];
                    arr3[j+1] = stuptr_temp;
                }
            }
        }
    }

    printf("Key '1' to show the arrangement by rollNumber!\n");
    printf("Key '2' to show the arrangement by studentName!\n");
    printf("Key '3' to show the arrangement by score!\n");
    char cmd = 0;
    int while_time = 0;
    while(cmd != 'q'){
        printf((while_time)?"\nPlease key a command and press the 'Enter' again : ":"Please key a command and press the 'Enter' : ");
        scanf("\n%c",&cmd);
        switch( cmd){
            case '1' :
                printf("\nBy rollNumber ~ ~ ~\n");
                visitlist(head);
                break;
            case '2' :
                printf("\nBy studentName ~ ~ ~\n");
                for( int i = 0; i < nop; i++){
                    printf("%d %s %d\n",arr2[i]->number,arr2[i]->name,arr2[i]->score);
                }
                break;   
            case '3' :
                printf("\nBy score ~ ~ ~\n");
                for( int i = 0; i < nop; i++){
                    printf("%d %s %d\n",arr3[i]->number,arr3[i]->name,arr3[i]->score);
                }
                break;
            case 'q' :
                break;
            default :
                printf("\nThis command is not valid ! ! ! ! ! ! !\n");
                break;
        }
        while_time =1;
    }
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
