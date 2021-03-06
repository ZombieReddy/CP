#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

#define FOR(i,a,b) for(int _n(b),i(a);i<_n;i++) 
#define REP(i,n) FOR(i,0,n)

void setIO() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
}


const int SIZE = 2;
const int BITS = 30;

struct TNode {
    TNode *child[SIZE] = {};
    int cnt = 0;
    
    void insert(int val) {
        TNode *cur = this;
        cur->cnt++;
        for (int i = BITS; i >= 0; i--) {
            int b = val >> i & 1;
            if (cur->child[b] == nullptr)
                cur->child[b] = new TNode();
            cur = cur->child[b];
            cur->cnt++;
        }
    }

    void remove(int val) {
        TNode *cur = this;
        cur->cnt--;
        for (int i = BITS; i >= 0; i--) {
            int b = val >> i & 1;
            cur = cur->child[b];
            cur->cnt--;
        }
    }
    
    // Max {a[i] ^ val}
    int maxXor(int val) {
        int r = 0;
        TNode *cur = this;
        for (int i = BITS; i >= 0 && cur; i--) {
            int b = 1 - (val >> i & 1);
            if (cur->child[b] && cur->child[b]->cnt) {
                r += 1 << i;
                cur = cur->child[b];
            } else {
                cur = cur->child[1-b];
            }
        }
        return r;
    }
    
    // Count of a[i] ^ val < lim
    int countLess(int val, int lim) {
        int r = 0;
        TNode *cur = this;
        for (int i = BITS; i >= 0 && cur; i--) {
            int bv = val >> i & 1;
            int bl = lim >> i & 1;
            if (bl == 0) {
                cur = cur->child[bv];
                continue;
            } else {
                if (cur->child[bv] != nullptr)
                    r += cur->child[bv]->cnt;
                cur = cur->child[1-bv];
            }
        }
        return r;
    }
    
    // mEx of {ar[i] ^ val}, assuming unique ar[i]
    int mexXor(int val) {
        int r = 0;
        TNode *cur = this;
        for (int i = BITS; i >= 0 && cur; i--) {
            int b = (val >> i & 1);
            if(cur->child[b] == nullptr)
                break;
            if (cur->child[b]->cnt < (1<<i)) {
                cur = cur->child[b];
            } else {
                r += 1 << i;
                cur = cur->child[1-b];
            }
        }
        return r;
    }
};

int main() {
    setIO();
    int t; cin>>t;
    int op, x;
    TNode root;

    while(t--) {
        // https://codeforces.com/contest/817/problem/E
        cin>>op>>x;
        if (op == 1) root.insert(x);
        else if (op == 2) root.remove(x);
        else {
            int lim; cin >> lim;
            cout << root.countLess(x, lim) << "\n";
        }
    }
    
    return 0;
}
