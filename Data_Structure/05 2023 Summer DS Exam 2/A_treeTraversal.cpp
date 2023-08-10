# include <bits/stdc++.h>
using namespace std;

class Node{
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;

    Node(int v){
        val = v;
        left = NULL;
        right = NULL;
        parent = NULL;
    }
};

int depth = 0;
int m_depth = 0;

void pre(Node* now){
    if(!now)    return;
    cout << now->val << " ";
    depth ++;
    pre(now->left);
    pre(now->right);
    if(depth > m_depth)     m_depth = depth;
    depth --;
}

int main(){
    int N;    cin >> N;
    vector<Node*> treePos(N+1, NULL);

    for(int i = 1; i <= N; i++){
        Node* root;
        if(!treePos[i]){
            root = new Node(i);
            treePos[i] = root;
        }else{
            root = treePos[i];
        }
        int l, r;   cin >> l >> r;
        if(l == -1)     root->left = NULL;
        else if(treePos[l])     root->left = treePos[l];
        else{   
            root->left = new Node(l);
            treePos[l] = root->left;
        }
        if(r == -1)     root->right = NULL;
        else if(treePos[r])     root->right = treePos[r];
        else{   
            root->right = new Node(r);
            treePos[r] = root->right;
        }
        if(l != -1)     treePos[l]->parent = root;
        if(r != -1)     treePos[r]->parent = root;
    }

    Node *ROOT = treePos[1], *v = ROOT;
    while(1){
        v = v->parent;
        if(!v)  break;
        ROOT = v;
    }

    pre(ROOT);
    cout << endl << m_depth << endl;

    // for(auto i:treePos){
    //     if(!i)  continue;
    //     cout << i->val << " ";
    // }

    return 0;
}