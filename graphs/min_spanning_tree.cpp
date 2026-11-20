// BEST TEMPLATE EVER by ikam
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

template<class T> istream& operator>>(istream& in, vector<T>& a);
template<class T> ostream& operator<<(ostream& out, const vector<T>& a);
template<class A, class B> istream& operator>>(istream& in, pair<A, B>& p) { return in >> p.fi >> p.se; }
template<class A, class B> ostream& operator<<(ostream& out, const pair<A, B>& p) { return out << p.fi << ' ' << p.se; }
template<class T> istream& operator>>(istream& in, vector<T>& a) {
    for (auto& x: a) in >> x;
    return in;
}
template<class T> ostream& operator<<(ostream& out, const vector<T>& a) {
    for (int i = 0; i < sz(a); ++i) out << a[i] << " \n"[i + 1 == sz(a)];
    return out;
}

template<class T, class U> inline bool chmin(T& a, const U& b) {
    if (!(b < a)) return false;
    a = b;
    return true;
}
template<class T, class U> inline bool chmax(T& a, const U& b) {
    if (!(a < b)) return false;
    a = b;
    return true;
}

#ifdef LOCAL
namespace debug_detail {
    template<class T> ostream& print(const T& value) {
        cerr << value;
        return cerr;
    }
    template<class T> ostream& print(const vector<T>& values);
    template<class A, class B> ostream& print(const pair<A, B>& p) {
        cerr << '(';
        print(p.fi) << ", ";
        return print(p.se) << ')';
    }
    template<class T> ostream& print(const vector<T>& values) {
        cerr << '[';
        for (int i = 0; i < sz(values); ++i) {
            if (i) cerr << ", ";
            print(values[i]);
        }
        return cerr << ']';
    }
    template<class... T> void print_values(const T&... values) {
        ((cerr << ' ', print(values)), ...);
        cerr << nn;
    }
}
#define dbg(...) (std::cerr << "[" #__VA_ARGS__ "]", debug_detail::print_values(__VA_ARGS__))
#else
#define dbg(...) ((void) 0)
#endif

inline int msb(ll x) { return x ? 63 - __builtin_clzll((ull) x) : -1; } // старший 1-бит (нумерация с нуля)
inline int lsb(ll x) { return x ? __builtin_ctzll((ull) x) : -1; } // младший 1-бит (нумерация с нуля)

constexpr int MOD = 1'000'000'007;
constexpr int INF = 0x3f3f3f3f;
constexpr ll LINF = 0x3f3f3f3f3f3f3f3fLL;
const ld PI = acos(-1.0L);
constexpr ld EPS = 1e-9L;

template<class T, class K, class Mul> inline T binpow_apply(T& a, K& e, Mul multiply) {
    T r = 1;
    for (; e > 1; e >>= 1) {
        if (e & 1) r = multiply(r, a);
        a = multiply(a, a);
    }
    r = multiply(r, a);
    return r;
}
template<class T, class K> inline T binpow(T a, K e) {
    assert(e >= 0);
    if (!(e > 0)) return 1;
    return binpow_apply(a, e, multiplies<>{});
}
template<class T = remove_cv_t<decltype(MOD)>, class A, class K> inline T modpow(A a, K e, T mod = MOD) {
    static_assert(is_integral_v<T> && sizeof(T) <= sizeof(ull));
    assert(e >= 0 && mod > 0);
    if (mod == 1 || !(e > 0)) return mod != 1;
    using Common = common_type_t<A, T>;
    using Remainder = conditional_t<is_signed_v<A> && is_unsigned_v<Common>, i128, Common>;
    Remainder remainder = (Remainder) a % mod;
    if (remainder < 0) remainder += mod;
    T base = (T) remainder;
    return binpow_apply(base, e, [m = (ull) mod](T x, T y) -> T {
        if (m <= (1ULL << 32)) return (T) ((ull) x * y % m);
        return (T) ((__uint128_t) x * y % m);
    });
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
        : parent(n)
        , size(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    int find_set(int u) {
        if (u == parent[u]) return u;
        return parent[u] = find_set(parent[u]);
    }
    bool unite(int a, int b) {
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
        if (dsu.unite(u, v)) {
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

template<typename T>
common_type_t<T, ll> prim(span<vector<pair<int, T>>> graph) {
    vector<T> min_edge(sz(graph), numeric_limits<T>::max());
    // vi parent(sz(graph), -1);
    // vector<pii> mst_edges;
    vector<bool> used(sz(graph), false);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
    common_type_t<T, ll> total = 0;
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

ll prim(span<vector<pii>> graph) { return prim<int>(graph); }

template<typename T>
common_type_t<T, ll> prim_v2(span<vector<pair<int, T>>> graph) {
    int n = sz(graph);
    const T inf = numeric_limits<T>::max();
    vector<T> min_edge(n, inf);
    // vi parent(n, -1);
    // vector<pii> mst_edges;
    vector<bool> used(n, false);
    common_type_t<T, ll> total = 0;
    min_edge[0] = 0;
    for (int i = 0; i < n; ++i) {
        int v = -1;
        for (int j = 0; j < n; ++j) {
            if (!used[j] && (v == -1 || min_edge[j] < min_edge[v])) {
                v = j;
            }
        }
        if (min_edge[v] == inf) {
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

ll prim_v2(span<vector<pii>> graph) { return prim_v2<int>(graph); }

ll boruvka(int n, span<array<int, 3>> edges) {
    int comps = n;
    DSU dsu(n);
    vi min_edge(n);
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
        for (int i = 0; i < n; ++i) {
            if (min_edge[i] != -1) {
                auto [u, v, w] = edges[min_edge[i]];
                if (dsu.unite(u, v)) {
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
