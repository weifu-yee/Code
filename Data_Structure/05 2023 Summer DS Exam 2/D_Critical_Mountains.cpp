# include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void dequeue(ll now, vector<vector<ll>>& adj, vector<ll>& level, vector<bool>& vis, list<ll>& q){
    for(auto i:adj[now]){
        if(vis[i])  continue;
        q.push_back(i);
        level[i] = level[now] + 1;
        vis[i] = true;
    }

    // cout<<q.front()<<": "<<level[q.front()]<<" , ";

    q.pop_front();
    if(q.size())    dequeue(q.front(),adj,level,vis,q);

    // else    cout<<"  .."<<endl;
}

void bfs(ll now, vector<vector<ll>>& adj, vector<ll>& level, vector<bool>& vis){
    if(!adj[now].size())    return;
    list<ll> q;
    q.push_back(now);
    vis[now] = true;
    dequeue(now,adj,level,vis,q);
}

int main(){
    ll n, m;   cin >> n >> m;
    vector<vector<ll>> adj(n+1);
    vector<ll> leveln(n+1, 0);
    vector<ll> level1(n+1, 0);
    vector<bool> visn(n+1, false);
    vector<bool> vis1(n+1, false);
    while(m--){
        ll u, v;   cin >> u >> v;
        if(u > v)
            adj[u].push_back(v);
        else
            adj[v].push_back(u);
    }

    bfs(n, adj, leveln, visn);
    bfs(1, adj, level1, vis1);

    vector<vector<ll>> levelTH(n);
    for(ll i = 1; i <= n; i++){
        levelTH[leveln[i]].push_back(i);
    }
    vector<vector<ll>>::iterator it = --levelTH.end();
    vector<ll> printN;
    while(it-- != levelTH.begin()){
        if((*it).size() == 1)  printN.push_back((*it)[0]);
    }

    levelTH.clear();
    for(ll i = 1; i <= n; i++){
        levelTH[level1[i]].push_back(i);
    }
    it = levelTH.begin();
    vector<ll> print1;
    ll k = 0;
    while(it++ != levelTH.end()){
        if((*it).size() == 1){
            if(printN[k] == (*it)[0]){
                cout<<(*it)[0]<<" ";
                k++;
            }
            else if(printN[k] < (*it)[0])   k++;
        }
    }

    return 0;
}