#include<bits/stdc++.h>
using namespace std;

int main(){
    int N, K;  cin >> N >> K;
    vector<int> L(N+1), R(N+1);
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> end;
    multiset<int> student;
    for(int i = 1; i <= K; i++){
        student.insert(1);
    }
    for(int i = 1; i <= N; i++){
        cin >> L[i];
    }
    for(int i = 1; i <= N; i++){
        int temp;   cin >> temp;
        R[i] = temp;
        end.push(std::make_pair(temp, i));
    }

    int ans = 0;
    while(!end.empty()){
        int i = end.top().second;
        end.pop();
        auto it = student.upper_bound(-1 * L[i]);
        if(it == student.end())     continue;
        student.erase(it);
        student.insert(-1 * R[i]);
        ans++;
    }

    cout << ans;
    return 0;
}