#include <bits/stdc++.h>
#define nn '\n'
typedef long long ll;
using namespace std;

struct SparseTable {
    int n;
    vector<int> lg;
    vector<vector<int>> dp;

    SparseTable(const vector<int>& a) : n((int) a.size()) {
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        dp.assign(lg[n] + 1, vector<int>(n));
        for (int i = 0; i < n; ++i) {
            dp[0][i] = a[i];
        }
        for (int k = 1; k <= lg[n]; k++) {
            for (int i = 0; i + (1 << k) - 1 < n; ++i) {
                dp[k][i] = min(dp[k - 1][i], dp[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        int k = lg[r - l + 1];
        return min(dp[k][l], dp[k][r - (1 << k) + 1]);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;
    SparseTable table(a);
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << table.query(l, r) << nn;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
