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
} // старший 1-бит (нумерация с нуля)
inline int lsb(ll x) {
    return x ? __builtin_ctzll((ull) x) : -1;
} // младший 1-бит (нумерация с нуля)

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
        if (bits < 64 && val >= ((1ULL << bits) - 1)) return -1ULL;
        int idx = order_of_key(val + 1);
        return (idx < size()) ? kth(idx) : -1ULL;
    }
};

void solve() {}
