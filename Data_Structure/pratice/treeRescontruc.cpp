#include <iostream>
#include <vector>
#include <functional>
using namespace std;

struct node {
    node *l = NULL, *r = NULL;
    int val;
    node(int x) : val(x) {}
};

void solve() {
    int n;
    cin >> n;
    vector<int> pre(n), in(n), pos(n + 5);
    for(int i = 0; i < n; ++i) {
        cin >> pre[i];
    }
    for(int i = 0; i < n; ++i) {
        cin >> in[i];
        pos[in[i]] = i;
    }

    function<node*(int, int)> build = [&](int l, int r) {
        if(l > r) {
            return (node*)(NULL);
        }
        static int now = 0;
        node *res = new node(pre[now++]);
        res->l = build(l, pos[res->val] - 1);
        res->r = build(pos[res->val] + 1, r);
        return res;
    };

    function<void(node*)> post = [&](node *t) {
        if(!t) return;
        post(t->l);
        post(t->r);
        cout << t->val << ' ';
    };
    
    node *t = build(0, n - 1);
    post(t);
}

int main() {
    solve();
}