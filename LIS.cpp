class BIT {
    public:
    int n;
    vector<int> tree;
    
    BIT(int _n) {
        n = _n + 1;
        tree.assign(n + 1, 0);
    }
 
    void update(int x, int v) {
        ++x;
        for (; x <= n; x += x&-x)
            tree[x] = max(tree[x], v);
    }
 
    int read(int x) {
        ++x;
        int sum = 0;
        for (; x > 0; x -= x&-x)
            sum = max(sum, tree[x]);
        return sum;
    }
};


class Solution {
public:
    
    
    // A. LIS (>=) based on BIT on compressed array
    vector<int> lisA(vector<int>& ar) {
        const int n = ar.size();
        
        // compress ar
        vector<pair<int, int> > a;
        for (int i = 0; i < n; i++) a.push_back({ar[i], i});
        sort(a.begin(), a.end());
        int v = 1;
        for (int i = 0, j = 0; i < n; ++v) {
            while (j < n && a[i].first == a[j].first) ++j;
            while (i < j) ar[a[i++].second] = v;
        }
        
        vector<int> res(n, 0);
        BIT bit(n);
        for (int i = 0; i < n; i++) {
            res[i] = bit.read(ar[i]) + 1;
            bit.update(ar[i], res[i]);
        }        
        
        // LIS ending at each index
        return res;
    }
    
    
    // B. LIS (>=)
    int lisB(vector<int>& ar) {
        const int n = ar.size();
        vector<int> dp;
        // vector<int> res(n, 0);
        
        for (int i = 0; i < n; i++) {
            if (dp.empty() || dp.back() <= ar[i]) {
                dp.push_back(ar[i]);
                // res[i] = dp.size();
            } else {
                auto it = upper_bound(begin(dp), end(dp), ar[i]);
                *it = ar[i];
                // res[i] = it - dp.begin() + 1;
            }
        }
        
        return dp.size();
    }
    
    
    
    // C. LIS (>)
    int lisC(vector<int>& ar) {
        const int n = ar.size();
        vector<int> dp;
        // vector<int> res(n, 0);
        
        for (int i = 0; i < n; i++) {
            if (dp.empty() || dp.back() < ar[i]) {
                dp.push_back(ar[i]);
                // res[i] = dp.size();
            } else {
                auto it = lower_bound(begin(dp), end(dp), ar[i]);
                *it = ar[i];
                // res[i] = it - dp.begin() + 1;
            }
        }
        
        return dp.size();
    }
    
};
