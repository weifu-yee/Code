#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct word{
    char* initial;
    struct word* next;
}word;
typedef struct page_number{
    int number;
    struct word* the_word;
    struct page_number* next;
}page_number;

page_number* n_insert(page_number* curr, page_number** npa);
word* w_insert(word* curr, word** nw, int i);

void n_print(page_number* curr, word* the_word);
void w_print(word* curr);

word* whead = NULL;
page_number* nhead  = NULL;

int main(){
    char w[30];
    int n;
    while( scanf("%s%d",w,&n) != EOF ){
        char* _w = (char*)malloc(30 * sizeof(char));
        word* curr = whead;
        bool same = false;
        while( curr){
            if( !strcmp(curr->initial,w))       same = true;
            curr = curr->next;
        }
        for( int i = 0;i < 30; i ++)        *(_w + i) = *(w + i);
        word* nword = (word*)malloc(sizeof(word));
        nword->initial = _w;
        if( !same){
            w_insert(whead,&nword,0);
        }

        page_number* npagenumber = (page_number*)malloc(sizeof(page_number));
        npagenumber->number = n;
        npagenumber->the_word = nword;
        n_insert(nhead, &npagenumber);
    }
    w_print(whead);
    return 0;
}

page_number* n_insert(page_number* curr, page_number** npa){
    if( !nhead){
        nhead = (*npa);
        ((*npa))->next = NULL;
        return NULL;
    }
    if( (*npa)->number < nhead->number){
        (*npa)->next = nhead;
        nhead = (*npa);
        return NULL;
    }
    page_number* temp = NULL;
    if( !curr)      return NULL;
    temp = n_insert(curr->next,npa);
    if( (*npa)->number > curr->number){
        if( !temp){
            curr->next = (*npa);
            (*npa)->next = temp;
            return curr;
        }
        if( (*npa)->number < temp->number){
            curr->next = (*npa);
            (*npa)->next = temp;
        }
    }
    return curr;
}

word* w_insert(word* curr, word** nw, int i){
    if( !whead){
        whead = (*nw);
        ((*nw))->next = NULL;
        return NULL;
    }
    if(curr == whead && *( (*nw)->initial + i) < *(curr->initial + i)){
        (*nw)->next = whead;
        whead = (*nw);
        return NULL;
    }
    if( i > 29)     return NULL;
    word* temp = NULL;
    if( !curr)      return NULL;
    if( *( (*nw)->initial + i) == *(curr->initial + i)){
        w_insert(curr,nw,i + 1);
        return curr;
    }
    temp = w_insert(curr->next,nw,i);
    if( *( (*nw)->initial + i) > *(curr->initial + i)){
        if( !temp){
            curr->next = (*nw);
            (*nw)->next = temp;
            return curr;
        }
        if( *( (*nw)->initial + i) < *(temp->initial + i)){
            curr->next = (*nw);
            (*nw)->next = temp;
        }
    }
    return curr;
}

void n_print(page_number* curr, word* the_word){
    if( !curr)      return;
    if( !strcmp(curr->the_word->initial,the_word->initial))
        printf("%d ",curr->number);
    n_print(curr->next,the_word);
    return;
}

void w_print(word* curr){
    if( !curr)      return;
    printf("%s\n",curr->initial);
    n_print(nhead,curr);
    printf("\n");
    w_print(curr->next);
    return;
}