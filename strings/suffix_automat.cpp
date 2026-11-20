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

template<size_t alphabet = 26, char min_char = 'a'> class SuffAuto {
public:
    struct Node {
        array<int, alphabet> to;
        int link = -1;
        int len = 0;
        int end_cnt = 0;

        int& operator[](char c) { return to[c - min_char]; }
        int operator[](char c) const { return to[c - min_char]; }

        Node() { to.fill(-1); }
    };

    int last = 0;
    bool endpos_built = false;
    vector<Node> nodes;
    vi cnt;

    SuffAuto(size_t max_len = 0) { clear(max_len); }

    void clear(size_t max_len = 0) {
        last = 0;
        endpos_built = false;
        nodes.clear();
        cnt.clear();
        if (max_len > 0) {
            nodes.reserve(2 * max_len);
            cnt.reserve(2 * max_len);
        }
        nodes.eb();
    }

    int extend(char c) {
        endpos_built = false;

        // GSAM
        if (nodes[last][c] != -1) {
            int q = nodes[last][c];
            if (nodes[q].len == nodes[last].len + 1) {
                ++nodes[q].end_cnt;
                return last = q;
            }
            int clone = sz(nodes);
            nodes.eb(nodes[q]);
            nodes[clone].len = nodes[last].len + 1;
            nodes[clone].end_cnt = 1;
            int u = last;
            while (u != -1 && nodes[u][c] == q) {
                nodes[u][c] = clone;
                u = nodes[u].link;
            }
            nodes[q].link = clone;
            return last = clone;
        }

        int cur = sz(nodes);
        nodes.eb();
        nodes[cur].len = nodes[last].len + 1;
        nodes[cur].end_cnt = 1;
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
                nodes[clone].len = nodes[u].len + 1;
                nodes[clone].end_cnt = 0;
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
        // last = 0; // для GSAM
        for (char c: s) {
            extend(c);
        }
    }

    vi topo_sort() const {
        int n = 0;
        for (const auto& node: nodes) n = max(n, node.len);
        vi cnt_len(n + 1, 0);
        for (const auto& i: nodes) {
            cnt_len[i.len]++;
        }
        for (int i = 1; i <= n; ++i) {
            cnt_len[i] += cnt_len[i - 1];
        }
        vi ord(sz(nodes));
        for (int i = sz(nodes) - 1; i >= 0; --i) {
            ord[--cnt_len[nodes[i].len]] = i;
        }
        return ord;
    }

    void build_endpos() {
        if (endpos_built) return;
        const vi ord = topo_sort();
        cnt.resize(sz(nodes));
        for (int v = 0; v < sz(nodes); ++v) {
            cnt[v] = nodes[v].end_cnt;
        }
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
