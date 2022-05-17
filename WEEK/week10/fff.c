#include<stdlib.h>
#include<stdio.h>
//建立一個單向 linked list, 每次都由開頭新增。
typedef struct node {
  	int data;
  	struct node *next;
}NODE;

void add_node (NODE **head_ref, int new_data){
    	NODE *new_node = (NODE *) malloc(sizeof(NODE));

    	new_node->data  = new_data; 
	//先設定新增node的連結到head
	new_node->next = (*head_ref); 	
	//再把原本的head連結設定到新增的node
    	(*head_ref)    = new_node;
}
void visitlist (NODE *node){
    	while (node != NULL){
        	printf("%d", node->data);
        	node = node->next;
       	 	if (node!= NULL)
            		printf("->");
    }
}

int main(){
	NODE *head = NULL;
    	char cmd;
    	int data;

//只做簡易的固定指令接收，未處理錯誤輸入格式的狀況
    	while (1) {
        	scanf("%c", &cmd);
        	switch (cmd) {
           		case 'q':
                	visitlist (head);
                	exit(1);
            	case 'a':
                	scanf("%d",&data);
                	add_node(&head, data);
                	break;
            	default:
                	continue;
        	}
    	}
  	return 0;
}
