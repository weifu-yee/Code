#include <bits/stdc++.h>
using namespace std;

constexpr int A = 998244353, B = 1E9 + 7;

vector<int> build(const string& s) {
	int n = s.size();
	vector<int> a(n + 1);
	for(int i = 0; i < n; i++) {
		a[i + 1] = (1LL * a[i] * A + s[i]) % B;
	}
	return a;
}
 4
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, q;
	cin >> n >> q;
	vector<vector<int>> S(n);
	for(int i = 0; i < n; i++) {
		int L;
		string s;
		cin >> L >> s;
		S[i] = build(s);
	}
	auto f = [&](int x, int a, int b, int c, int d) {
		return S[a][x] == S[b][x] && S[b][x] == S[c][x] && S[c][x] == S[d][x];
	};
	while(q--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--, b--, c--, d--;
		int ok = 0, ng = min({S[a].size(), S[b].size(), S[c].size(), S[d].size()});
		while(ng - ok > 1) {
			int mid = (ok + ng) / 2;
			if(f(mid, a, b, c, d)) {
				ok = mid;
			} else {
				ng = mid;
			}
		}
		cout << ok << "\n";
	}
	return 0;
}