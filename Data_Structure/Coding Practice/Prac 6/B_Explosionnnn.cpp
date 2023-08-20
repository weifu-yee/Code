#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;  cin >> N >> M;
    priority_queue<pair<int, int>> pq0;
    priority_queue<pair<int, int>> pq1;
    int ans = 0;

    auto loli = [&](int i, int m, int c){
        if(c >= M)  pq1.push(std::make_pair(m, c));
        else    pq0.push(std::make_pair(c, m));
    };

    auto burst = [&](int m){
        M -= m;
        pq1.pop();
        ans++;
    };

    auto asign = [&](){
        auto top = pq1.top();
        burst(top.first);
        while(!pq0.empty()){
            auto t = pq0.top();
            if(t.first < M)    break;
            pq1.push(std::make_pair(t.second, t.first));
            pq0.pop();
        }
    };

    for(int i = 1; i <= N; i++){
        int m, c;   cin >> m >> c;
        loli(i, m, c);
    }
    
    while(M > 0 && !pq1.empty()){
        asign();
    }

    if(ans == 0 || M > 0)    cout << "-1";
    else    cout << ans;

    return 0;
}