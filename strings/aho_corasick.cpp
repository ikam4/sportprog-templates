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

template<size_t alphabet = 26, char min_char = 'a'>
class AhoCorasick {
public:
    struct Node {
        array<int, alphabet> to;
        int end_cnt = 0;
        int len = 0;
        int link = 0;
        int exit_link = 0;
        int id = -1;
        int matches = 0;

        int& operator[](char c) { return to[c - min_char]; }
        int operator[](char c) const { return to[c - min_char]; }

        Node() { to.fill(-1); }
    };

    vi ord;
    vector<Node> nodes;

    AhoCorasick() { clear(); }

    void clear() {
        nodes.clear();
        ord.clear();
        nodes.eb();
    }

    int insert(string_view s, int idx = -1) {
        assert(!s.empty());
        int u = 0;
        for (char c: s) {
            if (nodes[u][c] == -1) {
                nodes[u][c] = sz(nodes);
                nodes.eb();
                nodes.back().len = nodes[u].len + 1;
            }
            u = nodes[u][c];
        }
        nodes[u].end_cnt++;
        nodes[u].id = idx;
        return u;
    }

    void build() {
        ord.clear();
        ord.reserve(sz(nodes));
        for (int c = 0; c < alphabet; ++c) {
            int u = nodes[0].to[c];
            if (u != -1) {
                ord.pb(u);
                nodes[u].matches = nodes[u].end_cnt;
            } else {
                nodes[0].to[c] = 0;
            }
        }
        for (int head = 0; head < sz(ord); ++head) {
            int v = ord[head];
            for (size_t c = 0; c < alphabet; ++c) {
                int u = nodes[v].to[c];
                if (u != -1) {
                    nodes[u].link = nodes[nodes[v].link].to[c];
                    int l = nodes[u].link;
                    nodes[u].exit_link = (nodes[l].end_cnt > 0) ? l : nodes[l].exit_link;
                    nodes[u].matches = nodes[l].matches + nodes[u].end_cnt;
                    ord.pb(u);
                } else {
                    nodes[v].to[c] = nodes[nodes[v].link].to[c];
                }
            }
        }
    }

    vector<pii> find_all(string_view text) const {
        int u = 0;
        vector<pii> ans;
        for (int i = 0; i < sz(text); ++i) {
            u = nodes[u][text[i]];
            int cur = (nodes[u].end_cnt > 0 ? u : nodes[u].exit_link);
            while (cur != 0) {
                ans.eb(i, nodes[cur].id);
                cur = nodes[cur].exit_link;
            }
        }
        return ans;
    }

    ll count_all(string_view text) const {
        ll ans = 0;
        int u = 0;
        for (auto c: text) {
            u = nodes[u][c];
            ans += nodes[u].matches;
        }
        return ans;
    }

    vll count_each(string_view text, const vi& p_nodes) const {
        vll cnt(sz(nodes));
        int u = 0;
        for (auto c: text) {
            u = nodes[u][c];
            cnt[u]++;
        }
        for (int i = sz(ord) - 1; i >= 0; --i) {
            int v = ord[i];
            cnt[nodes[v].link] += cnt[v];
        }
        vll ans(sz(p_nodes));
        for (int i = 0; i < sz(p_nodes); ++i) {
            ans[i] = cnt[p_nodes[i]];
        }
        return ans;
    }

    int size() const { return sz(nodes); }

    const Node& operator[](int v) const { return nodes[v]; }

    Node& operator[](int v) { return nodes[v]; }

    bool is_match(int v) const { return nodes[v].matches > 0; }

    vector<vi> link_tree() const {
        vector<vi> g(sz(nodes));
        for (int u: ord) {
            g[nodes[u].link].pb(u);
        }
        return g;
    }
};

void solve() {}
