#include<stdlib.h>
#include<stdio.h>
//建立一個單向 linked list, 每次都由開頭新增。
typedef struct node {
  	int data;
  	struct node *next;
}NODE;

int main(){
	NODE *head = NULL, *new_node = NULL;
    	char cmd;
    	int data;

	//只做簡易的固定指令接收，未處理錯誤輸入格式的狀況
    	while (1) {
        	scanf("%c", &cmd);
        	switch (cmd) {
           		case 'q':
                    /*因為顯示linked list之後程式就結束了, 所以這
                    邊使用head指標. 如果你的程式不是緊接著就結束,
                    最好有一個暫存的指標來負責指向. head應該要永遠
                    指向linked list的開頭.
                    */
                	
			        while (head != NULL){
                        	printf("%d", head->data);
                        	head = head->next;
                        	if (head!= NULL)
                            printf("->");
                    }
                	exit(1);
            	case 'a':
            	    	new_node = (NODE *) malloc(sizeof(NODE));
                    scanf("%d",&data);
                    new_node->data  = data;
                    //先設定新增node的連結到head
                    new_node->next = head;
                    //再把原本的head連結設定到新增的node
                    head = new_node;
                	break;
            	default:
                	continue;
        	}
    	}
  	return 0;
}