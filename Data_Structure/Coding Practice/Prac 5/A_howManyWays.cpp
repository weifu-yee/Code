#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;

void solve(){
    int n, m;   cin >> n >> m;
    vector<vector<int>> rev_adj(n+1);
    while(m--){
        int u, v;   cin >> u >> v;
        rev_adj[v].push_back(u);
    }

    auto topoSort = [&](void){
        vector<int> outdegree(n+1, 0);
        vector<int> dp(n+1, 0);     dp[n] = 1;
        for(int i = 1; i <= n; i++){
            for(auto u: rev_adj[i]){
                outdegree[u]++;
            }
        }

        queue<int> q;
        for(int i = 1; i <= n; i++)
            if(outdegree[i] == 0)
                q.push(i);

        while(!q.empty()){
            int v = q.front();  q.pop();
            for(auto u: rev_adj[v]){
                dp[u] += dp[v];
                dp[u] %= mod;
                if(--outdegree[u] == 0)
                    q.push(u);
            }
        }

        cout << dp[1];
    };

    topoSort();
}

int main(){
    solve();
    return 0;
}