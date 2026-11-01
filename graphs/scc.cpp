// BEST TEMPLATE EVER
#include <bits/stdc++.h>
#include <utility>

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

namespace scc {
    void dfs1(int v, vector<bool>& used, vi& ord, span<vi> graph) {
        used[v] = true;
        for (int u: graph[v]) {
            if (!used[u]) {
                dfs1(u, used, ord, graph);
            }
        }
        ord.pb(v);
    }

    void dfs2(int v, vi& comp, int timer, span<vi> graph) {
        comp[v] = timer;
        for (int u: graph[v]) {
            if (comp[u] == -1) {
                dfs2(u, comp, timer, graph);
            }
        }
    }

    vector<vi> get_dag(span<int> comp, int comp_cnt, span<vi> graph) {
        vector<vi> new_graph(comp_cnt);
        for (int v = 0; v < sz(comp); ++v) {
            if (comp[v] == -1) continue;
            for (int u: graph[v]) {
                if (comp[u] != comp[v]) {
                    new_graph[comp[v]].pb(comp[u]);
                }
            }
        }
        for (int i = 0; i < comp_cnt; ++i) {
            sort(all(new_graph[i]));
            new_graph[i].erase(unique(all(new_graph[i])), new_graph[i].end());
        }
        return new_graph;
    }

    pair<vector<vi>, vi> solve(span<vi> graph, span<vi> rev_graph) {
        vector<bool> used(graph.size(), false);
        vi ord;
        for (int u = 0; u < sz(graph); ++u) {
            if (!used[u]) {
                dfs1(u, used, ord, graph);
            }
        }
        int timer = 0;
        vi comp(graph.size(), -1);
        for (int u = sz(ord) - 1; u >= 0; --u) {
            int v = ord[u];
            if (comp[v] == -1) {
                dfs2(v, comp, timer++, rev_graph);
            }
        }
        vector<vi> dag = get_dag(comp, timer, graph);
        return {dag, comp};
    }
};

void solve() {}
