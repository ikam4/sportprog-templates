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

class ImplSegtreePool {
    struct Node {
        int l = 0, r = 0;
        int cnt = 0;
    };

    int max_n = 0, tr_sz = 0;
    vector<Node> tr;

    int create_node() {
        tr.eb();
        return tr_sz++;
    }

public:
    ImplSegtreePool(int max_n_, int max_nodes = 8'000'000)
        : max_n(max_n_) {
        tr.reserve(max_nodes);
        tr_sz++;
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
        int nw = create_node();
        if (cl + 1 == cr) {
            tr[nw].cnt = tr[u].cnt + tr[v].cnt;
            return nw;
        }
        int mid = cl + (cr - cl) / 2;
        int to_l = merge(tr[u].l, tr[v].l, cl, mid);
        int to_r = merge(tr[u].r, tr[v].r, mid, cr);
        tr[nw].l = to_l;
        tr[nw].r = to_r;
        tr[nw].cnt = tr[tr[nw].l].cnt + tr[tr[nw].r].cnt;
        return nw;
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

    void merge(const ImplSegtree& other) {
        if (seg_pool && other.seg_pool) {
            root = seg_pool->merge(root, other.root);
        } else if (other.seg_pool) {
            seg_pool = other.seg_pool;
            root = other.root;
        }
    }
};

void solve() {}
