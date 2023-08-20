#include <iostream>
#include <vector>
using namespace std;
#define ll long long 

bool binarySearch(vector<ll> &arr, ll query);

int main() {
	int n, m;cin>>n>>m;
	vector<ll> arr(n);
	for(auto &x : arr) cin>>x;
	while(m--) {
		ll q; cin>>q;
		if(!binarySearch(arr, q)) cout<<'N';
		else cout<<'Y';
		cout<<' ';
	}
	return 0;
}

bool binarySearch(vector<ll> &arr, ll query){
    int l = 0, r = arr.size() - 1 , mid;
    while(l <= r){
        mid = (l + r) / 2;
        if(arr[mid] == query)   return true;
        else if(arr[mid] < query) l = mid + 1;
        else r = mid - 1;
    }
    return false;
}