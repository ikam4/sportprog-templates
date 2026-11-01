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
}
inline int lsb(ll x) {
    return x ? __builtin_ctzll((ull) x) : -1;
}

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
    int T = 1;
    while (T--) solve();
    return 0;
}

// Возвращает наибольший общий делитель двух чисел.
ll gcdll(ll a, ll b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Возвращает наименьшее общее кратное двух чисел.
ll lcmll(ll a, ll b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return abs(a / gcdll(a, b) * b);
}

// Возвращает НОД и находит x, y такие, что a*x + b*y = НОД(a, b).
ll extgcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = (a >= 0 ? 1 : -1);
        y = 0;
        return abs(a);
    }

    ll next_x, next_y;
    ll g = extgcd(b, a % b, next_x, next_y);
    x = next_y;
    y = next_x - (a / b) * next_y;
    return g;
}

// Приводит число к диапазону [0, mod).
ll norm_mod(ll value, ll mod) {
    value %= mod;
    if (value < 0) {
        value += mod;
    }
    return value;
}

// Вычисляет base^exponent по модулю mod бинарным возведением в степень.
ll powmod(ll base, ll exponent, ll mod) {
    base = norm_mod(base, mod);
    ll result = 1 % mod;
    while (exponent > 0) {
        if (exponent & 1) {
            result = (ll) ((i128) result * base % mod);
        }
        base = (ll) ((i128) base * base % mod);
        exponent >>= 1;
    }
    return result;
}

// Возвращает обратный элемент по модулю или nullopt, если он не существует.
optional<ll> invmod(ll value, ll mod) {
    ll x, y;
    ll g = extgcd(value, mod, x, y);
    if (g != 1) {
        return nullopt;
    }
    return norm_mod(x, mod);
}

// Возвращает таблицу простоты всех чисел от 0 до n.
vector<bool> sieve(int n) {
    vector<bool> is_prime(n + 1, true);
    if (n >= 0) is_prime[0] = false;
    if (n >= 1) is_prime[1] = false;

    for (int p = 2; 1LL * p * p <= n; ++p) {
        if (!is_prime[p]) {
            continue;
        }
        for (int multiple = p * p; multiple <= n; multiple += p) {
            is_prime[multiple] = false;
        }
    }
    return is_prime;
}

struct SPF {
    vector<int> spf;
    vector<int> primes;

    // Строит таблицу минимальных простых делителей до n.
    explicit SPF(int n)
        : spf(n + 1) {
        for (int value = 2; value <= n; ++value) {
            if (spf[value] == 0) {
                spf[value] = value;
                primes.push_back(value);
                if (1LL * value * value <= n) {
                    for (int multiple = value * value; multiple <= n; multiple += value) {
                        if (spf[multiple] == 0) {
                            spf[multiple] = value;
                        }
                    }
                }
            }
        }
    }

    // Проверяет, является ли value простым числом.
    bool is_prime(int value) const { return value >= 2 && spf[value] == value; }
};

// Возвращает разложение числа на простые множители и их степени.
vector<pair<ll, int>> factor(ll value) {
    vector<pair<ll, int>> factors;
    if (value < 0) {
        value = -value;
    }

    for (ll prime = 2; prime <= value / prime; ++prime) {
        if (value % prime != 0) {
            continue;
        }
        int exponent = 0;
        while (value % prime == 0) {
            value /= prime;
            ++exponent;
        }
        factors.emplace_back(prime, exponent);
    }
    if (value > 1) {
        factors.emplace_back(value, 1);
    }
    return factors;
}

// Возвращает функцию Эйлера phi(n): количество чисел от 1 до n,
// взаимно простых с n.
ll phi(ll n) {
    ll result = n;
    for (const auto& [prime, exponent]: factor(n)) {
        (void) exponent;
        result -= result / prime;
    }
    return result;
}

// Возвращает значения функции Эйлера для всех чисел от 0 до n.
vector<int> phi_sieve(int n) {
    vector<int> phi(n + 1);
    iota(phi.begin(), phi.end(), 0);
    if (n >= 0) phi[0] = 0;
    for (int prime = 2; prime <= n; ++prime) {
        if (phi[prime] != prime) {
            continue;
        }
        for (int multiple = prime; multiple <= n; multiple += prime) {
            phi[multiple] -= phi[multiple] / prime;
        }
    }
    return phi;
}

template<ll MOD>
struct Comb {
    vector<ll> fact;
    vector<ll> ifact;

    // Предвычисляет факториалы и обратные факториалы по модулю MOD.
    explicit Comb(int n)
        : fact(n + 1)
        , ifact(n + 1) {
        fact[0] = 1;
        for (int i = 1; i <= n; ++i) {
            fact[i] = (ll) ((i128) fact[i - 1] * i % MOD);
        }

        ifact[n] = powmod(fact[n], MOD - 2, MOD);
        for (int i = n; i > 0; --i) {
            ifact[i - 1] = (ll) ((i128) ifact[i] * i % MOD);
        }
    }

    // Возвращает биномиальный коэффициент C(n, k) по модулю MOD.
    ll binomial(int n, int k) const {
        if (k < 0 || k > n) {
            return 0;
        }
        return (ll) ((i128) fact[n] * ifact[k] % MOD * ifact[n - k] % MOD);
    }
};

void solve() {}
