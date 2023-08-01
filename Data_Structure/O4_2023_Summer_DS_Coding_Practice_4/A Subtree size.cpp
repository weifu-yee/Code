#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>>& parent, vector<int>& subtree, vector<bool>& vis){
    if(vis[node])   return;
    for(auto i:parent[node]){
        dfs(i, parent, subtree, vis);
        subtree[node] += subtree[i];
    }
    vis[node] = true;
}

int main(){
    int n;  cin >> n;
    vector<vector<int>> parent(n+1);
    vector<int> subtree(n+1, 1);
    vector<bool> vis(n+1, false);

    for(int i = 2; i <= n; i++){
        int tmp;    cin >> tmp;
        parent[tmp].push_back(i);
    }
    for(int i = 1; i <= n; i++){
        dfs(i, parent, subtree, vis);
    }
    for(int i = 1; i <= n; i++){
        cout << subtree[i] - 1 << " ";
    }
    cout<<endl;
    
    return 0;
}