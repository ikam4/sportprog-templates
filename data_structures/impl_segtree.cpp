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

class ImplSegtreePool {
    struct Node {
        int l = 0, r = 0;
        int cnt = 0;
    };
    int max_n = 0;
    vector<Node> tr;
    int create_node() {
        int v = sz(tr);
        tr.eb();
        return v;
    }

public:
    ImplSegtreePool(int max_n_, int max_nodes = 0)
        : max_n(max_n_) {
        tr.reserve(max_nodes);
        tr.eb();
    }
    int update(int v, int pos, int val) { return update(v, 0, max_n, pos, val); }
    int merge(int u, int v) { return merge(u, v, 0, max_n); }
    int query(int v, int l, int r) const { return query(v, 0, max_n, l, r + 1); }

private:
    int update(int v, int cl, int cr, int pos, int val) {
        if (!v) v = create_node();
        if (cl + 1 == cr) {
            tr[v].cnt += val;
            return v;
        }
        int mid = cl + (cr - cl) / 2;
        if (pos < mid) {
            int to_l = update(tr[v].l, cl, mid, pos, val);
            tr[v].l = to_l;
        } else {
            int to_r = update(tr[v].r, mid, cr, pos, val);
            tr[v].r = to_r;
        }
        tr[v].cnt = tr[tr[v].l].cnt + tr[tr[v].r].cnt;
        return v;
    }
    int merge(int u, int v, int cl, int cr) {
        if (!u || !v) return u ? u : v;
        if (cl + 1 == cr) {
            tr[u].cnt += tr[v].cnt;
            return u;
        }
        int mid = cl + (cr - cl) / 2;
        tr[u].l = merge(tr[u].l, tr[v].l, cl, mid);
        tr[u].r = merge(tr[u].r, tr[v].r, mid, cr);
        tr[u].cnt = tr[tr[u].l].cnt + tr[tr[u].r].cnt;
        return u;
    }
    int query(int v, int cl, int cr, int l, int r) const {
        if (!v || cl >= r || cr <= l) return 0;
        if (cl >= l && cr <= r) {
            return tr[v].cnt;
        }
        int mid = cl + (cr - cl) / 2;
        return query(tr[v].l, cl, mid, l, r) + query(tr[v].r, mid, cr, l, r);
    }
};

struct ImplSegtree {
    int root = 0;
    ImplSegtreePool* seg_pool = nullptr;

    ImplSegtree() = default;
    ImplSegtree(ImplSegtreePool* pool, int r = 0)
        : root(r)
        , seg_pool(pool) {}
    ImplSegtree(ImplSegtreePool& pool, int r = 0)
        : root(r)
        , seg_pool(&pool) {}

    void update(int pos, int val = 1) {
        if (seg_pool) root = seg_pool->update(root, pos, val);
    }

    int query(int l, int r) const { return seg_pool ? seg_pool->query(root, l, r) : 0; }

    bool merge(ImplSegtree&& other) {
        if (this == &other) return false;
        if (!other.seg_pool) return true;
        if (seg_pool && seg_pool != other.seg_pool) return false;

        if (!seg_pool) seg_pool = other.seg_pool;
        root = seg_pool->merge(root, other.root);
        other.root = 0;
        return true;
    }
};

void solve() {}
