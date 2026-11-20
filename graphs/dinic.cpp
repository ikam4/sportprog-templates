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

template<class T> inline istream& operator>>(istream& in, vector<T>& a) {
    for (auto& x: a) in >> x;
    return in;
}
template<class T> inline ostream& operator<<(ostream& out, const vector<T>& a) {
    for (int i = 0; i < sz(a); ++i) out << a[i] << " \n"[i + 1 == sz(a)];
    return out;
}

inline int msb(ll x) { return x ? 63 - __builtin_clzll((ull) x) : -1; } // старший 1-бит (0 based)
inline int lsb(ll x) { return x ? __builtin_ctzll((ull) x) : -1; } // младший 1-бит (0 based)

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const ld PI = acos(-1.0L);
const ld EPS = 1e-9;

template<typename T, typename K> inline T modpow(T a, K e) {
    T r = 1;
    for (; e; e >>= 1, a = (ull) a * a % MOD)
        if (e & 1) r = (ull) r * a % MOD;
    return r;
}
template<typename T, typename K> inline T binpow(T a, K e) {
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

template<typename T> class Dinic {
public:
    int n;
    vector<vi> graph;
    vector<pair<int, T>> edges;

    Dinic(span<const vector<pair<int, T>>> input_graph, bool directed = true)
        : n(sz(input_graph))
        , graph(n) {
        for (int v = 0; v < n; ++v) {
            for (auto [u, cap]: input_graph[v]) {
                if (directed) {
                    add_edge(v, u, cap);
                } else if (v < u) {
                    add_edge(v, u, cap, cap);
                }
            }
        }
    }

    T maxflow(int s, int t) {
        if (s == t) return T{0};
        vi level(n, -1);
        T flow{0};
        while (bfs(s, t, level)) {
            vi ptr(n, 0);
            while (T pushed = dfs(s, t, numeric_limits<T>::max(), level, ptr)) {
                flow += pushed;
            }
        }
        return flow;
    }

    void add_edge(int v, int u, T cap, T rev_cap = T{0}) {
        int id = sz(edges);
        edges.eb(u, cap);
        edges.eb(v, rev_cap);
        graph[v].pb(id);
        graph[u].pb(id ^ 1);
    }

    bool bfs(int s, int t, vi& level) {
        queue<int> q;
        fill(all(level), -1);
        q.push(s);
        level[s] = 0;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id: graph[v]) {
                auto [u, cap] = edges[id];
                if (cap > 0 && level[u] == -1) {
                    level[u] = level[v] + 1;
                    q.push(u);
                }
            }
        }
        return level[t] != -1;

    }

    T dfs(int v, int t, T limit, const vi& lvl, vi& ptr) {
        if (v == t) return limit;
        for (; ptr[v] < sz(graph[v]); ++ptr[v]) {
            int id = graph[v][ptr[v]];
            auto& [u, cap] = edges[id];
            if (cap <= T{0} || lvl[u] != lvl[v] + 1) continue;
            T pushed = dfs(u, t, min(limit, cap), lvl, ptr);
            if (pushed == T{0}) continue;
            cap -= pushed;
            edges[id ^ 1].second += pushed;
            return pushed;
        }
        return T{0};
    }
};

void solve() {}
