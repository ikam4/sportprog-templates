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

template<int bits = 31>
class BitTrie {
public:
    struct Node {
        array<int, 2> to;
        int pass_cnt = 0;
        int end_cnt = 0;
        int& operator[](int idx) { return to[idx]; }
        const int& operator[](int idx) const { return to[idx]; }
        Node()
            : to{-1, -1} {}
    };

    vector<Node> nodes;

    BitTrie() { clear(); }

    void clear() {
        nodes.clear();
        nodes.eb();
    }

    void reserve(int max_nodes) { nodes.reserve(max_nodes); }

    int size() const { return nodes[0].pass_cnt; }

    bool empty() const { return size() == 0; }

    const Node& operator[](int v) const { return nodes[v]; }

    Node& operator[](int v) { return nodes[v]; }

    void insert(ull val) {
        int u = 0;
        nodes[u].pass_cnt++;
        for (int i = bits - 1; i >= 0; --i) {
            int j = (val >> i) & 1;
            if (nodes[u][j] == -1) {
                nodes[u][j] = sz(nodes);
                nodes.eb();
            }
            u = nodes[u][j];
            nodes[u].pass_cnt++;
        }
        nodes[u].end_cnt++;
    }

    int count(ull val) const {
        int u = 0;
        for (int i = bits - 1; i >= 0; --i) {
            int j = (val >> i) & 1;
            if (nodes[u][j] == -1 || !nodes[nodes[u][j]].pass_cnt) return 0;
            u = nodes[u][j];
        }
        return nodes[u].end_cnt;
    }

    bool erase(ull val) {
        int u = 0;
        array<int, bits + 1> path;
        path[0] = 0;
        for (int i = bits - 1; i >= 0; --i) {
            int j = (val >> i) & 1;
            if (nodes[u][j] == -1 || nodes[nodes[u][j]].pass_cnt == 0) {
                return false;
            }
            u = nodes[u][j];
            path[bits - i] = u;
        }
        if (nodes[u].end_cnt == 0) return false;
        for (int i = 0; i <= bits; ++i) {
            nodes[path[i]].pass_cnt--;
        }
        nodes[u].end_cnt--;
        return true;
    }

    ull mx_xor(ull val) const {
        assert(!empty());
        int u = 0;
        ull mx = 0;
        for (int i = bits - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            mx <<= 1;
            if (nodes[u][bit ^ 1] != -1 && nodes[nodes[u][bit ^ 1]].pass_cnt) {
                mx |= 1;
                u = nodes[u][bit ^ 1];
            } else {
                u = nodes[u][bit];
            }
        }
        return mx;
    }

    ull mn_xor(ull val) const {
        assert(!empty());
        int u = 0;
        ull mn = 0;
        for (int i = bits - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            mn <<= 1;
            if (nodes[u][bit] != -1 && nodes[nodes[u][bit]].pass_cnt) {
                u = nodes[u][bit];
            } else {
                mn |= 1;
                u = nodes[u][bit ^ 1];
            }
        }
        return mn;
    }

    // k — индекс наименьшего элемента, нумерация с нуля
    ull kth(int k) const {
        assert(k >= 0 && k < size());
        int u = 0;
        ull res = 0;
        for (int i = bits - 1; i >= 0; --i) {
            res <<= 1;
            int left = nodes[u][0];
            int left_cnt = (left != -1) ? nodes[left].pass_cnt : 0;
            if (k < left_cnt) {
                u = left;
            } else {
                res |= 1;
                k -= left_cnt;
                u = nodes[u][1];
            }
        }
        return res;
    }

    int order_of_key(ull val) const {
        if constexpr (bits < 64) if (val >= (1ULL << bits)) return size();
        int u = 0, ans = 0;
        for (int i = bits - 1; i >= 0; --i) {
            int bit = (val >> i) & 1;
            if (bit == 1) {
                int left = nodes[u][0];
                if (left != -1) ans += nodes[left].pass_cnt;
            }
            u = nodes[u][bit];
            if (u == -1 || !nodes[u].pass_cnt) break;
        }
        return ans;
    }

    int count_xor_less(ull val, ull limit) const {
        if constexpr (bits < 64) if (limit >= (1ULL << bits)) return size();
        int u = 0, ans = 0;
        for (int i = bits - 1; i >= 0; --i) {
            int v_bit = (val >> i) & 1;
            int l_bit = (limit >> i) & 1;
            if (l_bit == 1) {
                int same = nodes[u][v_bit];
                if (same != -1) ans += nodes[same].pass_cnt;
                u = nodes[u][v_bit ^ 1];
            } else {
                u = nodes[u][v_bit];
            }
            if (u == -1 || !nodes[u].pass_cnt) break;
        }
        return ans;
    }

    bool contains(ull val) const { return count(val) > 0; }

    ull min_val() const {
        assert(!empty());
        return kth(0);
    }

    ull max_val() const {
        assert(!empty());
        return kth(size() - 1);
    }

    ull lower_bound(ull val) const {
        int idx = order_of_key(val);
        return (idx < size()) ? kth(idx) : -1ULL;
    }

    ull upper_bound(ull val) const {
        if (val == numeric_limits<ull>::max()) return -1ULL;
        int idx = order_of_key(val + 1);
        return (idx < size()) ? kth(idx) : -1ULL;
    }
};

void solve() {}
