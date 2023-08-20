#include <bits/stdc++.h>
using namespace std;

typedef struct Node{
    string data;
    Node *left, *right;
    Node(string data){
        this->data = data;
        left = right = NULL;
    }
    
}Node;

Node* build(int l, int r, int pos, vector<string>& pre, vector<string>& in){
    Node* root = new Node(pre[pos]);
    root->left = build(l, pos-1, );
    build(l, r, root->right);
}

int main(){
    int t;  cin >> t;
    while(t--){
        int n;  cin >> n;
        vector<string> pre(n), in(n), post(n);
        for(int i = 0; i < n; i++)  cin >> pre[i];
        for(int i = 0; i < n; i++)  cin >> in[i];
        int pos = 0;

    }
    Node *root = new Node(1);

    return 0;
}