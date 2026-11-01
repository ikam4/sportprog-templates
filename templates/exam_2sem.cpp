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


inline uint64_t splitmix64(uint64_t x) noexcept {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
static uint64_t sm_state =
    (uint64_t) chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t) (uintptr_t) new int;
inline uint64_t rnd() noexcept {
    sm_state += 0x9e3779b97f4a7c15ULL;
    return splitmix64(sm_state);
}

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

template<typename T>
struct Fenwick {
    int n;
    vector<T> tr;

    Fenwick(int n)
        : n(n)
        , tr(n) {}

    Fenwick(vector<T> other)
        : n(sz(other))
        , tr(std::move(other)) {
        for (int i = 0; i < n; ++i) {
            int p = i | (i + 1);
            if (p < n) {
                tr[p] += tr[i];
            }
        }
    }

    void update_(int pos, T delta) {
        for (int i = pos; i < n; i = i | (i + 1)) {
            tr[i] += delta;
        }
    }

    T get_pref(int pos) {
        T res{};
        for (int i = pos; i >= 0; i = (i & (i + 1)) - 1) {
            res += tr[i];
        }
        return res;
    }

    T get(int l, int r) { return get_pref(r) - get_pref(l - 1); }

    void update(int pos, T val) { update_(pos, val - get(pos, pos)); }
};

template<typename Node, typename Lazy, typename Merge, typename Apply, typename Compose>
class lazy_segtree {
    struct node {
        Node val{};
        Lazy prom{};
    };
    int n;
    vector<node> tr;
    Merge merge_op;
    Apply apply_op;
    Compose compose_op;

public:
    lazy_segtree() = default;
    lazy_segtree(const vector<Node>& other, Merge m, Apply a, Compose c)
        : n(sz(other))
        , tr(4 * n)
        , merge_op(m)
        , apply_op(a)
        , compose_op(c) {
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

struct Treap {
    struct Node {
        int x = 0, y = 0, sz = 0;
        array<int, 2> children{};
        int& operator[](int idx) { return children[idx]; }
    };
    int root = 0;
    vector<Node> tr;

    Treap() { tr.eb(); }

    void recalc(int node) {
        if (!node) return;
        tr[node].sz = 1 + tr[tr[node][0]].sz + tr[tr[node][1]].sz;
    }

    int make_node(int x) {
        tr.eb(x, (int) rnd(), 1);
        return sz(tr) - 1;
    }

    pair<int, int> split(int T, int x) {
        if (!T) {
            return {0, 0};
        }
        if (tr[T].x >= x) {
            auto [TLL, TLR] = split(tr[T][0], x);
            tr[T][0] = TLR;
            recalc(T);
            return {TLL, T};
        } else {
            auto [TRL, TRR] = split(tr[T][1], x);
            tr[T][1] = TRL;
            recalc(T);
            return {T, TRR};
        }
    }

    int merge(int TL, int TR) {
        if (TL == 0) return TR;
        if (TR == 0) return TL;
        if (tr[TL].y >= tr[TR].y) {
            tr[TL][1] = merge(tr[TL][1], TR);
            recalc(TL);
            return TL;
        } else {
            tr[TR][0] = merge(TL, tr[TR][0]);
            recalc(TR);
            return TR;
        }
    }

    int insert(int T, int node) {
        if (!T) return node;
        if (tr[node].y >= tr[T].y) {
            auto [TL, TR] = split(T, tr[node].x);
            tr[node][0] = TL;
            tr[node][1] = TR;
            recalc(node);
            return node;
        }
        if (tr[T].x >= tr[node].x) {
            tr[T][0] = insert(tr[T][0], node);
        } else {
            tr[T][1] = insert(tr[T][1], node);
        }
        recalc(T);
        return T;
    }

    void insert(int x) {
        int node = make_node(x);
        root = insert(root, node);
    }

    int erase(int T, int x) {
        if (!T) return 0;
        if (tr[T].x == x) {
            return merge(tr[T][0], tr[T][1]);
        } else if (tr[T].x > x) {
            tr[T][0] = erase(tr[T][0], x);
        } else {
            tr[T][1] = erase(tr[T][1], x);
        }
        recalc(T);
        return T;
    }

    void erase(int x) { root = erase(root, x); }

    int get_kth(int k) {
        int T = root;
        while (T) {
            int left_sz = tr[tr[T][0]].sz;
            if (left_sz > k) {
                T = tr[T][0];
            } else if (left_sz == k) {
                return T;
            } else {
                k -= left_sz + 1;
                T = tr[T][1];
            }
        }
        return 0;
    }

    int count_less(int x) {
        int T = root;
        int count = 0;
        while (T) {
            if (tr[T].x >= x) {
                T = tr[T][0];
            } else {
                count += tr[tr[T][0]].sz + 1;
                T = tr[T][1];
            }
        }
        return count;
    }

    bool contains(int x) {
        int T = root;
        while (T) {
            if (tr[T].x == x) {
                return true;
            } else if (tr[T].x > x) {
                T = tr[T][0];
            } else {
                T = tr[T][1];
            }
        }
        return false;
    }
};

struct ImplTreap {
    struct Node {
        int y = 0, val = 0, sz = 0;
        array<int, 2> children{};
        int& operator[](int idx) { return children[idx]; }
    };
    int root = 0;
    vector<Node> tr;

    ImplTreap() { tr.eb(); }

    void recalc(int node) {
        if (!node) return;
        tr[node].sz = 1 + tr[tr[node][0]].sz + tr[tr[node][1]].sz;
    }

    int make_node(int x) {
        tr.eb((int) rnd(), x, 1);
        return sz(tr) - 1;
    }

    pair<int, int> split(int T, int x) {
        if (!T) {
            return {0, 0};
        }
        if (tr[tr[T][0]].sz >= x) {
            auto [TLL, TLR] = split(tr[T][0], x);
            tr[T][0] = TLR;
            recalc(T);
            return {TLL, T};
        } else {
            auto [TRL, TRR] = split(tr[T][1], x - tr[tr[T][0]].sz - 1);
            tr[T][1] = TRL;
            recalc(T);
            return {T, TRR};
        }
    }

    int merge(int TL, int TR) {
        if (TL == 0) return TR;
        if (TR == 0) return TL;
        if (tr[TL].y >= tr[TR].y) {
            tr[TL][1] = merge(tr[TL][1], TR);
            recalc(TL);
            return TL;
        } else {
            tr[TR][0] = merge(TL, tr[TR][0]);
            recalc(TR);
            return TR;
        }
    }

    int insert(int T, int x, int node) {
        if (!T) return node;
        if (tr[node].y >= tr[T].y) {
            auto [TL, TR] = split(T, x);
            tr[node][0] = TL;
            tr[node][1] = TR;
            recalc(node);
            return node;
        }
        if (x <= tr[tr[T][0]].sz) {
            tr[T][0] = insert(tr[T][0], x, node);
        } else {
            tr[T][1] = insert(tr[T][1], x - tr[tr[T][0]].sz - 1, node);
        }
        recalc(T);
        return T;
    }

    void insert(int x, int val) {
        int node = make_node(val);
        root = insert(root, x, node);
    }

    int erase(int T, int x) {
        if (!T) return 0;
        if (x == tr[tr[T][0]].sz) {
            return merge(tr[T][0], tr[T][1]);
        } else if (x < tr[tr[T][0]].sz) {
            tr[T][0] = erase(tr[T][0], x);
        } else {
            tr[T][1] = erase(tr[T][1], x - tr[tr[T][0]].sz - 1);
        }
        recalc(T);
        return T;
    }

    void erase(int x) { root = erase(root, x); }

    int get_kth(int k) {
        int cur = root;
        while (cur) {
            int left_sz = tr[tr[cur][0]].sz;
            if (k == left_sz) return tr[cur].val;
            if (k < left_sz) {
                cur = tr[cur][0];
            } else {
                k -= left_sz + 1;
                cur = tr[cur][1];
            }
        }
        return -1;
    }

    void print(int v) {
        if (!v) return;
        print(tr[v][0]);
        cout << tr[v].val << ' ';
        print(tr[v][1]);
    }

    void print() {
        print(root);
        cout << nn;
    }
};

struct DSU {
    vi parent, size;

    DSU(int n)
        : parent(n)
        , size(n, 1) {
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

// graph[v] stores (neighbor, edge_id); both directions share one unique nonnegative id.
namespace bridges {
    void dfs(int v, int p, vi& tin, vi& low, int& timer, span<vector<pii>> graph, vector<pii>& bridges) {
        tin[v] = low[v] = timer++;
        for (auto [u, id]: graph[v]) {
            if (id == p) continue;
            if (tin[u]) {
                low[v] = min(low[v], tin[u]);
            } else {
                dfs(u, id, tin, low, timer, graph, bridges);
                low[v] = min(low[v], low[u]);
                if (low[u] > tin[v]) {
                    bridges.eb(v, u);
                }
            }
        }

        // if (low[v] == tin[v]) {
        //     comps.eb();
        //     int cur;
        //     do {
        //         cur = st.top();
        //         st.pop();
        //         comps.back().push_back(cur);
        //     } while (cur != v);
        // }
    }

    vector<pii> solve(span<vector<pii>> graph) {
        vi tin(graph.size()), low(graph.size());
        vector<pii> bridges;
        int timer = 1;
        for (int v = 0; v < sz(graph); ++v) {
            if (!tin[v]) dfs(v, -1, tin, low, timer, graph, bridges);
        }
        return bridges;
    }
};

namespace dots {
    void dfs(int v, int p, vi& tin, vi& low, int& timer, span<vector<pii>> graph, vector<bool>& dot) {
        tin[v] = low[v] = timer++;
        int children = 0;
        for (auto [u, id]: graph[v]) {
            if (id == p) continue;
            if (tin[u]) {
                low[v] = min(low[v], tin[u]);
            } else {
                ++children;
                dfs(u, id, tin, low, timer, graph, dot);
                low[v] = min(low[v], low[u]);
                if (p != -1 && low[u] >= tin[v]) { // remove for block tree
                    dot[v] = true;
                }
                // if (low[u] >= tin[v]) {
                //     comps.push_back({});
                //     int w;
                //     do {
                //         w = st.top();
                //         st.pop();
                //         comps.back().push_back(w);
                //     } while (w != u);
                //     comps.back().push_back(v);
                // }
            }
        }
        if (p == -1 && children > 1) { // remove for block tree
            dot[v] = true;
        }
    }

    vector<bool> solve(span<vector<pii>> graph) {
        vi tin(graph.size()), low(graph.size());
        vector<bool> dot(graph.size(), false);
        int timer = 1;
        for (int v = 0; v < sz(graph); ++v) {
            if (!tin[v]) dfs(v, -1, tin, low, timer, graph, dot);
        }
        return dot;
    }

};

namespace scc {
    void dfs1(int v, vector<bool>& used, vi& ord, span<vi> graph) {
        used[v] = true;
        for (int u: graph[v]) {
            if (!used[u]) {
                dfs1(u, used, ord, graph);
            }
        }
        ord.pb(v);
    }

    void dfs2(int v, vi& comp, int timer, span<vi> graph) {
        comp[v] = timer;
        for (int u: graph[v]) {
            if (comp[u] == -1) {
                dfs2(u, comp, timer, graph);
            }
        }
    }

    vector<vi> get_dag(span<int> comp, int comp_cnt, span<vi> graph) {
        vector<vi> new_graph(comp_cnt);
        for (int v = 0; v < sz(comp); ++v) {
            if (comp[v] == -1) continue;
            for (int u: graph[v]) {
                if (comp[u] != comp[v]) {
                    new_graph[comp[v]].pb(comp[u]);
                }
            }
        }
        for (int i = 0; i < comp_cnt; ++i) {
            sort(all(new_graph[i]));
            new_graph[i].erase(unique(all(new_graph[i])), new_graph[i].end());
        }
        return new_graph;
    }

    pair<vector<vi>, vi> solve(span<vi> graph, span<vi> rev_graph) {
        vector<bool> used(graph.size(), false);
        vi ord;
        for (int u = 0; u < sz(graph); ++u) {
            if (!used[u]) {
                dfs1(u, used, ord, graph);
            }
        }
        int timer = 0;
        vi comp(graph.size(), -1);
        for (int u = sz(ord) - 1; u >= 0; --u) {
            int v = ord[u];
            if (comp[v] == -1) {
                dfs2(v, comp, timer++, rev_graph);
            }
        }
        vector<vi> dag = get_dag(comp, timer, graph);
        return {dag, comp};
    }
};

namespace shortest_path {
    template<typename T>
    T dijkstra(int s, int v, span<vector<pair<int, T>>> graph) {
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        vector<T> d(graph.size(), numeric_limits<T>::max() / 2);
        d[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [dist, cur] = q.top();
            q.pop();
            if (dist > d[cur]) continue;
            for (auto [u, w]: graph[cur]) {
                if (d[u] > d[cur] + w) {
                    d[u] = d[cur] + w;
                    q.emplace(d[u], u);
                }
            }
        }
        return (d[v] == numeric_limits<T>::max() / 2 ? -1 : d[v]);
    }

    int bfs01(int s, int v, span<vector<pii>> graph) {
        deque<int> q;
        vector<bool> used(graph.size(), false);
        vi d(graph.size(), INF / 2);
        d[s] = 0;
        q.emplace_back(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            if (used[cur]) continue;
            used[cur] = true;
            for (auto [u, w]: graph[cur]) {
                if (d[u] > d[cur] + w) {
                    d[u] = d[cur] + w;
                    if (w == 0) {
                        q.emplace_front(u);
                    } else {
                        q.emplace_back(u);
                    }
                }
            }
        }
        return (d[v] == INF / 2 ? -1 : d[v]);
    }

    int bfs0k(int s, int v, int k, span<vector<pii>> graph) {
        vector<queue<int>> q(k + 1);
        vi d(graph.size(), INF / 2);
        int pos = 0, cnt = 1;
        d[s] = 0;
        q[0].push(s);
        while (cnt > 0) {
            while (q[pos % (k + 1)].empty()) {
                ++pos;
            }
            int cur = q[pos % (k + 1)].front();
            q[pos % (k + 1)].pop();
            --cnt;
            if (pos > d[cur]) continue;
            for (auto [u, w]: graph[cur]) {
                if (d[u] > d[cur] + w) {
                    d[u] = d[cur] + w;
                    q[d[u] % (k + 1)].push(u);
                    ++cnt;
                }
            }
        }
        return (d[v] == INF / 2 ? -1 : d[v]);
    }
};

namespace euler {
    void euler(int v, vector<vector<pii>>& graph, vector<bool>& deleted, vi& path) {
        while (!graph[v].empty()) {
            auto [u, id] = graph[v].back();
            graph[v].pop_back();
            if (deleted[id]) continue;
            deleted[id] = true;
            euler(u, graph, deleted, path);
        }
        path.pb(v);
    }

    vi solve(span<vi> graph) {
        vi deg(graph.size());
        vector<vector<pii>> new_graph(graph.size());
        int edge_id = 0;
        for (int v = 0; v < sz(graph); ++v) {
            for (int u: graph[v]) {
                if (u < v) {
                    new_graph[u].eb(v, edge_id);
                    new_graph[v].eb(u, edge_id);
                    deg[u]++;
                    deg[v]++;
                    edge_id++;
                }
            }
        }
        int start = -1;
        for (int i = 0; i < sz(graph); ++i) {
            if (deg[i] % 2 != 0) return {};
            if (deg[i] > 0 && start == -1) {
                start = i;
            }
        }
        if (start == -1) return {};
        vi path;
        vector<bool> deleted(edge_id, false);
        euler(start, new_graph, deleted, path);
        return path;
    }
};

struct LCA {
    int LOG;
    vector<vi> up;
    vi depth;

    LCA(int root, span<vi> graph) { solve(root, graph); }
    void dfs(int v, int p, span<vi> graph, vector<vi>& up, vi& depth) {
        up[v][0] = (p == -1 ? v : p);
        for (int i = 1; i < LOG; ++i) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
        for (int u: graph[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v, graph, up, depth);
            }
        }
    }

    int get_lca(int u, int v, const vi& depth, const vector<vi>& up) {
        if (depth[u] < depth[v]) swap(u, v);
        int diff = depth[u] - depth[v];
        for (int i = 0; i < LOG; ++i) {
            if ((diff >> i) & 1) {
                u = up[u][i];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        return up[u][0];
    }

    void solve(int root, span<vi> graph) {
        LOG = max(1, (int) bit_width((unsigned) graph.size()));
        up.assign(graph.size(), vi(LOG));
        depth.assign(graph.size(), 0);
        if (!graph.empty()) dfs(root, -1, graph, up, depth);
    }

    int query(int u, int v) { return get_lca(u, v, depth, up); }
};

struct fast_LCA {
    vi ord, euler_ord, first, depth;
    vector<vi> st;

    fast_LCA(int root, span<vi> graph) { solve(root, graph); }

    void dfs(int v, int p, vi& ord, span<vi> graph, vi& depth, vi& euler_ord, vi& first) {
        ord.pb(v);
        euler_ord.pb(depth[v]);
        if (first[v] == -1) first[v] = sz(euler_ord) - 1;
        for (int u: graph[v]) {
            if (u != p) {
                depth[u] = depth[v] + 1;
                dfs(u, v, ord, graph, depth, euler_ord, first);
                ord.pb(v);
                euler_ord.pb(depth[v]);
            }
        }
    }

    int get_lca(int u, int v, span<vi> st, const vi& first, const vi& euler_ord, const vi& ord) {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        int i = 31 - __builtin_clz(r - l + 1);
        int idx1 = st[i][l];
        int idx2 = st[i][r - (1 << i) + 1];
        int min_idx = (euler_ord[idx1] < euler_ord[idx2]) ? idx1 : idx2;
        return ord[min_idx];
    }

    void solve(int root, span<vi> graph) {
        ord.clear();
        euler_ord.clear();
        first.assign(graph.size(), -1);
        depth.assign(graph.size(), 0);
        if (graph.empty()) { st.clear(); return; }
        dfs(root, -1, ord, graph, depth, euler_ord, first);
        int LOG = 32 - __builtin_clz(sz(ord));
        st.assign(LOG, vi(sz(ord)));
        for (int i = 0; i < sz(ord); ++i) {
            st[0][i] = i;
        }
        for (int i = 1; i < LOG; ++i) {
            for (int j = 0; j + (1 << i) <= sz(ord); ++j) {
                int idx1 = st[i - 1][j], idx2 = st[i - 1][j + (1 << (i - 1))];
                st[i][j] = (euler_ord[idx1] < euler_ord[idx2] ? idx1 : idx2);
            }
        }
    }

    int query(int u, int v) {
        return get_lca(u, v, st, first, euler_ord, ord);
    }
};

namespace shortest_path_neg {
    template<typename T>
    vector<T> bellman_ford(int s, int n, span<array<T, 3>> edges) {
        T INF = numeric_limits<T>::max() / 2;
        vector<T> d(n, INF);
        d[s] = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (auto [u, v, w]: edges) {
                if (d[u] != INF && d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                }
            }
        }
        for (auto [u, v, w]: edges) {
            if (d[u] != INF && d[v] > d[u] + w) {
                return {};
            }
        }
        return d;
    }

    template<typename T>
    vector<vector<T>> floyd_yorshell(int n, span<vector<pair<int, T>>> graph) {
        T INF = numeric_limits<T>::max() / 2;
        vector d(n, vector<T>(n, INF));
        for (int i = 0; i < n; ++i) {
            d[i][i] = 0;
            for (auto [u, w]: graph[i]) {
                d[i][u] = min(d[i][u], w);
            }
        }
        for (int k = 0; k < n; ++k) {
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (d[i][k] != INF && d[k][j] != INF && d[i][j] > d[i][k] + d[k][j]) {
                        d[i][j] = max(-INF, d[i][k] + d[k][j]);
                    }
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (d[i][i] < 0) {
                return {};
            }
        }
        return d;
    }
};

namespace MST {
    ll kruskal(int n, span<array<int, 3>> edges) {
        ll res = 0;
        int comps = n;
        DSU dsu(n);
        ranges::sort(edges, [](const auto& lhs, const auto& rhs) { return lhs[2] < rhs[2]; });
        for (auto [u, v, w]: edges) {
            if (dsu.unite(u, v)) {
                res += w;
                comps--;
                if (comps == 1) break;
            }
        }
        if (comps > 1) {
            return -1;
        }
        return res;
    }

    ll prim(int n, span<vector<pii>> graph) {
        priority_queue<pii, vector<pii>, greater<>> q;
        ll res = 0;
        int cnt = 0;
        vector<bool> used(n, false);
        q.emplace(0, 0);
        while (!q.empty()) {
            auto [e_w, v] = q.top();
            q.pop();
            if (used[v]) continue;
            used[v] = true;
            res += e_w;
            ++cnt;
            for (auto [u, w]: graph[v]) {
                q.emplace(w, u);
            }
        }
        if (cnt < n) return -1;
        return res;
    }

    ll boruvka(int n, span<array<int, 3>> edges) {
        ll res = 0;
        int comps = n;
        vi min_edge(n);
        DSU dsu(n);
        while (comps > 1) {
            bool added = false;
            ranges::fill(min_edge, -1);
            for (int i = 0; i < sz(edges); ++i) {
                auto [u, v, w] = edges[i];
                int root_u = dsu.find_set(u);
                int root_v = dsu.find_set(v);
                if (root_u != root_v) {
                    if (min_edge[root_u] == -1 || w < edges[min_edge[root_u]][2]) {
                        min_edge[root_u] = i;
                    }
                    if (min_edge[root_v] == -1 || w < edges[min_edge[root_v]][2]) {
                        min_edge[root_v] = i;
                    }
                }
            }
            for (int i = 0; i < n; ++i) {
                if (min_edge[i] != -1) {
                    auto [u, v, w] = edges[min_edge[i]];
                    if (dsu.unite(u, v)) {
                        res += w;
                        --comps;
                        added = true;
                    }
                }
            }
            if (!added) break;
        }
        if (comps > 1) return -1;
        return res;
    }
};

// Range addition and range sum, compatible with HLD below.
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
    }

    void add_or(int a, int b) {
        add_impl(a ^ 1, b);
        add_impl(b ^ 1, a);
    }

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
        fill(all(used), false);
        ord.clear();
        fill(all(comp), -1);
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

struct centroid_decomp {
    span<vi> graph;
    vi size;
    vi centroid_parent;
    // vector<vector<pii>> ancestors;
    vector<bool> used;

    centroid_decomp(span<vi> g)
        : graph(g)
        , size(graph.size(), 0)
        , centroid_parent(graph.size(), -1)
        // , ancestors(graph.size())
        , used(graph.size(), false) {
        if (!graph.empty()) build(0, -1);
    }

    void meta_dfs(int v, int p) {
        size[v] = 1;
        for (int u: graph[v]) {
            if (u != p && !used[u]) {
                meta_dfs(u, v);
                size[v] += size[u];
            }
        }
    }

    int centroid(int v, int p, int n) {
        for (int u: graph[v]) {
            if (u != p && !used[u] && size[u] > n / 2) {
                return centroid(u, v, n);
            }
        }
        return v;
    }

    void build(int v, int p) {
        meta_dfs(v, -1);
        int c = centroid(v, -1, size[v]);
        used[c] = true;
        centroid_parent[c] = p;
        // ancestors[c].eb(0, c);
        // auto dfs = [&](auto& self, int v, int p, int dist) -> void {
        //     ancestors[v].eb(dist, c);
        //     for (int u: graph[v]) {
        //         if (!used[u] && u != p) {
        //             self(self, u, v, dist + 1);
        //         }
        //     }
        // };
        // for (int u: graph[c]) {
        //     if (!used[u]) {
        //         dfs(dfs, u, c, 1);
        //     }
        // }
        for (int u: graph[c]) {
            if (!used[u]) {
                build(u, c);
            }
        }
    }
};


void solve() {}
