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
    bool built = false;
    un_mp<int, vi> previous_ids;

    AhoCorasick() { clear(); }

    void clear() {
        built = false;
        nodes.clear();
        ord.clear();
        previous_ids.clear();
        nodes.eb();
    }

    int insert(string_view s, int idx = -1) {
        if (built) return -1;
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
        if (nodes[u].end_cnt > 0) previous_ids[u].pb(nodes[u].id);
        nodes[u].end_cnt++;
        nodes[u].id = idx;
        return u;
    }

    void build() {
        if (built) return;
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
        built = true;
    }

    vector<pii> find_all(string_view text) const {
        int u = 0;
        vector<pii> ans;
        for (int i = 0; i < sz(text); ++i) {
            u = nodes[u][text[i]];
            int cur = (nodes[u].end_cnt > 0 ? u : nodes[u].exit_link);
            while (cur != 0) {
                if (nodes[cur].end_cnt > 1) {
                    for (int id: previous_ids.at(cur)) ans.eb(i, id);
                }
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
