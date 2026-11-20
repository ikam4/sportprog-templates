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
        ll cnt = 0;
        ll lazy = 0;
    };

    int max_n = 0;
    vector<Node> tr;

    int create_node() {
        int v = sz(tr);
        tr.eb();
        return v;
    }

    void pull(int v) { tr[v].cnt = tr[tr[v].l].cnt + tr[tr[v].r].cnt; }

    void apply(int v, int cl, int cr, ll val) {
        tr[v].lazy += val;
        tr[v].cnt += val * (cr - cl);
    }

    void push(int v, int cl, int cr) {
        ll tag = tr[v].lazy;
        if (!tag) return;
        int mid = cl + (cr - cl) / 2;

        if (!tr[v].l) tr[v].l = create_node();
        if (!tr[v].r) tr[v].r = create_node();

        apply(tr[v].l, cl, mid, tag);
        apply(tr[v].r, mid, cr, tag);
        tr[v].lazy = 0;
    }

public:
    ImplSegtreePool(int max_n_, int max_nodes = 0)
        : max_n(max_n_) {
        tr.reserve(max_nodes);
        tr.eb();
    }

    int update(int v, int ql, int qr, ll val) { return update(v, 0, max_n, ql, qr + 1, val); }

    ll query(int v, int ql, int qr) const {
        return ql > qr ? 0 : query(v, 0, max_n, ql, qr + 1, 0);
    }

    int merge(int u, int v) {
        if (!u || !v) return u ? u : v;

        tr[u].cnt += tr[v].cnt;
        tr[u].lazy += tr[v].lazy;
        tr[u].l = merge(tr[u].l, tr[v].l);
        tr[u].r = merge(tr[u].r, tr[v].r);
        return u;
    }

    void split(int v, int pos, int& l_tree, int& r_tree) { split(v, 0, max_n, pos, l_tree, r_tree); }

private:
    int update(int v, int cl, int cr, int ql, int qr, ll val) {
        if (ql >= cr || qr <= cl) return v;
        if (!v) v = create_node();

        if (ql <= cl && cr <= qr) {
            apply(v, cl, cr, val);
            return v;
        }

        push(v, cl, cr);
        int mid = cl + (cr - cl) / 2;
        tr[v].l = update(tr[v].l, cl, mid, ql, qr, val);
        tr[v].r = update(tr[v].r, mid, cr, ql, qr, val);
        pull(v);
        return v;
    }

    ll query(int v, int cl, int cr, int ql, int qr, ll carry) const {
        if (cl >= qr || cr <= ql) return 0;
        if (!v) return carry * (min(cr, qr) - max(cl, ql));
        if (ql <= cl && cr <= qr) return tr[v].cnt + carry * (cr - cl);

        carry += tr[v].lazy;
        int mid = cl + (cr - cl) / 2;
        return query(tr[v].l, cl, mid, ql, qr, carry) +
               query(tr[v].r, mid, cr, ql, qr, carry);
    }

    void split(int v, int cl, int cr, int pos, int& l_tree, int& r_tree) {
        if (!v) {
            l_tree = r_tree = 0;
            return;
        }
        if (cl >= pos) {
            l_tree = 0;
            r_tree = v;
            return;
        }
        if (cr <= pos) {
            l_tree = v;
            r_tree = 0;
            return;
        }

        push(v, cl, cr);
        l_tree = v;
        r_tree = create_node();

        int mid = cl + (cr - cl) / 2;
        int ll_, lr_, rl_, rr_;
        split(tr[v].l, cl, mid, pos, ll_, lr_);
        split(tr[v].r, mid, cr, pos, rl_, rr_);
        tr[l_tree].l = ll_; tr[r_tree].l = lr_;
        tr[l_tree].r = rl_; tr[r_tree].r = rr_;

        pull(l_tree);
        pull(r_tree);
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

    void update(int l, int r, ll val) {
        if (seg_pool) root = seg_pool->update(root, l, r, val);
    }

    void update_point(int pos, ll val = 1) {
        if (seg_pool) root = seg_pool->update(root, pos, pos, val);
    }

    ll query(int l, int r) const { return seg_pool ? seg_pool->query(root, l, r) : 0; }

    bool merge(ImplSegtree&& other) {
        if (this == &other) return false;
        if (!other.seg_pool) return true;
        if (seg_pool && seg_pool != other.seg_pool) return false;

        if (!seg_pool) seg_pool = other.seg_pool;
        root = seg_pool->merge(root, other.root);
        other.root = 0;
        return true;
    }

    ImplSegtree split(int pos) {
        if (!seg_pool) return ImplSegtree();
        int right_root = 0;
        seg_pool->split(root, pos, root, right_root);
        return ImplSegtree(seg_pool, right_root);
    }
};

void solve() {}
