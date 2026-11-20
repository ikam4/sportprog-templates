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

// Прибавление и сумма на отрезке; совместимо с HLD ниже.
class HldSegtree {
    struct node {
        ll val = 0;
        ll promise = 0;
    };
    int n = 0;
    vector<node> tree;

public:
    HldSegtree() = default;
    HldSegtree(const vi& arr) : n(sz(arr)), tree(4 * n) {
        if (n) build(0, 0, n, arr);
    }
    void update(int l, int r, ll val) { update(0, 0, n, l, r + 1, val); }
    ll query(int l, int r) { return query(0, 0, n, l, r + 1); }

private:
    void build(int idx, int cl, int cr, const vi& arr) {
        if (cl + 1 == cr) {
            tree[idx].val = arr[cl];
            return;
        }
        int mid = (cl + cr) / 2;
        build(idx * 2 + 1, cl, mid, arr);
        build(idx * 2 + 2, mid, cr, arr);
        tree[idx].val = tree[idx * 2 + 1].val + tree[idx * 2 + 2].val;
    }

    void push(int idx, int cl, int cr) {
        int mid = (cl + cr) / 2;
        if (tree[idx].promise == 0) return;
        tree[2 * idx + 1].promise += tree[idx].promise;
        tree[2 * idx + 1].val += tree[idx].promise * (mid - cl);
        tree[2 * idx + 2].promise += tree[idx].promise;
        tree[2 * idx + 2].val += tree[idx].promise * (cr - mid);
        tree[idx].promise = 0;
    }

    void update(int idx, int cl, int cr, int l, int r, ll val) {
        if (cr <= l || cl >= r) return;
        if (cl >= l && cr <= r) {
            tree[idx].val += val * (cr - cl);
            tree[idx].promise += val;
            return;
        }
        push(idx, cl, cr);
        int mid = (cl + cr) / 2;
        update(idx * 2 + 1, cl, mid, l, r, val);
        update(idx * 2 + 2, mid, cr, l, r, val);
        tree[idx].val = tree[idx * 2 + 1].val + tree[idx * 2 + 2].val;
    }

    ll query(int idx, int cl, int cr, int l, int r) {
        if (cr <= l || cl >= r) return 0;
        if (cl >= l && cr <= r) return tree[idx].val;
        push(idx, cl, cr);
        int mid = (cl + cr) / 2;
        return query(idx * 2 + 1, cl, mid, l, r) + query(idx * 2 + 2, mid, cr, l, r);
    }
};

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
        , size(n, 0)
        , parent(n, -1)
        , depth(n, 0)
        , heavy(n, -1)
        , pos(n, -1)
        , head(n, -1)
        , vals(n) {
        dfs1(root, -1);
        dfs2(root, -1, root);
        for (int i = 0; i < n; ++i) {
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

    ll query(int u, int v) {
        ll res = 0;
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
