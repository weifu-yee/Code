#include<bits/stdc++.h>
using namespace std;

int main(){
    int N;  cin >> N;
    int Q;  cin >> Q;
    vector<set<int>> v(N+1);

    auto shakesHands = [&](int x, int y){
        v[x].insert(y);
        v[y].insert(x);
    };
    auto asking = [&](int x, int y){
        if(v[x].count(y))   cout << "yes";
        else    cout << "no";
        cout << endl;
    };

    while(Q--){
        int op, x, y;   cin >> op >> x >> y;
        if(op == 1) shakesHands(x, y);
        else if(op == 2)    asking(x, y);
    }

    return 0;
}