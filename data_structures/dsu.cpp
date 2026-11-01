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

struct DSU {
    vi parent, size;

    DSU(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find_set(int v) {
        if (parent[v] == v) return v;
        return parent[v] = find_set(parent[v]);
    }

    bool unite(int u, int v) {
        int a = find_set(u);
        int b = find_set(v);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
            return true;
        }
        return false;
    }
};

struct RollbackDSU {
    vector<int> parent, size;
    int comps;
    vector<pair<int*, int>> history;

    RollbackDSU(int n) : parent(n), size(n, 1), comps(n) {
        iota(parent.begin(), parent.end(), 0);
        // history.reserve(1000000);
    }

    int find_set(int u) const {
        while (u != parent[u]) {
            u = parent[u];
        }
        return u;
    }

    bool union_sets(int u, int v) {
        u = find_set(u);
        v = find_set(v);
        if (u == v) return false;

        if (size[u] < size[v]) {
            swap(u, v);
        }

        history.eb(&parent[v], parent[v]);
        parent[v] = u;

        history.eb(&size[u], size[u]);
        size[u] += size[v];

        history.eb(&comps, comps);
        comps--;

        return true;
    }

    int snapshot() const { return history.size(); }

    void rollback(int target_state) {
        while ((int) history.size() > target_state) {
            *history.back().first = history.back().second;
            history.pop_back();
        }
    }
};

void solve() {}
