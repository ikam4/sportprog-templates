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

struct PolyHash {
    static constexpr ll MOD1 = 1'000'000'007;
    static constexpr ll MOD2 = 1'000'000'009;
    static constexpr ll BASE = 911'382'323;

    vector<ll> pow1{1};
    vector<ll> pow2{1};
    vector<ll> pref1{0};
    vector<ll> pref2{0};

    // Строит префиксные хеши строки и степени основания.
    explicit PolyHash(string_view s) {
        pow1.resize(s.size() + 1);
        pow2.resize(s.size() + 1);
        pref1.resize(s.size() + 1);
        pref2.resize(s.size() + 1);

        for (int i = 0; i < static_cast<int>(s.size()); ++i) {
            const ll value = static_cast<unsigned char>(s[i]) + 1;
            pow1[i + 1] = pow1[i] * BASE % MOD1;
            pow2[i + 1] = pow2[i] * BASE % MOD2;
            pref1[i + 1] = (pref1[i] * BASE + value) % MOD1;
            pref2[i + 1] = (pref2[i] * BASE + value) % MOD2;
        }
    }

    // Возвращает двойной хеш подстроки s[l..r) за O(1).
    pair<ll, ll> get(int l, int r) const {
        ll hash1 = (pref1[r] - pref1[l] * pow1[r - l]) % MOD1;
        ll hash2 = (pref2[r] - pref2[l] * pow2[r - l]) % MOD2;
        if (hash1 < 0) hash1 += MOD1;
        if (hash2 < 0) hash2 += MOD2;
        return {hash1, hash2};
    }

    // Проверяет равенство двух подстрок одной строки.
    bool equal(int left1, int right1, int left2, int right2) const {
        return right1 - left1 == right2 - left2 && get(left1, right1) == get(left2, right2);
    }
};

void solve() {}
