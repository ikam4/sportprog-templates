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

template<typename Node, typename Lazy, typename Merge, typename Apply, typename Compose>
class lazy_segtree {
    struct node {
        Node val{};
        Lazy prom{};
    };
    int n = 0;
    vector<node> tr;
    Merge merge_op;
    Apply apply_op;
    Compose compose_op;

public:
    lazy_segtree() = default;
    lazy_segtree(const vector<Node>& other, Merge m, Apply a, Compose c) :
        n(sz(other)), tr(4 * n), merge_op(m), apply_op(a), compose_op(c) {
        if (n > 0) {
            build(0, 0, n, other);
        }
    }
    void update(int l, int r, Lazy val) { update(0, 0, n, l, r + 1, val); }
    Node query(int l, int r) { return query(0, 0, n, l, r + 1); }

private:
    void build(int idx, int cl, int cr, const vector<Node>& other) {
        if (cl + 1 == cr) {
            tr[idx].val = other[cl];
            return;
        }
        int mid = (cl + cr) / 2;
        build(2 * idx + 1, cl, mid, other);
        build(2 * idx + 2, mid, cr, other);
        tr[idx].val = merge_op(tr[2 * idx + 1].val, tr[2 * idx + 2].val);
    }

    void push(int idx) {
        tr[2 * idx + 1].val = apply_op(tr[2 * idx + 1].val, tr[idx].prom);
        tr[2 * idx + 2].val = apply_op(tr[2 * idx + 2].val, tr[idx].prom);
        tr[2 * idx + 1].prom = compose_op(tr[2 * idx + 1].prom, tr[idx].prom);
        tr[2 * idx + 2].prom = compose_op(tr[2 * idx + 2].prom, tr[idx].prom);
        tr[idx].prom = Lazy{};
    }

    void update(int idx, int cl, int cr, int l, int r, Lazy val) {
        if (cl >= r || l >= cr) {
            return;
        }
        if (cl >= l && cr <= r) {
            tr[idx].val = apply_op(tr[idx].val, val);
            tr[idx].prom = compose_op(tr[idx].prom, val);
            return;
        }
        push(idx);
        int mid = (cl + cr) / 2;
        update(2 * idx + 1, cl, mid, l, r, val);
        update(2 * idx + 2, mid, cr, l, r, val);
        tr[idx].val = merge_op(tr[2 * idx + 1].val, tr[2 * idx + 2].val);
    }

    Node query(int idx, int cl, int cr, int l, int r) {
        if (cl >= r || l >= cr) {
            return Node{};
        }
        if (cl >= l && cr <= r) {
            return tr[idx].val;
        }
        push(idx);
        int mid = (cl + cr) / 2;
        return merge_op(query(2 * idx + 1, cl, mid, l, r), query(2 * idx + 2, mid, cr, l, r));
    }
};

// попроще: прибавление на отрезке и минимум
class segtree {
    struct node {
        ll val = 0;
        ll promise = 0;
    };
    int n;
    vector<node> tree;

public:
    segtree(int k) : n(k), tree(4 * n) {}
    template<typename T = ll>
    segtree(const vector<T>& arr) : n(sz(arr)), tree(4 * n) {
        if (n) build(0, 0, n, arr);
    }
    void update(int l, int r, ll val) { update(0, 0, n, l, r + 1, val); }
    ll get(int l, int r) { return get(0, 0, n, l, r + 1); }

private:
    template<typename T>
    void build(int idx, int cl, int cr, const vector<T>& arr) {
        if (cl + 1 == cr) {
            tree[idx].val = arr[cl];
            return;
        }
        int mid = (cl + cr) / 2;
        build(idx * 2 + 1, cl, mid, arr);
        build(idx * 2 + 2, mid, cr, arr);
        tree[idx].val = min(tree[idx * 2 + 1].val, tree[idx * 2 + 2].val);
    }

    void push(int idx) {
        if (tree[idx].promise == 0) return;
        tree[2 * idx + 1].promise += tree[idx].promise;
        tree[2 * idx + 1].val += tree[idx].promise;
        tree[2 * idx + 2].promise += tree[idx].promise;
        tree[2 * idx + 2].val += tree[idx].promise;
        tree[idx].promise = 0;
    }
    void update(int idx, int cl, int cr, int l, int r, ll val) {
        if (cr <= l || cl >= r) {
            return;
        }
        if (cl >= l && cr <= r) {
            tree[idx].val += val;
            tree[idx].promise += val;
            return;
        }
        push(idx);
        int mid = (cl + cr) / 2;
        update(idx * 2 + 1, cl, mid, l, r, val);
        update(idx * 2 + 2, mid, cr, l, r, val);
        tree[idx].val = min(tree[idx * 2 + 1].val, tree[idx * 2 + 2].val);
    }
    ll get(int idx, int cl, int cr, int l, int r) {
        if (cr <= l || cl >= r) return LINF;
        if (cl >= l && cr <= r) return tree[idx].val;
        push(idx);
        int mid = (cl + cr) / 2;
        return min(get(idx * 2 + 1, cl, mid, l, r), get(idx * 2 + 2, mid, cr, l, r));
    }
};

void solve() {}
