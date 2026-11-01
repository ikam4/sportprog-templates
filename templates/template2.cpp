// BEST TEMPLATE EVER
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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

template<class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template<class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}
    template<class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};
template<class Fun>
decltype(auto) y_comb(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
// y_comb([&](...) -> type {...}) - рекурсия лямбд внутри другой функции

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

inline uint64_t splitmix64(uint64_t x) noexcept {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
static uint64_t sm_state = (uint64_t) chrono::steady_clock::now().time_since_epoch().count() ^
                           (uint64_t) (uintptr_t) new int;
inline uint64_t rnd() noexcept {
    sm_state += 0x9e3779b97f4a7c15ULL;
    return splitmix64(sm_state);
}

struct chash {
    static inline uint64_t seed() noexcept {
        static const uint64_t s = rnd();
        return s;
    }
    inline size_t operator()(uint64_t x) const noexcept {
        uint64_t sd = seed();
        return (size_t) splitmix64(x + sd);
    }
    inline size_t operator()(int64_t x) const noexcept {
        uint64_t sd = seed();
        return (size_t) splitmix64((uint64_t) x + sd);
    }
    inline size_t operator()(uint32_t x) const noexcept {
        uint64_t sd = seed();
        return (size_t) splitmix64((uint64_t) x + sd);
    }
    inline size_t operator()(int32_t x) const noexcept {
        uint64_t sd = seed();
        return (size_t) splitmix64((uint64_t) (int64_t) x + sd);
    }
    inline size_t operator()(string_view s) const noexcept {
        uint64_t sd = seed();
        const uint8_t* p = (const uint8_t*) s.data();
        size_t n = s.size();
        uint64_t h = splitmix64(sd ^ (uint64_t) n);
        while (n >= 8) {
            uint64_t x;
            memcpy(&x, p, 8);
            h = splitmix64(h ^ (x + sd));
            p += 8;
            n -= 8;
        }
        if (n) {
            uint64_t x = 0;
            memcpy(&x, p, n);
            h = splitmix64(h ^ (x + sd));
        }
        return (size_t) h;
    }
    inline size_t operator()(const string& s) const noexcept { return (*this)(string_view(s)); }
    inline size_t operator()(const char* s) const noexcept {
        return (*this)(string_view(s, strlen(s)));
    }
    template<class A, class B>
    inline size_t operator()(const pair<A, B>& p) const noexcept {
        uint64_t a = (uint64_t) (*this)(p.first);
        uint64_t b = (uint64_t) (*this)(p.second);
        return (size_t) splitmix64(a ^ (b + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2)));
    }
};

template<class K, class V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, chash>;
template<class K>
using hash_set = __gnu_pbds::gp_hash_table<K, __gnu_pbds::null_type, chash>;
template<class T>
using ord_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                                 __gnu_pbds::tree_order_statistics_node_update>;
// order_of_key(x) - сколько меньше x, find_by_order(x) - итератор на элемент на позиции x (0-based)

template<typename T, T MOD>
struct ModInt {
    T v;
    inline ModInt() noexcept : v(0) {}
    template<typename U>
    inline ModInt(U x) noexcept {
        set(x);
    }
    template<typename U>
    inline void set(U x) noexcept {
        if constexpr (U(-1) < U(0)) {
            __int128 t = (__int128) x % (__int128) MOD;
            if (t < 0) t += MOD;
            v = (T) t;
        } else {
            __uint128_t t = (__uint128_t) x % (__uint128_t) MOD;
            v = (T) t;
        }
    }
    inline explicit operator T() const noexcept { return v; }
    friend inline ostream& operator<<(ostream& os, const ModInt& a) { return os << a.v; }
    friend inline istream& operator>>(istream& is, ModInt& a) {
        long long x;
        is >> x;
        a.set(x);
        return is;
    }
    inline ModInt& operator+=(const ModInt& o) noexcept {
        v = (T) (((__int128) v + o.v) % MOD);
        return *this;
    }
    inline ModInt& operator-=(const ModInt& o) noexcept {
        v = (T) (((__int128) v - o.v + MOD) % MOD);
        return *this;
    }
    inline ModInt& operator*=(const ModInt& o) noexcept {
        if constexpr (sizeof(T) <= 4) {
            v = (T) (1ull * v * o.v % MOD);
        } else {
            v = (T) ((__int128) v * o.v % MOD);
        }
        return *this;
    }
    static inline ModInt pow(ModInt a, long long e) noexcept {
        ModInt r = 1;
        for (; e; e >>= 1, a *= a)
            if (e & 1) r *= a;
        return r;
    }
    static inline ModInt inv(ModInt a) noexcept { return pow(a, (long long) MOD - 2); }
    inline ModInt& operator/=(const ModInt& o) noexcept { return *this *= inv(o); }
    friend inline ModInt operator+(ModInt a, const ModInt& b) noexcept { return a += b; }
    friend inline ModInt operator-(ModInt a, const ModInt& b) noexcept { return a -= b; }
    friend inline ModInt operator*(ModInt a, const ModInt& b) noexcept { return a *= b; }
    friend inline ModInt operator/(ModInt a, const ModInt& b) noexcept { return a /= b; }
    friend inline bool operator==(const ModInt& a, const ModInt& b) noexcept { return a.v == b.v; }
    friend inline bool operator!=(const ModInt& a, const ModInt& b) noexcept { return a.v != b.v; }
};

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
using mint = ModInt<int, MOD>;

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

void solve() {}
