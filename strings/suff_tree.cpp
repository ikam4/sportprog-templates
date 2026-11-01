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

template<size_t alphabet = 27, char min_char = 'a'> class SuffTree {
public:
    struct Node {
        array<int, alphabet> to;
        int start = -1, end = -1, link = 0;
        int len = 0;
        int leaf_idx = -1;

        static int get_c(char c) { return (c == '$') ? (int) alphabet - 1 : (c - min_char); }

        int& operator[](char c) { return to[get_c(c)]; }
        int operator[](char c) const { return to[get_c(c)]; }

        Node() { to.fill(-1); }
        Node(int start, int end)
            : start(start)
            , end(end) {
            to.fill(-1);
        }
    };

    string s;
    vector<Node> nodes;
    int active_node = 0, active_edge = 0, active_len = 0, rem = 0;
    int leaf_end = 0;

    SuffTree() { clear(); }

    SuffTree(string_view str) { build(str); }

    void clear() {
        nodes.clear();
        s.clear();
        nodes.eb();
        active_node = active_edge = active_len = rem = 0;
        leaf_end = 0;
    }

    void build(string_view str) {
        clear();
        s = string(str) + '$';
        nodes.reserve(2 * sz(s) + 5);
        for (int i = 0; i < sz(s); ++i) {
            extend(i);
        }
        calc_len();
    }

    int edge_len(int u) const {
        if (nodes[u].start == -1) return 0; // в корень ребро не ведет
        return min(nodes[u].end, leaf_end) - nodes[u].start;
    }

    vi get_topo() const {
        vi q = {0};
        q.reserve(sz(nodes));
        for (int i = 0; i < sz(q); ++i) {
            int u = q[i];
            for (int c = 0; c < (int) alphabet; ++c) {
                int v = nodes[u].to[c];
                if (v != -1) q.pb(v);
            }
        }
        return q;
    }

    vi get_leaves() const {
        vi order = get_topo();
        vi leaves(sz(nodes), 0);
        for (int i = sz(order) - 1; i >= 0; --i) {
            int u = order[i];
            leaves[u] = (nodes[u].leaf_idx != -1 ? 1 : 0);
            for (int c = 0; c < (int) alphabet; ++c) {
                int v = nodes[u].to[c];
                if (v != -1) leaves[u] += leaves[v];
            }
        }
        return leaves;
    }

    vi get_parents() const {
        vi par(sz(nodes), -1);
        for (int u = 0; u < sz(nodes); ++u) {
            for (int c = 0; c < (int) alphabet; ++c) {
                int v = nodes[u].to[c];
                if (v != -1) par[v] = u;
            }
        }
        return par;
    }

    int real_len(int u) const {
        if (u <= 0) return 0;
        return nodes[u].len - (nodes[u].leaf_idx != -1 ? 1 : 0);
    }

    string kth_substring(ll k, bool distinct = true) const {
        if (k <= 0) return "";
        int n = sz(nodes);
        vi order = get_topo();
        vi leaves = distinct ? vi() : get_leaves();
        vll dp(n, 0);
        for (int i = sz(order) - 1; i >= 0; --i) {
            int u = order[i];
            for (int c = 0; c < (int) alphabet - 1; ++c) {
                int v = nodes[u].to[c];
                if (v == -1) continue;
                int elen = real_len(v) - nodes[u].len;
                if (elen <= 0) continue;
                ll mult = distinct ? 1LL : leaves[v];
                dp[u] += elen * mult + dp[v];
            }
        }
        if (k > dp[0]) return "";
        string ans;
        int u = 0;
        while (k > 0) {
            for (int c = 0; c < (int) alphabet - 1; ++c) {
                int v = nodes[u].to[c];
                if (v == -1) continue;
                int elen = real_len(v) - nodes[u].len;
                if (elen <= 0) continue;
                ll mult = distinct ? 1LL : leaves[v];
                ll edge_cnt = elen * mult;
                ll cur = edge_cnt + dp[v];
                if (k <= edge_cnt) {
                    ll take = distinct ? k : (k + mult - 1) / mult;
                    ans += s.substr(nodes[v].start, take);
                    return ans;
                }
                if (k <= cur) {
                    ans += s.substr(nodes[v].start, elen);
                    k -= edge_cnt;
                    u = v;
                    break;
                }
                k -= cur;
            }
        }

        return ans;
    }

    int size() const { return sz(nodes); }
    const Node& operator[](int v) const { return nodes[v]; }
    Node& operator[](int v) { return nodes[v]; }

private:
    void calc_len() {
        nodes[0].len = 0;
        vi order = get_topo();
        each(u, order) {
            for (int c = 0; c < (int) alphabet; ++c) {
                int v = nodes[u].to[c];
                if (v != -1) {
                    nodes[v].len = nodes[u].len + edge_len(v);
                }
            }
        }
    }

    bool propagate(int next) {
        int len = edge_len(next);
        if (active_len >= len) {
            active_edge += len;
            active_len -= len;
            active_node = next;
            return true;
        }
        return false;
    }

    void next_suff(int pos) {
        rem--;
        if (active_node == 0 && active_len > 0) {
            active_len--;
            active_edge = pos - rem + 1;
        } else if (active_node != 0) {
            active_node = nodes[active_node].link;
        }
    }

    int create_leaf(int pos) {
        int leaf = sz(nodes);
        nodes.eb(pos, INF);
        nodes[leaf].leaf_idx = pos - rem + 1;
        return leaf;
    }

    void extend(int pos) {
        leaf_end = pos + 1; // полуинтервалы [start, end)
        rem++;
        int last = 0;
        while (rem > 0) {
            if (active_len == 0) {
                active_edge = pos;
            }
            char c = s[active_edge];
            if (nodes[active_node][c] == -1) { // сработает только когда active_len == 0
                nodes[active_node][c] = create_leaf(pos);
                if (last != 0) {
                    nodes[last].link = active_node;
                    last = 0;
                }
                next_suff(pos);
            } else {
                int next = nodes[active_node][c];
                if (propagate(next)) continue;
                char edge_c = s[nodes[next].start + active_len];
                if (edge_c == s[pos]) {
                    if (last != 0) {
                        nodes[last].link = active_node;
                        last = 0;
                    }
                    active_len++;
                    break;
                }
                int split = sz(nodes);
                nodes.eb(nodes[next].start, nodes[next].start + active_len);
                nodes[active_node][c] = split;
                nodes[split][s[pos]] = create_leaf(pos);
                nodes[next].start += active_len;
                nodes[split][s[nodes[next].start]] = next;
                if (last != 0) {
                    nodes[last].link = split;
                }
                last = split;
                next_suff(pos);
            }
        }
    }
};

void solve() {}
