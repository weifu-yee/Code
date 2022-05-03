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
        char* new_name = malloc( 10*sizeof( char));     //�t�r�굲���̦h10��
        for( int i = 0; i < 10; i++)    *(new_name + i) = *(name + i);
        new_stu->name = new_name;
        new_stu->score = score;
        new_stu->next = head;
        head = new_stu;
        nop ++;             //�����H��
    }
    head = bubblesort(head,nop);        //�i��w�j�Ƨ�

    STU* arrN[nop];
    STU* arrS[nop];
    STU* n = head;
    for( int i = 0; i < nop; i++){      //�إ�2�ӷs���}�C �O�����Ы��Vlinked list
        arrN[i] = n;                    //�m�W�Ƨ�
        arrS[i] = n;                    //�Ǹ��Ƨ�
        n = n->next;
    }

    STU* stuptr_temp;       //�Ȧs����
    int a,b;        //�t�s����ܼƥH����^��Ƨ�(�Ҽ{�j�p�g)
    for( int i = 0; i < nop -1; i++){       //�o��for�j��Ʃm�W
        for( int j = 0; j < nop -1 -i; j++){
            int k;
            for( k = 0; k < 9; k++){        //�W�r���W�L9�Ӧr���A�̦h���U���9��
                a = *(arrN[j]->name + k) - 65;      //�j�g�p�g�ഫ���ۦP�Ʀr���
                a = ((a-25)>0)? a-32 : a;           //~
                b = *(arrN[j+1]->name + k) - 65;    //~
                b = ((b-25)>0)? b-32 : b;           //~
                if( a > b ){
                    stuptr_temp = arrN[j];
                    arrN[j] = arrN[j+1];
                    arrN[j+1] = stuptr_temp;
                    break;
                }else if( a < b )   break;
            }
            if(k == 9){
                if( arrN[j]->number > arrN[j+1]->number){
                    stuptr_temp = arrN[j];
                    arrN[j] = arrN[j+1];
                    arrN[j+1] = stuptr_temp;
                }
            }
        }
    }
    for( int i = 0; i < nop -1; i++){           //�o��for�j��Ʀ��Z
        for( int j = 0; j < nop -1 -i; j++){
            if( arrS[j]->score > arrS[j+1]->score){
                    stuptr_temp = arrS[j];
                    arrS[j] = arrS[j+1];
                    arrS[j+1] = stuptr_temp;
            }else if(arrS[j]->score == arrS[j+1]->score){       //���Ƥ@�ˤ�Ǹ�
                if( arrS[j]->number > arrS[j+1]->number){
                    stuptr_temp = arrS[j];
                    arrS[j] = arrS[j+1];
                    arrS[j+1] = stuptr_temp;
                }
            }
        }
    }

    printf("Key '1' to show the arrangement by rollNumber!\n");
    printf("Key '2' to show the arrangement by studentName!\n");
    printf("Key '3' to show the arrangement by score!\n");
    printf("Key 'q' to exit!\n");
    char cmd = 0;
    int while_time = 0;
    while(cmd != 'q'){          //���O�j��
        printf((while_time)?"\nPlease key a command and press the 'Enter' again : ":"Please key a command and press the 'Enter' : ");
        scanf("\n%c",&cmd);
        switch( cmd){
            case '1' :
                printf("\n\tBy rollNumber ~\n");
                visitlist(head);
                break;
            case '2' :
                printf("\n\tBy studentName ~\n");
                for( int i = 0; i < nop; i++)   printf("%d %s %d\n",arrN[i]->number,arrN[i]->name,arrN[i]->score);
                break;
            case '3' :
                printf("\n\tBy score ~\n");
                for( int i = 0; i < nop; i++)   printf("%d %s %d\n",arrS[i]->number,arrS[i]->name,arrS[i]->score);
                break;
            case 'q' :
                break;
            default :
                printf("\n\tThis command is not valid ! ! ! ! ! ! !\n");
                break;
        }
        while_time =1;          //�����O�_������printf
    }
    fclose(input);
    return 0;
}
void visitlist(STU* n){             //printf�X linked list
    while(n != NULL){
        printf("%d %s %d\n",n->number,n->name,n->score);
        n = n->next;
    }
}
STU* bubblesort(STU* head,int nop){         //�w�j�Ƨ�linked list
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
