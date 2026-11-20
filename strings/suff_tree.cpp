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

    vi get_leaves() const { return count_leaves(get_topo()); }

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
        vi leaves = distinct ? vi() : count_leaves(order);
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
    vi count_leaves(const vi& order) const {
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
