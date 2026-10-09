#include <bits/stdc++.h>
#define nn '\n'
typedef long long ll;
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& i: a) cin >> i;
    vector<int> lg(n + 1);
    for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
    vector dp(lg[n] + 1, vector<int>(n)); // dp[i][j] - i - длина отрезка; j - его левый конец
    for (int i = 0; i < n; ++i) {
        dp[0][i] = a[i];
    }
    for (int k = 1; k <= lg[n]; k++) {
        for (int i = 0; i + (1 << k) - 1 < n; ++i) {
            dp[k][i] = min(dp[k - 1][i], dp[k - 1][i + (1 << (k - 1))]);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int k = lg[r - l + 1];
        cout << min(dp[k][l], dp[k][r - (1 << k) + 1]) << nn;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
