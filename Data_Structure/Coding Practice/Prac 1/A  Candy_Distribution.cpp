#include <bits/stdc++.h>
using namespace std;

vector<int> arr;
int n,m;
int Max = 0;

bool check(int x){
    int sum = 0;
    for(auto i:arr)
        sum += ceil((double)i / x);
    return sum <= m;
}

int binaryclip(int L,int R){
    int M = (L + R) / 2;
    if(L==M)
        return check(M)?M:M+1;
    return check(M)?binaryclip(L,M):binaryclip(M+1,R);
}

int main(){
    cin>>n>>m;
    while(n--){
        int x;
        cin>>x;
        Max = max(Max,x);
        arr.push_back(x);
    }
    cout<<binaryclip(1,Max)<<endl;
}