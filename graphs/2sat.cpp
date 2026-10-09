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

struct TWO_SAT {
    int n;
    vector<vi> graph, graph_rev;
    vector<bool> used, ans;
    vi ord, comp;

    TWO_SAT(int n)
        : n(n)
        , graph(2 * n)
        , graph_rev(2 * n)
        , used(2 * n, false)
        , ans(n)
        , comp(2 * n, -1) {}

    void add_impl(int a, int b) {
        graph[a].pb(b);
        graph_rev[b].pb(a);
        graph[b ^ 1].pb(a ^ 1);
        graph_rev[a ^ 1].pb(b ^ 1);
    }

    void add_or(int a, int b) { add_impl(a ^ 1, b); }

    void set(int i, bool val) {
        int u = 2 * i + (val ? 0 : 1);
        add_impl(u ^ 1, u);
    }

    void dfs1(int v) {
        used[v] = true;
        for (int u: graph[v]) {
            if (!used[u]) {
                dfs1(u);
            }
        }
        ord.pb(v);
    }

    void dfs2(int v, int color) {
        comp[v] = color;
        for (int u: graph_rev[v]) {
            if (comp[u] == -1) {
                dfs2(u, color);
            }
        }
    }

    bool get_ans() {
        for (int i = 0; i < 2 * n; ++i) {
            if (!used[i]) dfs1(i);
        }
        int color = 0;
        for (int i = sz(ord) - 1; i >= 0; --i) {
            int v = ord[i];
            if (comp[v] == -1) {
                dfs2(v, color++);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (comp[2 * i] == comp[2 * i + 1]) {
                return false;
            }
            ans[i] = comp[2 * i] > comp[2 * i + 1];
        }
        return true;
    }
};

void solve() {}
