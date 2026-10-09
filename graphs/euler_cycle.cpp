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

vector<int> ans;

void euler(int v, auto& graph, auto& deleted) {
    while (!graph[v].empty()) {
        auto [u, id] = graph[v].back();
        graph[v].pop_back();
        if (!deleted[id]) {
            deleted[id] = true;
            euler(u, graph, deleted);
        }
    }
    ans.pb(v);
}

void solve() {
    int n, m; // кол-во вершин и ребер
    cin >> n >> m;
    vector<vector<pii>> graph(n + 1);
    vector<bool> deleted(m + 1, false);
    vector<int> deg(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].eb(b, i);
        graph[b].eb(a, i);
        deg[a]++;
        deg[b]++;
    }
    // если не гарантируется, что граф эйлеров или полуэйлеров, просто и для ориент, и для неориент
    // найдем компоненты связности (слабой связности),
    // алгос по сути тут такой же, просто надо еще обратные ребра добавить, короче разобьем и
    // проверим, что есть только 1 компонента с ребрами

    int start_node = 0;
    for (int i = 1; i <= n; ++i) {
        if (!start_node && deg[i] % 2 == 0 && deg[i] > 0) {
            start_node = i;
        }
        if (deg[i] % 2 == 1) {
            start_node = i;
            break;
        }
    }
    if (!start_node) {
        cout << -1;
        return;
    }
    euler(start_node, graph, deleted);
    ranges::reverse(ans);
    if (sz(ans) != m + 1) {
        cout << -1;
        return;
    }
    each(x, ans) cout << x;
}

void euler2(int v, auto& graph) {
    while (!graph[v].empty()) {
        int u = graph[v].back();
        graph[v].pop_back();
        euler2(u, graph);
    }
    ans.pb(v);
}

void solve2() { // для ориент
    int n, m; // кол-во вершин и ребер
    cin >> n >> m;
    vector<vi> graph(n + 1);
    vector<int> in(n + 1), out(n + 1);
    for (int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].pb(b);
        in[b]++;
        out[a]++;
    }
    // если не гарантируется, что граф эйлеров или полуэйлеров, просто и для ориент, и для неориент
    // найдем компоненты связности (слабой связности),
    // алгос по сути тут такой же, просто надо еще обратные ребра добавить, короче разобьем и
    // проверим, что есть только 1 компонента с ребрами

    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 1; i <= n; ++i) {
        if (in[i] - out[i] == 1) {
            cnt1++;
        } else if (out[i] - in[i] == 1) {
            cnt2++;
        } else if (in[i] == out[i]) {
            continue;
        } else {
            cnt1 = cnt2 = 2;
            break;
        }
    }

    if (cnt1 != cnt2 || cnt1 + cnt2 >= 4) {
        cout << -1;
        return;
    }

    int start_node = 0;
    for (int i = 1; i <= n; ++i) {
        if (!start_node && in[i] == out[i] && in[i] + out[i] > 0) {
            start_node = i;
        }
        if (out[i] - in[i] == 1) {
            start_node = i;
            break;
        }
    }
    if (!start_node) {
        cout << -1;
        return;
    }
    euler2(start_node, graph);
    ranges::reverse(ans);
    if (sz(ans) != m + 1) {
        cout << -1;
        return;
    }
    each(x, ans) cout << x;
}
