#include<bits/stdc++.h>
using namespace std;
 
int main() {
    int n; 
    cin >> n;
 
    if (n == 1) {
        cout << 1 << '\n';
        return 0;
    }
 
    list<int> li;
    for (int i = 1; i <= n; i++)
        li.push_back(i);
    
    auto it = li.begin();
    it++;
    for (int i = 0; i < n; i++) {
        cout << *it << ' ';
        it = li.erase(it);
 
        if (it == li.end()) it = li.begin(); 
        it++;
        if (it == li.end()) it = li.begin(); 
    }
}