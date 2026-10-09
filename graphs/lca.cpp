// BEST TEMPLATE EVER
#include <bits/stdc++.h>

#define nn '\n'
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int) (x).size())
#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define rrep(i, a, b) for (int i = (a); i > (b); --i)
#define each(x, a) for (auto& x: a)
#define each2(x, y, a) for (auto& [x, y]: a)
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define un_mp unordered_map
#define un_st unordered_set
#define popcnt __builtin_popcountll

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vstr = vector<string>;
using vll = vector<ll>;
using i128 = __int128_t;

template<class T>
inline istream& operator>>(istream& in, vector<T>& a) {
    for (auto& x: a) in >> x;
    return in;
}
template<class T>
inline ostream& operator<<(ostream& out, const vector<T>& a) {
    for (int i = 0; i < sz(a); ++i) out << a[i] << " \n"[i + 1 == sz(a)];
    return out;
}

inline int msb(ll x) {
    return x ? 63 - __builtin_clzll((ull) x) : -1;
} // старший 1-бит (0 based)
inline int lsb(ll x) {
    return x ? __builtin_ctzll((ull) x) : -1;
} // младший 1-бит (0 based)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const ld PI = acos(-1.0L);
const ld EPS = 1e-9;

template<typename T, typename K>
inline T modpow(T a, K e) {
    T r = 1;
    for (; e; e >>= 1, a = (ull) a * a % MOD)
        if (e & 1) r = (ull) r * a % MOD;
    return r;
}
template<typename T, typename K>
inline T binpow(T a, K e) {
    T r = 1;
    for (; e; e >>= 1, a = a * a)
        if (e & 1) r = r * a;
    return r;
}

void solve();

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << fixed << setprecision(15);
    // freopen("", "r", stdin);
    // freopen("", "w", stdout);
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}

namespace LCA {
    const int LOG = 20;
    void dfs(int v, int p, span<vi> graph, vector<vi>& up, vi& depth) {
        up[v][0] = (p == -1 ? v : p);
        for (int i = 1; i < LOG; ++i) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        for (int u: graph[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v, graph, up, depth);
            }
        }
    }

    int get_lca(int u, int v, const vi& depth, const vector<vi>& up) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; ++i) {
            if ((diff >> i) & 1) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    void solve(int root, span<vi> graph) {
        vector up(graph.size(), vi(LOG));
        vi depth(graph.size(), 0);
        dfs(root, -1, graph, up, depth);
    }
};

namespace fast_LCA {
    void dfs(int v, int p, vi& ord, span<vi> graph, vi& depth, vi& euler_ord, vi& first) {
        ord.pb(v);
        euler_ord.pb(depth[v]);
        if (first[v] == -1) first[v] = sz(euler_ord) - 1;
        for (int u: graph[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v, ord, graph, depth, euler_ord, first);
                ord.pb(v);
                euler_ord.pb(depth[v]);
            }
        }
    }

    int get_lca(int u, int v, span<vi> st, const vi& first, const vi& euler_ord, const vi& ord) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        int i = 31 - __builtin_clz(r - l + 1);
        int idx1 = st[i][l];
        int idx2 = st[i][r - (1 << i) + 1];
        int min_idx = (euler_ord[idx1] < euler_ord[idx2]) ? idx1 : idx2;
        return ord[min_idx];
    }

    void solve(int root, span<vi> graph) {
        vi ord, euler_ord, first(graph.size(), -1), depth(graph.size());
        dfs(root, -1, ord, graph, depth, euler_ord, first);
        int LOG = 32 - __builtin_clz(sz(ord));
        vector st(LOG, vi(sz(ord)));
        for (int i = 0; i < sz(ord); ++i) {
            st[0][i] = i;
        }
        for (int i = 1; i < LOG; ++i) {
            for (int j = 0; j + (1 << i) <= sz(ord); ++j) {
                int idx1 = st[i - 1][j], idx2 = st[i - 1][j + (1 << (i - 1))];
                st[i][j] = (euler_ord[idx1] < euler_ord[idx2] ? idx1 : idx2);
            }
        }
    }
};

void solve() {}
