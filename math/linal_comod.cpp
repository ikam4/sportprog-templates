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

template<typename T> struct Matrix {
    int n, m;
    vector<vector<T>> a;

    Matrix(int n, int m, T val = 0)
        : n(n)
        , m(m)
        , a(n, vector<T>(m, val)) {}

    Matrix(const vector<vector<T>>& init)
        : n(sz(init))
        , m(init.empty() ? 0 : sz(init[0]))
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
            p >>= 1;
            if (p > 0) base = base * base;
        }
        return res;
    }
};

struct LinearBasis {
    vector<ull> basis;

    void insert(ull x) {
        for (ull b: basis) x = min(x, x ^ b);
        if (x > 0) {
            basis.pb(x);
            sort(rall(basis));
        }
    }

    void merge(const LinearBasis& o) {
        for (ull b: o.basis) insert(b);
    }

    bool can_represent(ull x) const {
        for (ull b: basis) x = min(x, x ^ b);
        return x == 0;
    }

    ull max_xor(ull res = 0) const {
        for (ull b: basis) res = max(res, res ^ b);
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
            ld sum = 0;
            ld scale = abs(a[i][m]);
            for (int j = 0; j < m; ++j) {
                ld term = (ld) ans[j] * a[i][j];
                sum += term;
                scale += abs(term);
            }
            if (abs(sum - a[i][m]) > EPS * max(1.0L, scale)) return 0;
        }
        for (int i = 0; i < m; ++i)
            if (where[i] == -1) return INF;
        return 1;
    }

    // Система по модулю MOD: a[n][m + 1]
    int gauss_mod(vector<vi> a, vi& ans) {
        for (auto& coefficients: a) {
            for (int& x: coefficients) {
                x %= MOD;
                if (x < 0) x += MOD;
            }
        }
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
