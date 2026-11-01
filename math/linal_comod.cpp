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

template<typename T> struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix(int n, int m, T val = 0)
        : n(n)
        , m(m)
        , a(n, vector<T>(m, val)) {}

    Matrix(const vector<vector<T>>& init)
        : n(sz(init))
        , m(sz(init[0]))
        , a(init) {}

    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }

    static Matrix identity(int n) {
        Matrix res(n, n);
        for (int i = 0; i < n; ++i) res[i][i] = 1;
        return res;
    }

    Matrix operator*(const Matrix& other) const {
        assert(m == other.n);
        Matrix res(n, other.m);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < m; ++k) {
                for (int j = 0; j < other.m; ++j) {
                    res[i][j] += a[i][k] * other[k][j];
                }
            }
        }
        return res;
    }

    Matrix operator^(ll p) const {
        assert(n == m);
        Matrix res = identity(n);
        Matrix base = *this;
        while (p > 0) {
            if (p & 1) res = res * base;
            base = base * base;
            p >>= 1;
        }
        return res;
    }
};

struct LinearBasis {
    vector<ll> basis;

    void insert(ll x) {
        for (ll b: basis) x = min(x, x ^ b);
        if (x > 0) {
            basis.pb(x);
            sort(rall(basis));
        }
    }

    void merge(const LinearBasis& o) {
        for (ll b: o.basis) insert(b);
    }

    bool can_represent(ll x) const {
        for (ll b: basis) x = min(x, x ^ b);
        return x == 0;
    }

    ll max_xor(ll res = 0) const {
        for (ll b: basis) res = max(res, res ^ b);
        return res;
    }

    int size() const { return sz(basis); }
    void clear() { basis.clear(); }
};

namespace SLAE {
    const int INF = 2; // 0 — нет решений, 1 — одно, INF — бесконечно
    // where[i] = j -> x_i - базисная в строке j, where[i] = -1 -> x_i - свободная
    // Вещественная система: a[n][m + 1]
    int gauss(vector<vector<double>> a, vector<double>& ans) {
        int n = sz(a), m = sz(a[0]) - 1, row = 0;
        vi where(m, -1);
        for (int col = 0; col < m && row < n; ++col) {
            int sel = row;
            for (int i = row; i < n; ++i)
                if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
            if (abs(a[sel][col]) < EPS) continue;
            swap(a[sel], a[row]);
            where[col] = row;
            for (int i = 0; i < n; ++i)
                if (i != row) {
                    double c = a[i][col] / a[row][col];
                    for (int j = col; j <= m; ++j) a[i][j] -= a[row][j] * c;
                }
            ++row;
        }
        ans.assign(m, 0);
        for (int i = 0; i < m; ++i)
            if (where[i] != -1) ans[i] = a[where[i]][m] / a[where[i]][i];
        for (int i = 0; i < n; ++i) {
            double sum = 0;
            for (int j = 0; j < m; ++j) sum += ans[j] * a[i][j];
            if (abs(sum - a[i][m]) > EPS) return 0;
        }
        for (int i = 0; i < m; ++i)
            if (where[i] == -1) return INF;
        return 1;
    }

    // Система по модулю MOD: a[n][m + 1]
    int gauss_mod(vector<vi> a, vi& ans) {
        int n = sz(a), m = sz(a[0]) - 1, row = 0;
        vi where(m, -1);
        for (int col = 0; col < m && row < n; ++col) {
            int sel = row;
            for (int i = row; i < n; ++i)
                if (a[i][col]) {
                    sel = i;
                    break;
                }
            if (!a[sel][col]) continue;
            swap(a[sel], a[row]);
            where[col] = row;
            int inv = modpow(a[row][col], MOD - 2);
            for (int j = col; j <= m; ++j) a[row][j] = (ull) a[row][j] * inv % MOD;
            for (int i = 0; i < n; ++i)
                if (i != row && a[i][col]) {
                    int c = a[i][col];
                    for (int j = col; j <= m; ++j) {
                        a[i][j] = (a[i][j] - (ll) a[row][j] * c % MOD + MOD) % MOD;
                        if (a[i][j] < 0) a[i][j] += MOD;
                    }
                }
            ++row;
        }
        ans.assign(m, 0);
        for (int i = 0; i < m; ++i)
            if (where[i] != -1) ans[i] = a[where[i]][m];
        for (int i = 0; i < n; ++i) {
            ull sum = 0;
            for (int j = 0; j < m; ++j) sum = (sum + (ull) ans[j] * a[i][j]) % MOD;
            if (sum != (ull) a[i][m]) return 0;
        }
        for (int i = 0; i < m; ++i)
            if (where[i] == -1) return INF;
        return 1;
    }

    // XOR-система: b_i лежит в позиции a[i][m]
    template<size_t N> int gauss_bitset(int n, int m, vector<bitset<N>>& a, bitset<N>& ans) {
        vi where(m, -1);
        for (int col = 0, row = 0; col < m && row < n; ++col) {
            for (int i = row; i < n; ++i)
                if (a[i][col]) {
                    swap(a[i], a[row]);
                    break;
                }
            if (!a[row][col]) continue;
            where[col] = row;
            for (int i = 0; i < n; ++i)
                if (i != row && a[i][col]) a[i] ^= a[row];
            ++row;
        }
        ans.reset();
        for (int i = 0; i < m; ++i)
            if (where[i] != -1) ans[i] = a[where[i]][m];
        for (int i = 0; i < n; ++i)
            if (((a[i] & ans).count() & 1) != a[i][m]) return 0;
        for (int i = 0; i < m; ++i)
            if (where[i] == -1) return INF;
        return 1;
    }
};

void solve() {}
