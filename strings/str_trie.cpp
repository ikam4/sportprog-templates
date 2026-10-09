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

class StrTrie {
public:
    struct Node {
        vector<pair<char, int>> to;
        int pass_cnt = 0;
        int end_cnt = 0;
        int operator[](char c) const {
            for (const auto& p: to) {
                if (p.fi == c) {
                    return p.se;
                }
            }
            return -1;
        }
        void add(char c, int v) { to.eb(c, v); }
    };

    vector<Node> nodes;

    StrTrie() { clear(); }

    void clear() {
        nodes.clear();
        nodes.eb();
    }

    void reserve(int max_nodes) { nodes.reserve(max_nodes); }

    int size() const { return nodes[0].pass_cnt; }

    bool empty() const { return size() == 0; }

    const Node& operator[](int v) const { return nodes[v]; }

    Node& operator[](int v) { return nodes[v]; }

    int insert(string_view s) {
        int u = 0;
        nodes[u].pass_cnt++;
        for (char c: s) {
            int fnd = nodes[u][c];
            if (fnd == -1) {
                fnd = sz(nodes);
                nodes[u].add(c, fnd);
                nodes.eb();
            }
            u = fnd;
            nodes[u].pass_cnt++;
        }
        nodes[u].end_cnt++;
        return u;
    }

    int find(string_view s) const {
        int u = 0;
        for (char c: s) {
            u = nodes[u][c];
            if (u == -1 || !nodes[u].pass_cnt) return -1;
        }
        return u;
    }

    int count(string_view s) const {
        int u = find(s);
        return (u != -1) ? nodes[u].end_cnt : 0;
    }

    int prefix_count(string_view s) const {
        int u = find(s);
        return (u != -1) ? nodes[u].pass_cnt : 0;
    }

    bool contains(string_view s) const { return count(s) > 0; }

    bool starts_with(string_view s) const { return prefix_count(s) > 0; }

    int lcp(string_view s) const {
        int u = 0, len = 0;
        for (char c: s) {
            u = nodes[u][c];
            if (u == -1 || !nodes[u].pass_cnt) break;
            ++len;
        }
        return len;
    }

    bool erase(string_view s) {
        if (count(s) == 0) return false;
        int u = 0;
        nodes[u].pass_cnt--;
        for (char c: s) {
            u = nodes[u][c];
            nodes[u].pass_cnt--;
        }
        nodes[u].end_cnt--;
        return true;
    }
};

void solve() {}
