#include <bits/stdc++.h>
using namespace std;

struct listOfRemoved{
    char alphabet;
    int orderOfRemoval;
};

int N, M;
vector<char> S;
vector<listOfRemoved> T;

bool f(int p){
    int j = 0;
    for(int i = 0; i < N;){
        if(T[j].orderOfRemoval <= p)  j++;
        else if(S[i++] == T[j].alphabet)    j++;
        if(j >= M)  return true;
    }
    return false;
}

int binarySearch(int L,int R){
    int M = (L + R) / 2;
    if(L==M)
        return f(M)?M:M+1;
    return f(M)?binarySearch(L,M):binarySearch(M+1,R);
}

int main(){

    cin>>N>>M;
    for(int i = 0; i < N; i++){
        char temp;
        cin>>temp;
        S.push_back(temp);
    }
    for(int i = 0; i < M; i++){
        listOfRemoved temp;
        char c;
        cin>>c;
        temp.alphabet = c;
        temp.orderOfRemoval = 0;
        T.push_back(temp);
    }
    for(int i = 1; i <= M; i++){
        int temp;
        cin>>temp;
        T[temp-1].orderOfRemoval = i;
    }

    cout<<binarySearch(1,M);

    // cout << endl;
    // for(auto i : S){
    //     cout<<i<<' ';
    // }
    // cout << endl;
    // for(auto i : T){
    //     cout<<i.alphabet;
    //     cout<<i.orderOfRemoval<<' ';
    // }
    // cout << endl;
    // for(int i = 0; i < M; i++)
    //     cout << f(i);
    // cout << endl;

}