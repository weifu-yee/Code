#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> arr;

ll merge(int L, int M, int R) {
  ll inversions = 0;
  static vector<ll> buff;
  buff.clear();
  int i = L, j = M + 1;
  while(i <= M && j <= R){
    if(arr[i] <= arr[j]){
        buff.push_back(arr[i++]);
    }else{
        buff.push_back(arr[j++]);
        inversions += (M - i + 1);
    }
  }
  for(;i<=M;++i)    buff.push_back(arr[i]);
  for(;j<=R;++j)    buff.push_back(arr[j]);
  for(int k=L; k<= R; k++)    arr[k] = buff[k - L];
  return inversions;
}

ll merge_sort(int L, int R) {
    ll inversions = 0;
    if(L>=R)    return 0;
    int M = (L + R)/2;
    inversions += merge_sort(L,M);
    inversions += merge_sort(M+1,R);
    inversions += merge(L,M,R);
    return inversions;
}

int main(){
    int n;
    cin>>n;
    while(n--){
        ll d;
        cin>>d;
        arr.push_back(d);
    }
    cout<<merge_sort(0,arr.size()-1)<<endl;
    return 0;
}

