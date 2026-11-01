// Лучший шаблон
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

inline int msb(ll x) { return x ? 63 - __builtin_clzll((ull) x) : -1; } // старший 1-бит (нумерация с нуля)
inline int lsb(ll x) { return x ? __builtin_ctzll((ull) x) : -1; } // младший 1-бит (нумерация с нуля)

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
        ll cnt = 0;
        ll lazy = 0;
    };

    int max_n = 0, tr_sz = 0;
    vector<Node> tr;

    int create_node() {
        tr.eb();
        return tr_sz++;
    }

    void pull(int v) { tr[v].cnt = tr[tr[v].l].cnt + tr[tr[v].r].cnt; }

    void push(int v, int cl, int cr) {
        if (!tr[v].lazy) return;
        int mid = cl + (cr - cl) / 2;

        if (!tr[v].l) tr[v].l = create_node();
        if (!tr[v].r) tr[v].r = create_node();

        tr[tr[v].l].lazy += tr[v].lazy;
        tr[tr[v].l].cnt += tr[v].lazy * (mid - cl);

        tr[tr[v].r].lazy += tr[v].lazy;
        tr[tr[v].r].cnt += tr[v].lazy * (cr - mid);

        tr[v].lazy = 0;
    }

public:
    ImplSegtreePool(int max_n_, int max_nodes = 0)
        : max_n(max_n_) {
        tr.reserve(max_nodes);
        tr_sz++;
        tr.eb();
    }

    int update(int v, int ql, int qr, ll val) { return update(v, 0, max_n, ql, qr + 1, val); }

    ll query(int v, int ql, int qr) { return query(v, 0, max_n, ql, qr + 1); }

    int merge(int u, int v) { return merge(u, v, 0, max_n); }

    void split(int v, int pos, int& l_tree, int& r_tree) { split(v, 0, max_n, pos, l_tree, r_tree); }

private:
    int update(int v, int cl, int cr, int ql, int qr, ll val) {
        if (ql >= cr || qr <= cl) return v;
        if (!v) v = create_node();

        if (ql <= cl && cr <= qr) {
            tr[v].cnt += val * (cr - cl);
            tr[v].lazy += val;
            return v;
        }

        push(v, cl, cr);
        int mid = cl + (cr - cl) / 2;
        tr[v].l = update(tr[v].l, cl, mid, ql, qr, val);
        tr[v].r = update(tr[v].r, mid, cr, ql, qr, val);
        pull(v);
        return v;
    }

    int merge(int u, int v, int cl, int cr) {
        if (!u || !v) return u ? u : v;

        int nw = create_node();
        if (cl + 1 == cr) {
            tr[nw].cnt = tr[u].cnt + tr[v].cnt;
            return nw;
        }

        push(u, cl, cr);
        push(v, cl, cr);

        int mid = cl + (cr - cl) / 2;
        tr[nw].l = merge(tr[u].l, tr[v].l, cl, mid);
        tr[nw].r = merge(tr[u].r, tr[v].r, mid, cr);
        pull(nw);
        return nw;
    }

    ll query(int v, int cl, int cr, int ql, int qr) {
        if (!v || cl >= qr || cr <= ql) return 0;
        if (ql <= cl && cr <= qr) return tr[v].cnt;

        push(v, cl, cr);
        int mid = cl + (cr - cl) / 2;
        return query(tr[v].l, cl, mid, ql, qr) + query(tr[v].r, mid, cr, ql, qr);
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

    void merge(const ImplSegtree& other) {
        if (seg_pool && other.seg_pool) {
            root = seg_pool->merge(root, other.root);
        } else if (other.seg_pool) {
            seg_pool = other.seg_pool;
            root = other.root;
        }
    }

    ImplSegtree split(int pos) {
        if (!seg_pool) return ImplSegtree();
        int right_root = 0;
        seg_pool->split(root, pos, root, right_root);
        return ImplSegtree(seg_pool, right_root);
    }
};

void solve() {}
