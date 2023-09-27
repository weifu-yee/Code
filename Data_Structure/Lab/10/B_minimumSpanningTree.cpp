//minimumSpanningTree
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

    int find_root(int x){
        if(x == parent[x])  return x;
        else return parent[x] = find_root(parent[x]);
    }
    bool same(int x, int y){
        return find_root(x) == find_root(y);
    }
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

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n, m;   cin >> n >> m;
    DisjointSet dsu(n);
    vector<tuple<int, int, int>> edge;
    while(m--){
        int u, v, w;    cin >> u >> v >> w;
        edge.push_back(make_tuple(w, u, v));
    }
    sort(edge.begin(), edge.end());
    long long ans = 0;
    for(auto [w, u, v]: edge){
        if(dsu.find_root(u) == dsu.find_root(v))
            continue;
        ans += w;
        dsu.uni(u, v);
    }
    cout << ans;
    return 0;
}