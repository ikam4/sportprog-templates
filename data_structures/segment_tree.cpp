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

class segtree {
  struct Node { ll val = 0; };
  int n;
  vector<Node> tr;
public:
  segtree(const vi& other) : n(sz(other)), tr(4 * n) { if (n) build(0, 0, n, other); }
  void update(int pos, int val) { update(0, 0, n, pos, val); }
  ll query(int l, int r) { return query(0, 0, n, l, r + 1).val; }
private:
  Node merge(const Node& lhs, const Node& rhs) { return {lhs.val + rhs.val}; }
  void build(int idx, int cl, int cr, const vi& other) {
    if (cl + 1 == cr) {
      tr[idx].val = other[cl];
      return;
    }
    int mid = (cl + cr) / 2;
    build(2 * idx + 1, cl, mid, other);
    build(2 * idx + 2, mid, cr, other);
    tr[idx] = merge(tr[2 * idx + 1], tr[2 * idx + 2]);
  }
  void update(int idx, int cl, int cr, int pos, int val) {
    if (cl + 1 == cr) {
      tr[idx].val = val;
      return;
    }
    int mid = (cl + cr) / 2;
    if (pos < mid) update(2 * idx + 1, cl, mid, pos, val);
    else update(2 * idx + 2, mid, cr, pos, val);
    tr[idx] = merge(tr[2 * idx + 1], tr[2 * idx + 2]);
  }
  Node query(int idx, int cl, int cr, int l, int r) {
    if (cl >= r || cr <= l) return Node{};
    if (cl >= l && cr <= r) { return tr[idx]; }
    int mid = (cl + cr) / 2;
    return merge(query(2 * idx + 1, cl, mid, l, r), query(2 * idx + 2, mid, cr, l, r));
  }
};

void solve() {}
