#include <bits/stdc++.h>
using namespace std;

int MIS(int v, vector<vector<int>>& adjlist, vector<int>& vis, vector<int>& m_size){
    if(vis[v])  return 0;

    vis[v] = true;
    int skip = 0,keep = 1;
    for(auto i:adjlist[v])
        skip += MIS(i, adjlist, vis, m_size);
    for(auto i:adjlist[v])
        for(auto j:adjlist[i]){
            if(j == v)  continue;
            keep += m_size[j];
        }
    m_size[v] = max(skip, keep);
    return m_size[v];
}

int main(){
    int n;  cin >> n;
    vector<vector<int>> adjlist(n+1);
    vector<int> vis(n+1, false);
    vector<int> m_size(n+1, 0);

    for(int i = 0; i < n-1; i++){
        int a, b;   cin >> a >> b;
        adjlist[a].push_back(b);
        adjlist[b].push_back(a);
    }

    cout << MIS(1, adjlist, vis, m_size) << endl;
    return 0;
}