# include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dequeue(ll now, vector<vector<ll>>& adj, vector<bool>& vis, vector<ll>& level, list<ll>& q){
    for(auto i:adj[now]){
        if(vis[i])  continue;
        q.push_back(i);
        vis[i] = true;
        level[i] = level[now] + 1;
    }

    // cout<<q.front()<<": "<<level[q.front()]<<" , ";

    q.pop_front();
    if(q.size())    dequeue(q.front(),adj,vis,level,q);
    // else    cout<<"  .."<<endl;
}

void bfs(ll now, vector<vector<ll>>& adj, vector<bool>& vis, vector<ll>& level){
    if(!adj[now].size())    return;
    list<ll> q;
    vis[now] = true;
    q.push_back(now);
    dequeue(now,adj,vis,level,q);
}

int main(){
    ll N1, N2, M;  cin >> N1 >> N2 >> M;
    vector<vector<ll>> adj(N1+N2+1);
    vector<bool> vis(N1+N2+1, false);
    vector<ll> level(N1+N2+1, 0);
    while(M--){
        ll u, v;   cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bfs(1,adj,vis,level);
    bfs(N1+N2,adj,vis,level);
    ll max_d1 = 0, max_d2 = 0;
    for(ll i = 1; i <= N1; i++){
        if(level[i] > max_d1)   max_d1 = level[i];
    }
    for(ll i = N1+1; i <= N1 + N2; i++){
        if(level[i] > max_d2)   max_d2 = level[i];
    }

    // cout<<max_d1<<" || "<<max_d2<<endl;

    cout<<max_d1 + max_d2 + 1<<endl;

    return 0;
}