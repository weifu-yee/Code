#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n, m;   cin >> n >> m;
    vector<vector<int>> adj(n+1);
    while(m--){
        int u, v;   cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> max_depth(n+1, 0);
    set<int> inverseSet;
    auto topoSort = [&](void){
        vector<int> indeg(n+1, 0);
        for(int i = 1; i <= n; i++)
            for(auto v: adj[i])
                indeg[v]++;
        queue<int> q;
        for(int i = 1; i <= n; i++)
            if(indeg[i] == 0)
                q.push(i);
        while(!q.empty()){
            int u = q.front();  q.pop();
            for(auto i: adj[u]){
                int d = max_depth[u] + 1;
                if(d > max_depth[i])
                    max_depth[i] = d;
                if(--indeg[i] == 0)
                    q.push(i);
            }
            inverseSet.insert(-1 * max_depth[u]);
        }
    };

    topoSort();
    if(*inverseSet.lower_bound(-1*n) == (n-1) * -1)
        cout << "Yes";
    else
        cout << "No";    
}

int main(){
    solve();
}