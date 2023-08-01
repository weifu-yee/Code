#include <bits/stdc++.h>
using namespace std;

vector<list<int>> arr;
vector<list<int>::iterator> pos;

int main(){
    int t;
    cin>>t;
    while(t--){
        list<int> li;
        int n, q;
        cin>>n>>q;
        for(int i = 0; i < n;) li.push_back(++i);

        pos.clear();
        auto it = li.begin();
        for(int i = 0; i < n; ++i) pos.push_back(it++);

        for(int i = 0; i < q; ++i){
            char c;   cin>>c;
            int x;  cin>>x;
                li.erase(pos[x-1]);
                if(c == 'H'){
                    li.push_front(x);
                    pos[x-1] = li.begin();
                }else{
                    li.push_back(x);
                    pos[x-1] = --li.end();
                }
        }
        arr.push_back(li);
    }
    for(auto li:arr){
        for(auto i:li) cout<<i<<" ";
        cout<<endl;
    }
    return 0;
}