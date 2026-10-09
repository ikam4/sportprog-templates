// BEST TEMPLATE EVER
#include <bits/stdc++.h>

#include <algorithm>

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

struct DSU {
    vector<int> parent;
    vector<int> size;
    DSU(int n)
        : parent(n + 1)
        , size(n + 1, 1) {
        for (int i = 0; i <= n; ++i) {
            parent[i] = i;
        }
    }
    int find_set(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find_set(parent[u]);
    }
    bool union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) {
                swap(a, b);
            }
            parent[b] = a;
            size[a] += size[b];
            return true;
        }
        return false;
    }
};

ll kruskal(int n, span<array<int, 3>> edges) {
    DSU dsu(n);
    // vector<pii> mst_edges;
    int comps = n;
    ll total = 0;
    ranges::sort(edges, [](const array<int, 3>& lhs, const array<int, 3>& rhs) { return lhs[2] < rhs[2]; });
    for (auto [u, v, w]: edges) {
        if (dsu.union_sets(u, v)) {
            total += w;
            comps--;
            // mst_edges.eb(u, v);
        }
    }
    if (comps != 1) {
        return -1;
    }
    return total;
}

ll prim(span<vector<pii>> graph) {
    vi min_edge(sz(graph), INF);
    // vi parent(sz(graph), -1);
    // vector<pii> mst_edges;
    vector<bool> used(sz(graph), false);
    priority_queue<pii, vector<pii>, greater<>> q;
    ll total = 0;
    int count = 0;
    min_edge[0] = 0;
    q.emplace(0, 0);
    while (!q.empty()) {
        auto [w, v] = q.top();
        q.pop();
        if (w > min_edge[v] || used[v]) continue;
        used[v] = true;
        count++;
        total += w;
        // if (parent[v] != -1) {
        //     mst_edges.eb(parent[v], v);
        // }
        for (auto [u, w2]: graph[v]) {
            if (!used[u] && w2 < min_edge[u]) {
                min_edge[u] = w2;
                // parent[u] = v;
                q.emplace(w2, u);
            }
        }
    }
    if (count < sz(graph)) return -1;
    return total;
}

ll prim_v2(span<vector<pii>> graph) {
    int n = sz(graph);
    vi min_edge(n, INF);
    // vi parent(n, -1);
    // vector<pii> mst_edges;
    vector<bool> used(n, false);
    ll total = 0;
    min_edge[0] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || min_edge[j] < min_edge[v])) {
                v = j;
            }
        }
        if (min_edge[v] == INF) {
            return -1;
        }
        used[v] = true;
        total += min_edge[v];
        // if (parent[v] != -1) {
        //     mst_edges.eb(parent[v], v);
        // }
        for (auto [u, w2]: graph[v]) {
            if (!used[u] && w2 < min_edge[u]) {
                min_edge[u] = w2;
                // parent[u] = v;
            }
        }
    }
    return total;
}

ll boruvka(int n, span<array<int, 3>> edges) {
    int comps = n;
    DSU dsu(n);
    vi min_edge(n + 1);
    // vector<array<int, 3>> mst_edges;
    ll total = 0;
    while (comps > 1) {
        std::ranges::fill(min_edge, -1);
        bool added = false;
        for (int i = 0; i < sz(edges); ++i) {
            auto [u, v, w] = edges[i];
            int root_u = dsu.find_set(u);
            int root_v = dsu.find_set(v);
            if (root_u != root_v) {
                if (min_edge[root_u] == -1 || edges[min_edge[root_u]][2] > w) {
                    min_edge[root_u] = i;
                }
                if (min_edge[root_v] == -1 || edges[min_edge[root_v]][2] > w) {
                    min_edge[root_v] = i;
                }
            }
        }
        for (int i = 1; i <= n; ++i) {
            if (min_edge[i] != -1) {
                auto [u, v, w] = edges[min_edge[i]];
                if (dsu.union_sets(u, v)) {
                    total += w;
                    // mst_edges.pb(edges[min_edge[i]]);
                    --comps;
                    added = true;
                }
            }
        }
        if (!added) break;
    }
    if (comps > 1) return -1;
    return total;
}

void solve() {}
