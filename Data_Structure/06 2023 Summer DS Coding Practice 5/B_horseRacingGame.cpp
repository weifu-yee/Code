#include<bits/stdc++.h>
using namespace std;

int main(){
    int N, M;   cin >> N >> M;
    vector<vector<int>> adj(N+1);
    while(M--){
        int u, v;   cin >> u >> v;
        adj[u].push_back(v);
    }

    auto topoSort = [&](void){
        vector<int> indegree(N+1, 0);
        for(int i = 1; i <= N; i++){
            for(auto v: adj[i]){
                indegree[v]++;
            }
        }
        set<int> s;
        vector<int> ans;
        for(int i = 1; i <= N; i++)
            if(indegree[i] == 0)
                s.insert(i);

        while(!s.empty()){
            auto u = s.lower_bound(0);
            ans.push_back(*u);
            for(auto v: adj[*u]){
                indegree[v]--; 
                if(indegree[v] == 0){
                    s.insert(v);
                }
            }
            s.erase(u);
        }
        if(ans.size() != N){
            cout << "-1";
            return;
        }

        for(auto i: ans)
            cout << i << ' ';
    };

    topoSort();
}