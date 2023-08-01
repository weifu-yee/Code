#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct element{
    ll value;
    ll frontSmall;
    ll backBig;
};

using Iter = vector<element>::iterator;

ll rightRest, leftToken;
ll n;
vector<element> arr;

void merge(Iter L, Iter M, Iter R) {
    static vector<element> buff;
    buff.clear();
    Iter i = L, j = M;
    leftToken = 0;  rightRest = 0;
    for(Iter k = j; k != R; k++){
        rightRest ++;
    }
    while (i != M && j != R) {
        if ((*i).value < (*j).value) {
            (*i).backBig += rightRest;
            buff.emplace_back(*i), i++;
            leftToken ++;
        } else {
            (*j).frontSmall += leftToken;
            buff.emplace_back(*j), j++;
            rightRest --;
        }
    }
    for (; i != M; i++){
        buff.emplace_back(*i);
    }
    for (; j != R; j++){
        (*j).frontSmall += leftToken;
        buff.emplace_back(*j);
    }
    copy(buff.begin(), buff.end(), L);
}

void merge_sort(Iter L, Iter R) {
    if (L+1 >= R)    return;
    Iter M = L + (R - L) / 2;
    merge_sort(L, M);
    merge_sort(M, R);
    merge(L, M, R);
}

ll numOfTuple(){
    ll ans = 0;
    for(auto i:arr){
        ans += i.frontSmall * i.backBig;
    }
    return ans;
}

int main(){
    cin>>n;
    for(ll i = 0; i < n; i++){
        ll temp;
        cin>>temp;
        arr.push_back({temp,0,0});
    }

    merge_sort(arr.begin(), arr.end());
    cout<<numOfTuple()<<endl;
}