// BEST TEMPLATE EVER by ikam
#pragma GCC optimize("O3,unroll-loops")
#ifdef FAST_X86
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#endif
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

inline istream& operator>>(istream& in, i128& value) {
    string token;
    if (!(in >> token)) return in;
    const bool negative = token[0] == '-';
    size_t i = negative || token[0] == '+' ? 1 : 0;
    if (i == token.size()) {
        in.setstate(ios::failbit);
        return in;
    }
    const __uint128_t limit = (__uint128_t(1) << 127) - 1 + negative;
    const __uint128_t cutoff = limit / 10;
    const unsigned last_digit = limit % 10;
    __uint128_t magnitude = 0;
    for (; i < token.size(); ++i) {
        unsigned digit = token[i] - '0';
        if (digit > 9 || magnitude > cutoff || (magnitude == cutoff && digit > last_digit)) {
            in.setstate(ios::failbit);
            return in;
        }
        magnitude = magnitude * 10 + digit;
    }
    value = negative && magnitude ? -1 - (i128) (magnitude - 1) : (i128) magnitude;
    return in;
}

inline ostream& operator<<(ostream& out, i128 value) {
    const bool negative = value < 0;
    __uint128_t magnitude = (__uint128_t) value;
    if (negative) magnitude = -magnitude;
    char buffer[40];
    char* end = buffer + sizeof(buffer);
    char* first = end;
    do {
        *--first = char('0' + magnitude % 10);
        magnitude /= 10;
    } while (magnitude);
    if (negative) *--first = '-';
    return out << string_view(first, end - first);
}

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
    template<class T> ostream& print(const T& value) { cerr << value; return cerr; }
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

inline uint64_t splitmix64(uint64_t x) noexcept {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}
static uint64_t sm_state = (uint64_t) chrono::steady_clock::now().time_since_epoch().count() ^
                           (uint64_t) (uintptr_t) &sm_state;
inline uint64_t rnd() noexcept {
    sm_state += 0x9e3779b97f4a7c15ULL;
    return splitmix64(sm_state);
}

struct chash {
    static uint64_t seed() noexcept {
        static const uint64_t s = rnd();
        return s;
    }
    template<class T> enable_if_t<(is_integral_v<T> || is_enum_v<T>) && sizeof(T) <= sizeof(uint64_t), size_t> operator()(T x) const noexcept {
        return (size_t) splitmix64((uint64_t) x + seed());
    }
    size_t operator()(string_view s) const noexcept {
        uint64_t sd = seed();
        const char* p = s.data();
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
    template<class A, class B> size_t operator()(const pair<A, B>& p) const noexcept {
        uint64_t a = (uint64_t) (*this)(p.first);
        uint64_t b = (uint64_t) (*this)(p.second);
        return (size_t) splitmix64(a ^ (b + 0x9e3779b97f4a7c15ULL + (a << 6) + (a >> 2)));
    }
};

template<class K, class V> using hash_map = __gnu_pbds::gp_hash_table<K, V, chash>;
template<class K> using hash_set = __gnu_pbds::gp_hash_table<K, __gnu_pbds::null_type, chash>;
template<class T> using ord_set = __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                                                __gnu_pbds::tree_order_statistics_node_update>;
// order_of_key(x) - сколько меньше x, find_by_order(x) - итератор на элемент на позиции x (нумерация с нуля)

template<class Int, class Coef> inline Int extgcd_core(Int a, Int b, Coef& x, Coef& y) {
    if (b == 0) {
        x = a < 0 ? -1 : 1;
        y = 0;
        return a < 0 ? -a : a;
    }
    Coef next_x;
    Int g = extgcd_core(b, a % b, next_x, x);
    y = next_x - (Coef) (a / b) * x;
    return g;
}

// Возвращает НОД и коэффициенты x, y такие, что a*x + b*y = НОД(a, b).
// НОД должен помещаться в ll.
inline ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (a != LLONG_MIN && b != LLONG_MIN) return extgcd_core(a, b, x, y);
    i128 wide_x, wide_y;
    i128 g = extgcd_core((i128) a, (i128) b, wide_x, wide_y);
    assert(g <= LLONG_MAX);
    x = (ll) wide_x;
    y = (ll) wide_y;
    return (ll) g;
}

// Возвращает обратный элемент или nullopt для неположительного модуля или НОД != 1.
template<class T> inline optional<common_type_t<ll, T>> invmod(i128 value, T mod) {
    static_assert(is_integral_v<T> && sizeof(T) <= sizeof(ull));
    const i128 modulus = mod;
    if (modulus <= 0) return nullopt;
    if (value < -modulus || value >= modulus) {
        const bool fits_ll = modulus <= LLONG_MAX && LLONG_MIN <= value && value <= LLONG_MAX;
        value = fits_ll ? (ll) value % (ll) modulus : value % modulus;
    }
    if (value < 0) value += modulus;
    using Coef = conditional_t<(sizeof(T) < sizeof(ll) || is_signed_v<T>), ll, i128>;
    Coef x, y;
    if (extgcd_core((ull) mod, (ull) value, y, x) != 1) return nullopt;
    return (common_type_t<ll, T>) (x < 0 ? x + (Coef) mod : x);
}

template<typename T, T MOD> struct ModInt {
    static_assert(is_integral_v<T> && sizeof(T) <= sizeof(ull), "ModInt requires an integer type up to 64 bits");
    static_assert(MOD > 0, "ModInt requires a positive modulus");
    T v = 0; // Нормализованный остаток из [0, MOD).
    ModInt() noexcept = default;
    template<class U> ModInt(U x) noexcept { set(x); }
    template<class U> void set(U x) noexcept {
        using Word = conditional_t<(U(-1) < U(0)), ll, ull>;
        using Wide = conditional_t<is_signed_v<Word>, i128, __uint128_t>;
        constexpr bool fits_word = (is_integral_v<U> || is_enum_v<U>)
            && sizeof(U) <= sizeof(Word) && MOD <= numeric_limits<Word>::max();
        using Work = conditional_t<fits_word, Word, Wide>;
        Work residue = (Work) x % (Work) MOD;
        v = (T) (residue < 0 ? residue + (Work) MOD : residue);
    }
    explicit operator T() const noexcept { return v; }
    friend ostream& operator<<(ostream& os, const ModInt& a) { return os << +a.v; }
    friend istream& operator>>(istream& is, ModInt& a) {
        using Input = conditional_t<(is_unsigned_v<T> && sizeof(T) == sizeof(ull)), i128, ll>;
        Input x = 0;
        if (is >> x) a.set(x);
        return is;
    }
    ModInt& operator+=(const ModInt& o) noexcept {
        const T gap = MOD - o.v;
        v = v >= gap ? v - gap : v + o.v;
        return *this;
    }
    ModInt& operator-=(const ModInt& o) noexcept {
        v = v >= o.v ? v - o.v : MOD - (o.v - v);
        return *this;
    }
    ModInt& operator*=(const ModInt& o) noexcept {
        using Product = conditional_t<(MOD <= (1LL << 32)), ull, __uint128_t>;
        v = (T) ((Product) v * (Product) o.v % (Product) MOD);
        return *this;
    }
    template<class K> static ModInt pow(ModInt a, K e) noexcept { return binpow(a, e); }
    static optional<ModInt> try_inv(ModInt a) noexcept {
        optional<ModInt> result;
        if (auto value = invmod(a.v, MOD)) result.emplace().v = (T) *value;
        return result;
    }
    // Для inv и деления делитель должен быть обратим по модулю MOD.
    static ModInt inv(ModInt a) noexcept {
        auto result = try_inv(a);
        if (!result) abort();
        return *result;
    }
    ModInt& operator/=(const ModInt& o) noexcept { return *this *= inv(o); }
    friend ModInt operator+(ModInt a, const ModInt& b) noexcept { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b) noexcept { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b) noexcept { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b) noexcept { return a /= b; }
    friend bool operator==(const ModInt& a, const ModInt& b) noexcept { return a.v == b.v; }
    friend bool operator!=(const ModInt& a, const ModInt& b) noexcept { return !(a == b); }
};

using mint = ModInt<int, MOD>;

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

// НОД. Абсолютные значения обоих аргументов должны помещаться в ll.
ll gcdll(ll a, ll b) { return std::gcd(a, b); }

// НОК. Для ненулевых аргументов их модули и результат должны помещаться в ll.
ll lcmll(ll a, ll b) {
    if (a == 0 || b == 0) return 0;
    return std::lcm(a, b);
}

// Решето Эратосфена для 0..n за O(n log log n).
vector<bool> sieve(int n) {
    if (n < 0) return {};
    vector<bool> is_prime((size_t) n + 1, true);
    is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;

    for (int p = 2; 1LL * p * p <= n; ++p) {
        if (!is_prime[p]) continue;
        for (ll multiple = 1LL * p * p; multiple <= n; multiple += p) {
            is_prime[multiple] = false;
        }
    }
    return is_prime;
}

struct SPF {
    vector<int> spf;
    vector<int> primes;

    // Строит таблицу минимальных простых делителей для 0..n.
    explicit SPF(int n)
        : spf(n < 0 ? 0 : (size_t) n + 1) {
        for (ll value = 2; value <= n; ++value) {
            if (spf[value] != 0) continue;
            spf[value] = (int) value;
            primes.push_back((int) value);
            for (ll multiple = value * value; multiple <= n; multiple += value) {
                if (spf[multiple] == 0) spf[multiple] = (int) value;
            }
        }
    }

    // Проверяет простоту. Вне [2,n] возвращает false.
    bool is_prime(int value) const { return value >= 2 && (size_t) value < spf.size() && spf[value] == value; }

    // Разлагает value из [1,n] за O(log value).
    vector<pair<int, int>> factor(int value) const {
        assert(value >= 1 && (size_t) value < spf.size());
        vector<pair<int, int>> factors;
        while (value > 1) {
            int prime = spf[value], exponent = 0;
            do {
                value /= prime;
                ++exponent;
            } while (value % prime == 0);
            factors.emplace_back(prime, exponent);
        }
        return factors;
    }
};

// Разлагает |value| перебором делителей за O(sqrt(|value|)).
// Для |value| < 2 возвращает пустой список.
vector<pair<ll, int>> factor(ll value) {
    vector<pair<ll, int>> factors;
    ull remaining = (ull) value;
    if (value < 0) remaining = -remaining;

    for (ull prime = 2; prime <= remaining / prime; prime += (prime == 2 ? 1 : 2)) {
        if (remaining % prime != 0) continue;
        int exponent = 0;
        while (remaining % prime == 0) {
            remaining /= prime;
            ++exponent;
        }
        factors.emplace_back((ll) prime, exponent);
    }
    if (remaining > 1) factors.emplace_back((ll) remaining, 1);
    return factors;
}

// Функция Эйлера для n >= 0, phi(0) = 0. Копировать вместе с factor.
ll phi(ll n) {
    assert(n >= 0);
    ll result = n;
    for (const auto& entry: factor(n)) {
        result -= result / entry.first;
    }
    return result;
}

// Значения функции Эйлера для 0..n за O(n log log n).
vector<int> phi_sieve(int n) {
    if (n < 0) return {};
    vector<int> phi((size_t) n + 1);
    iota(phi.begin(), phi.end(), 0LL);
    for (ll prime = 2; prime <= n; ++prime) {
        if (phi[prime] != prime) continue;
        for (ll multiple = prime; multiple <= n; multiple += prime) {
            phi[multiple] -= (int) (phi[multiple] / prime);
        }
    }
    return phi;
}

// Положительные делители n по возрастанию за O(sqrt(n)). Для n <= 0 список пуст.
vector<ll> divisors(ll n) {
    vector<ll> small, large;
    for (ll d = 1; d <= n / d; ++d) {
        if (n % d != 0) continue;
        small.push_back(d);
        if (d != n / d) large.push_back(n / d);
    }
    small.insert(small.end(), large.rbegin(), large.rend());
    return small;
}

template<ll MOD> struct Comb {
    static_assert(MOD > 1);

private:
    static ll mul(ll a, ll b) {
        if constexpr (MOD <= INT_MAX) return a * b % MOD;
        else return (ll) ((i128) a * b % MOD);
    }

    struct Residue {
        ll value;

        Residue(ll x) : value(x) {}
        Residue operator*(Residue other) const { return mul(value, other.value); }
    };

public:
    vector<ll> fact;
    vector<ll> ifact;

    // Использует binpow, общий для template1 и template2. Требуется простой MOD и 0 <= n < MOD.
    explicit Comb(int n) {
        assert(0 <= n && n < MOD);
        fact.resize((size_t) n + 1);
        ifact.resize(fact.size());
        fact[0] = 1;
        for (ll i = 1; i <= n; ++i) {
            fact[i] = mul(fact[i - 1], i);
        }

        ifact[n] = binpow(Residue(fact[n]), MOD - 2).value;
        for (int i = n; i > 0; --i) {
            ifact[i - 1] = mul(ifact[i], i);
        }
    }

    // Возвращает биномиальный коэффициент C(n, k) по модулю MOD.
    ll binomial(int n, int k) const {
        if (k < 0 || k > n) return 0;
        assert((size_t) n < fact.size());
        return mul(mul(fact[n], ifact[k]), ifact[n - k]);
    }
};

void solve() {}
