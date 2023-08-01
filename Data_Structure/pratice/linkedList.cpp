#include <bits/stdc++.h>
using namespace std;

struct singNode{
    int data;
    singNode* nxt;
};

struct douNode{
    int data;
    douNode* nxt;
    douNode* pre;
};

void singIns(singNode* pre, int data){
    singNode* nd = new singNode;
    nd->data = data;
    nd->nxt = pre->nxt;
    pre->nxt = nd;
}
void singDel(singNode* pre){
    singNode* bye = pre->nxt;
    pre->nxt = bye->nxt;
    delete bye;
}
void douIns(douNode* pre, int data){
    douNode* nd = new douNode, *nex = pre->nxt;
    nd->data = data;
    nd->nxt = nex;
    nd->pre = pre;
    pre->nxt = nd;
    if(nex) nex->pre = nd;
}
void douDel(douNode* bye){
    douNode *pre = bye->pre, *nex = bye->nxt;
    if(pre) pre->nxt = nex;
    if(nex) nex->pre = pre;
    delete bye;
}

int main(){
    list<int> mylist;
    list<int>::iterator it;

    for( int i = 1; i <= 5; ++i){
        mylist.push_back(i);
    }

    it = mylist.begin();
    ++it;

    mylist.insert( it, 10);
    mylist.insert( it, 2, 20);

    --it;

    vector<int> myvector(2,30);
    mylist.insert (it, myvector.begin(), myvector.end());

    cout<<"mylist contains:";
    // for(it = mylist.begin(); it != mylist.end(); ++it)
    //     cout<<" "<<*it;
    for(auto i:mylist)
        cout<<" "<<i;
    cout<<endl;

    return 0;
}
