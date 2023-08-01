#include <iostream>
#include <vector>
using namespace std;
using Iter = vector<int>::iterator;
void merge_sort(Iter L, Iter R);
void merge(Iter L, Iter M, Iter R);

int main(){
    vector<int> arr(10, 0);
    for(int i = 0; i < 10; i++){
        cin>>arr[i];
    }
    vector<int>::iterator L = arr.begin();
    Iter R = arr.end();
    merge_sort(L, R);
    for(auto i:arr){
        cout<<i<<" ";
    }
}

void merge_sort(Iter L, Iter R) {
  if (L+1 >= R)    return;
  Iter M = L + (R - L) / 2;
  merge_sort(L, M);
  merge_sort(M, R);
  merge(L, M, R);
}

void merge(Iter L, Iter M, Iter R) {
  static vector<int> buff;
  buff.clear();
  Iter i = L, j = M;
  while (i != M && j != R) {
    if (*i < *j) {
      buff.emplace_back(*i), i++;
    } else {
      buff.emplace_back(*j), j++;
    }
  }
  for (; i != M; i++) buff.emplace_back(*i);
  for (; j != R; j++) buff.emplace_back(*j);
  copy(buff.begin(), buff.end(), L);
}
