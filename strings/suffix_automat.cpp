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

template<size_t alphabet = 26, char min_char = 'a'> class SuffAuto {
public:
    struct Node {
        array<int, alphabet> to;
        int link = -1;
        int len = 0;
        int first_pos = -1;

        int& operator[](char c) { return to[c - min_char]; }
        int operator[](char c) const { return to[c - min_char]; }

        Node() { to.fill(-1); }
    };

    int last = 0;
    bool endpos_built = false;
    bool kth_duplicates = false;
    vector<Node> nodes;
    vi cnt, ord;
    vll ways;

    SuffAuto(size_t max_len = 0) { clear(max_len); }

    void clear(size_t max_len = 0) {
        last = 0;
        endpos_built = false;
        kth_duplicates = false;
        nodes.clear();
        cnt.clear();
        ord.clear();
        ways.clear();
        if (max_len > 0) {
            nodes.reserve(2 * max_len);
            cnt.reserve(2 * max_len);
        }
        nodes.eb();
        cnt.eb(0);
    }

    int extend(char c) {
        //GSAM
        // if (nodes[last][c] != -1) {
            // int q = nodes[last][c];
            // if (nodes[q].len == nodes[last].len + 1) {
                // return last = q;
            // }
            // int clone = sz(nodes);
            // nodes.eb(nodes[q]);
            // cnt.eb(0);
            // nodes[clone].len = nodes[last].len + 1;
            // int u = last;
            // while (u != -1 && nodes[u][c] == q) {
                // nodes[u][c] = clone;
                // u = nodes[u].link;
            // }
            // nodes[q].link = clone;
            // return last = clone;
        // }

        int cur = sz(nodes);
        nodes.eb();
        cnt.eb(1);
        nodes[cur].len = nodes[last].len + 1;
        nodes[cur].first_pos = nodes[cur].len - 1;

        int u = last;
        while (u != -1 && nodes[u][c] == -1) {
            nodes[u][c] = cur;
            u = nodes[u].link;
        }

        if (u == -1) {
            nodes[cur].link = 0;
        } else {
            int v = nodes[u][c];
            if (nodes[v].len == nodes[u].len + 1) {
                nodes[cur].link = v;
            } else {
                int clone = sz(nodes);
                nodes.eb(nodes[v]);
                cnt.eb(0);
                nodes[clone].len = nodes[u].len + 1;
                while (u != -1 && nodes[u][c] == v) {
                    nodes[u][c] = clone;
                    u = nodes[u].link;
                }
                nodes[v].link = clone;
                nodes[cur].link = clone;
            }
        }
        return last = cur;
    }

    void build(string_view s) {
        for (char c: s) {
            extend(c);
        }
    }

    void topo_sort() {
        int n = nodes[last].len;
        // int n = 0;
        // for (const auto& node: nodes) n = max(n, node.len); // compatible with GSAM
        vi cnt_len(n + 1, 0);
        for (const auto& i: nodes) {
            cnt_len[i.len]++;
        }
        for (int i = 1; i <= n; ++i) {
            cnt_len[i] += cnt_len[i - 1];
        }
        ord.assign(sz(nodes), 0);
        for (int i = sz(nodes) - 1; i >= 0; --i) {
            ord[--cnt_len[nodes[i].len]] = i;
        }
    }

    void build_endpos() {
        if (endpos_built) return;
        if (ord.empty()) topo_sort();
        for (int i = sz(nodes) - 1; i >= 0; --i) {
            int v = ord[i];
            if (nodes[v].link != -1) {
                cnt[nodes[v].link] += cnt[v];
            }
        }
        endpos_built = true;
    }

    int min_len(int v) const { return v == 0 ? 0 : nodes[nodes[v].link].len + 1; }

    int get_state(string_view s) const {
        int v = 0;
        for (char c: s) {
            if (nodes[v][c] == -1) return -1;
            v = nodes[v][c];
        }
        return v;
    }

    int count_occs(string_view s) const {
        assert(endpos_built);
        int v = get_state(s);
        return v == -1 ? 0 : cnt[v];
    }

    int first_occ(string_view s) const {
        int v = get_state(s);
        return v == -1 ? -1 : nodes[v].first_pos - sz(s) + 1;
    }

    void prepare_kth(bool duplicates = false) {
        kth_duplicates = duplicates;
        if (duplicates && !endpos_built) build_endpos();
        if (ord.empty()) topo_sort();
        ways.assign(sz(nodes), 0);
        for (int i = sz(nodes) - 1; i >= 0; --i) {
            int u = ord[i];
            if (u != 0) {
                ways[u] = duplicates ? cnt[u] : 1;
            }
            for (size_t c = 0; c < alphabet; ++c) {
                int v = nodes[u].to[c];
                if (v != -1) {
                    ways[u] += ways[v];
                }
            }
        }
    }

    string kth_substr(ll k) const {
        assert(k > 0 && !ways.empty());
        if (k > ways[0]) return "";
        string res;
        int u = 0;
        while (k > 0) {
            for (size_t c = 0; c < alphabet; ++c) {
                int v = nodes[u].to[c];
                if (v == -1) continue;
                if (k <= ways[v]) {
                    u = v;
                    res += static_cast<char>(min_char + c);
                    ll cur = kth_duplicates ? cnt[u] : 1;
                    if (k <= cur) return res;
                    k -= cur;
                    break;
                } else {
                    k -= ways[v];
                }
            }
        }
        return res;
    }

    int size() const { return sz(nodes); }

    const Node& operator[](int v) const { return nodes[v]; }

    Node& operator[](int v) { return nodes[v]; }

    vector<vi> link_tree() const {
        vector<vi> link_tree(sz(nodes));
        for (int v = 1; v < sz(nodes); ++v) {
            link_tree[nodes[v].link].pb(v);
        }
        return link_tree;
    }
};

void solve() {}
