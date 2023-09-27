//addingEdges
#include<bits/stdc++.h>
using namespace std;

struct DisjointSet{
    int _n;
    vector<int> parent, size;

    DisjointSet(int n) :_n(n){
        parent.resize(n + 1);
        size.resize(n + 1, 1);
        iota(parent.begin(), parent.end(), 0);
    }

    int find_root(int x);
    bool same(int x, int y);
    int get_size(int x){
        return size[find_root(x)];
    }
    int uni(int x, int y){
        int rx = find_root(x);  int ry = find_root(y);
        if(rx == ry)    return 0;
        if(size[rx] > size[ry]) swap(rx, ry);
        parent[rx] = ry;
        size[ry] += size[rx];
        _n --;
        return size[ry];
    }
};

int DisjointSet::find_root(int x){
    if(x == parent[x])  return x;
    else return parent[x] = find_root(parent[x]);
}
bool DisjointSet::same(int x, int y){
    return find_root(x) == find_root(y);
}

int main(){
    int n, m;   cin >> n >> m;
    DisjointSet dsu(n);
    priority_queue<int> pq;
    vector<pair<int, int>> ans;
    while(m--){
        int u, v;   cin >> u >> v;
        pq.push(dsu.uni(u, v));
        ans.push_back(std::make_pair(dsu._n, pq.top()));
    }
    for(auto i: ans){
        cout << i.first << ' ' << i.second << endl;
    }
    return 0;
}