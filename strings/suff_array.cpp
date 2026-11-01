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
    // freopen("sufflcp.in", "r", stdin);
    // freopen("sufflcp.out", "w", stdout);
    int T = 1;
    // cin >> T;
    while (T--) solve();
    return 0;
}

vi suff_array(string s) {
    s += '\0';
    int n = sz(s);
    const int alphabet = 256;
    vi p(n), cnt(max(alphabet, n), 0);
    vi c(n), pn(n), cn(n);
    for (int i = 0; i < n; ++i) c[i] = (unsigned char) s[i];
    for (int x: c) cnt[x]++;
    for (int i = 1; i < alphabet; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) p[--cnt[c[i]]] = i;
    cn[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; ++i) {
        if (c[p[i]] != c[p[i - 1]]) classes++;
        cn[p[i]] = classes - 1;
    }
    swap(c, cn);
    for (int h = 0; (1 << h) < n; ++h) {
        int shift = 1 << h;
        for (int i = 0; i < n; ++i) {
            pn[i] = p[i] - shift;
            if (pn[i] < 0) pn[i] += n;
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; ++i) cnt[c[pn[i]]]++;
        for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
        for (int i = n - 1; i >= 0; --i) p[--cnt[c[pn[i]]]] = pn[i];
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; ++i) {
            int r1 = p[i] + shift, r2 = p[i - 1] + shift;
            if (r1 >= n) r1 -= n;
            if (r2 >= n) r2 -= n;
            if (c[p[i]] != c[p[i - 1]] || c[r1] != c[r2]) classes++;
            cn[p[i]] = classes - 1;
        }
        swap(c, cn);
        if (classes == n) break;
    }
    return vi(p.begin() + 1, p.end());
}

vi lcp(string_view s, const vi& sa) {
    int n = sz(s);
    if (n <= 1) return {};
    vi rank(n);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    vi lcp(n - 1, 0);
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[rank[i]] = k;
        if (k > 0) {
            --k;
        }
    }
    return lcp;
}

void solve() {}
