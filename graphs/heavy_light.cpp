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

template<typename Segtree>
struct HLD {
    int n;
    span<vi> graph;
    vi size, parent, depth, heavy, pos, head, vals;
    int timer = 0;
    Segtree tr;

    HLD(int root, span<vi> graph, vi vert_vals)
        : n(sz(graph))
        , graph(graph)
        , size(n + 1, 0)
        , parent(n + 1, -1)
        , depth(n + 1, 0)
        , heavy(n + 1, -1)
        , pos(n + 1, -1)
        , head(n + 1, -1)
        , vals(n + 1) {
        dfs1(root, -1);
        dfs2(root, -1, root);
        for (int i = 1; i <= n; ++i) {
            vals[pos[i]] = vert_vals[i];
        }
        tr = Segtree(vals);
    }

    void dfs1(int v, int p) {
        size[v] = 1;
        parent[v] = p;
        int mx_child = 0;
        for (int u: graph[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs1(u, v);
                size[v] += size[u];
                if (size[u] > mx_child) {
                    mx_child = size[u];
                    heavy[v] = u;
                }
            }
        }
    }

    void dfs2(int v, int p, int cur_head) {
        pos[v] = timer++;
        head[v] = cur_head;
        if (heavy[v] != -1) {
            dfs2(heavy[v], v, cur_head);
        }
        for (int u: graph[v]) {
            if (u != p && u != heavy[v]) {
                dfs2(u, v, u);
            }
        }
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] >= depth[head[v]]) {
                u = parent[head[u]];
            } else {
                v = parent[head[v]];
            }
        }
        if (depth[u] >= depth[v]) {
            return v;
        } else {
            return u;
        }
    }

    int query(int u, int v) {
        int res = 0;
        while (head[u] != head[v]) {
            if (depth[head[u]] >= depth[head[v]]) {
                res += tr.query(pos[head[u]], pos[u]);
                u = parent[head[u]];
            } else {
                res += tr.query(pos[head[v]], pos[v]);
                v = parent[head[v]];
            }
        }
        if (depth[u] > depth[v]) swap(u, v);
        res += tr.query(pos[u], pos[v]);
        return res;
    }

    void update(int u, int v, int val) {
        while (head[u] != head[v]) {
            if (depth[head[u]] >= depth[head[v]]) {
                tr.update(pos[head[u]], pos[u], val);
                u = parent[head[u]];
            } else {
                tr.update(pos[head[v]], pos[v], val);
                v = parent[head[v]];
            }
        }
        if (depth[u] > depth[v]) swap(u, v);
        tr.update(pos[u], pos[v], val);
    }
};

void solve() {}
