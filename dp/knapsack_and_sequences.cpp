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
    int T = 1;
    while (T--) solve();
    return 0;
}

// Решает 0/1-рюкзак: каждый предмет можно взять не более одного раза.
ll knap01(const vector<int>& w, const vector<ll>& v, int cap) {
    vector<ll> dp(cap + 1);
    for (int i = 0; i < sz(w); ++i) {
        for (int c = cap; c >= w[i]; --c) {
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
        }
    }
    return dp[cap];
}

// Решает рюкзак с неограниченным количеством копий каждого предмета.
// Если есть предмет нулевого веса с положительной ценой, возвращает LLONG_MAX.
ll knap_inf(const vector<int>& w, const vector<ll>& v, int cap) {
    for (int i = 0; i < sz(w); ++i) {
        if (w[i] == 0 && v[i] > 0) return LLONG_MAX;
    }

    vector<ll> dp(cap + 1);
    for (int i = 0; i < sz(w); ++i) {
        if (w[i] == 0) continue;
        for (int c = w[i]; c <= cap; ++c) {
            dp[c] = max(dp[c], dp[c - w[i]] + v[i]);
        }
    }
    return dp[cap];
}

// Решает рюкзак с ограниченным количеством копий каждого предмета.
// Использует двоичное разбиение количества, сложность O(W * sum(log(count))).
ll knap_lim(const vector<int>& w, const vector<ll>& v, const vector<int>& cnt, int cap) {
    vector<ll> dp(cap + 1);

    for (int i = 0; i < sz(w); ++i) {
        int remaining = cnt[i];
        for (int chunk = 1; remaining > 0; chunk <<= 1) {
            const int take = min(chunk, remaining);
            const ll weight = 1LL * w[i] * take;
            const ll value = v[i] * take;
            for (int c = cap; c >= weight; --c) {
                dp[c] = max(dp[c], dp[c - weight] + value);
            }
            remaining -= take;
        }
    }
    return dp[cap];
}

// Решает ограниченный рюкзак за O(nW) с помощью монотонных очередей.
ll knap_lim_fast(const vector<int>& w, const vector<ll>& v, const vector<int>& cnt, int cap) {
    vector<ll> dp(cap + 1);
    ll zero_weight_value = 0;

    for (int i = 0; i < sz(w); ++i) {
        if (w[i] == 0) {
            zero_weight_value += max(0LL, v[i]) * cnt[i];
            continue;
        }
        if (w[i] < 0 || w[i] > cap) continue;

        vector<ll> next = dp;
        for (int rem = 0; rem < w[i] && rem <= cap; ++rem) {
            deque<pair<int, ll>> q;
            for (int k = 0, pos = rem; pos <= cap; ++k, pos += w[i]) {
                const ll cur = dp[pos] - 1LL * k * v[i];
                while (!q.empty() && q.back().second <= cur) {
                    q.pop_back();
                }
                q.emplace_back(k, cur);
                while (!q.empty() && q.front().first < k - cnt[i]) {
                    q.pop_front();
                }
                next[pos] = q.front().second + 1LL * k * v[i];
            }
        }
        dp = std::move(next);
    }
    return dp[cap] + zero_weight_value;
}

// Возвращает индексы предметов, выбранных в оптимальном 0/1-рюкзаке.
vector<int> knap01_items(const vector<int>& w, const vector<ll>& v, int cap) {
    const int n = sz(w);
    vector dp(n + 1, vector<ll>(cap + 1));

    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c <= cap; ++c) {
            dp[i][c] = dp[i - 1][c];
            if (w[i - 1] <= c) {
                dp[i][c] = max(dp[i][c], dp[i - 1][c - w[i - 1]] + v[i - 1]);
            }
        }
    }

    vector<int> ans;
    for (int i = n, c = cap; i > 0; --i) {
        if (dp[i][c] == dp[i - 1][c]) {
            continue;
        }
        ans.push_back(i - 1);
        c -= w[i - 1];
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// Возвращает одну из наибольших строго возрастающих подпоследовательностей.
template<class T>
vector<T> lis(const vector<T>& a) {
    if (a.empty()) {
        return {};
    }

    vector<T> tails;
    vector<int> ids;
    vector<int> prv(sz(a), -1);

    for (int i = 0; i < sz(a); ++i) {
        const int pos = static_cast<int>(lower_bound(tails.begin(), tails.end(), a[i]) - tails.begin());
        if (pos > 0) {
            prv[i] = ids[pos - 1];
        }

        if (pos == sz(tails)) {
            tails.push_back(a[i]);
            ids.push_back(i);
        } else {
            tails[pos] = a[i];
            ids[pos] = i;
        }
    }

    vector<T> ans;
    for (int i = ids.back(); i != -1; i = prv[i]) {
        ans.push_back(a[i]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

// Возвращает одну из наибольших общих подпоследовательностей двух векторов.
template<class T>
vector<T> lcs(const vector<T>& a, const vector<T>& b) {
    vector dp(a.size() + 1, vector<int>(b.size() + 1));

    for (int i = 1; i <= sz(a); ++i) {
        for (int j = 1; j <= sz(b); ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    vector<T> ans;
    int i = sz(a), j = sz(b);
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            ans.push_back(a[i - 1]);
            --i;
            --j;
        } else if (dp[i - 1][j] >= dp[i][j - 1]) {
            --i;
        } else {
            --j;
        }
    }

    reverse(ans.begin(), ans.end());
    return ans;
}

// Возвращает одну из наибольших общих подпоследовательностей двух строк.
string lcs(const string& a, const string& b) {
    vector<char> va(a.begin(), a.end());
    vector<char> vb(b.begin(), b.end());
    const vector<char> common = lcs(va, vb);
    return {common.begin(), common.end()};
}

// Возвращает одну из наибольших общих возрастающих подпоследовательностей.
template<class T>
vector<T> lcis(const vector<T>& a, const vector<T>& b) {
    if (b.empty()) {
        return {};
    }

    vector<int> len(sz(b)), prv(sz(b), -1);
    // Предки неизменяемы: последующие обновления не должны менять старые цепочки.
    // Время O(nm), память для восстановления — до O(nm).
    vector<pair<T, int>> hist;

    for (const T& value: a) {
        int best = 0;
        int last = -1;
        for (int j = 0; j < sz(b); ++j) {
            if (value == b[j] && best + 1 > len[j]) {
                len[j] = best + 1;
                prv[j] = sz(hist);
                hist.emplace_back(value, last);
            } else if (value > b[j] && len[j] > best) {
                best = len[j];
                last = prv[j];
            }
        }
    }

    int end = static_cast<int>(max_element(len.begin(), len.end()) - len.begin());
    if (len[end] == 0) {
        return {};
    }

    vector<T> ans;
    for (int cur = prv[end]; cur != -1; cur = hist[cur].second) {
        ans.push_back(hist[cur].first);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

void solve() {}
