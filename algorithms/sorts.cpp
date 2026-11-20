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

void bubble_sort(vector<int>& a) { // стабильна
    int n = (int) a.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1;
             ++j) { // мы пузырючим макс. элик в конец, поэтому у нас последние i эликов посорчены
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]), swapped = true;
        }
        if (!swapped) break;
    }
}

void selection_sort(vector<int>& a) { // нестабильна, т.к. по сути мы делаем обмены между произвольными позициями здесь
    int n = (int) a.size();
    for (int i = 0; i < n - 1; ++i) {
        int min_id = i;
        for (int j = i + 1; j < n; ++j) { // мега очев просто для каждой позиции ищем мин элик
            if (a[j] < a[min_id]) min_id = j;
        }
        if (min_id != i) swap(a[i], a[min_id]);
    }
}

void insertion_sort(vector<int>& a) { // стабильна
    int n = (int) a.size();
    for (int i = 1; i < n; ++i) {
        int j = i - 1;
        int key = a[i];
        while (j >= 0 && a[j] > key)
            a[j + 1] = a[j], j--; // двигаем элики пока новый элик не на норм позе (короче фулл посорчено до i-1)
        a[j + 1] = key;
    }
}

int partition(vector<int>& a, int l, int r) {
    int& pivot = a[r]; // лучше рандомить
    for (int i = l; i < r; ++i) {
        if (a[i] < pivot) swap(a[l++], a[i]); // делаем так, чтобы на [0, l) были элики меньше пивота
    }
    swap(a[l], pivot);
    return l;
}

void quick_sort(vector<int>& a, int l, int r) { // нестабильна + O(n^2) в худшем случае
    if (l >= r) return;
    int p = partition(a, l, r);
    quick_sort(a, l, p - 1);
    quick_sort(a, p + 1, r);
}

void merge(vector<int>& a, int l, int m, int r) {
    vector<int> left(a.begin() + l, a.begin() + m + 1);
    vector<int> right(a.begin() + m + 1, a.begin() + r + 1);
    size_t i = 0, j = 0, k = (int) l;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j])
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }
    while (i < left.size()) a[k++] = left[i++];
    while (j < right.size()) a[k++] = right[j++];
}

void merge_sort(vector<int>& a, int l, int r) { // стабильная но память O(n) :(
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        // inplace_merge(a.begin()+l, a.begin()+m+1, a.begin()+r+1); - встроена
        merge(a, l, m, r); // свой
    }
}

void counting_sort(vector<int>& a) { // быстрейшая (O(n)) и стабильная
    int mx = *max_element(a.begin(), a.end());
    vector<int> count(mx + 1, 0);
    for (int x: a) count[x]++;
    int idx = 0;
    for (int i = 0; i <= mx; ++i) {
        while (count[i]--) a[idx++] = i;
    }
}

void counting_pivotushka(vector<int>& a, int d) { // для радикс нада стабильная сортуха
    int n = a.size();
    vector<int> ans(n);
    vector<int> cnt(10);

    for (int i = 0; i < n; i++) cnt[(a[i] / d) % 10]++;

    for (int i = 1; i < 10; i++)
        cnt[i] +=
            cnt[i - 1]; // превращаем массив частот в такое:  cnt[i] значит, сколько эликов в цифрой в разряде d <= i

    for (int i = n - 1; i >= 0; i--) { // мы кнтху уменьшаем, поэтому чтобы была стабильность, надо от обратного идти
        int digit = (a[i] / d) % 10;
        ans[cnt[digit] - 1] = a[i];
        cnt[digit]--;
    }

    a = move(ans);
}

void radix_sort(
    vector<int>& a) { // сложность O(d*(n+k)) и память O(n+k), d - кол-во разрядов, k - основание системы счисления
    int mx = *max_element(a.begin(), a.end());
    for (int d = 1; mx / d > 0; d *= 10) counting_pivotushka(a, d);
}

void solve() {
    vector<int> a = {23, 565, 77, 3457, 456, 347, 7};
    vector<int> b = a;
    // bubble_sort(a);
    // selection_sort(a);
    // insertion_sort(a);
    // quick_sort(a, 0, int(a.size()) - 1);
    // merge_sort(a, 0, int(a.size()) - 1);
    // counting_sort(a);
    radix_sort(a);
    sort(b.begin(), b.end());
    for (int i = 0; i < (int) a.size(); ++i) {
        assert(a[i] == b[i]);
    }
    cout << "passed";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
