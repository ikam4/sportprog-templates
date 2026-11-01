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

struct BellmanResult {
    vll dp;
    vi parent;
    bool cycle;

    // Восстанавливаем путь только при отсутствии достижимого отрицательного цикла.
    vi get_path(int target) const {
        if (cycle || dp[target] == LINF) return {};
        vi path;
        for (int v = target; v != -1; v = parent[v]) path.pb(v);
        reverse(all(path));
        return path;
    }
};

BellmanResult bellman_ford(int s, int n, span<array<int, 3>> edges) {
    vll dp(n, LINF);
    vi parent(n, -1);
    dp[s] = 0;
    for (int i = 0; i < n - 1; ++i) {
        for (auto [u, v, w]: edges) {
            if (dp[u] < LINF && dp[v] > dp[u] + w) {
                dp[v] = dp[u] + w;
                parent[v] = u;
            }
        }
    }
    bool cycle = false;
    for (auto [u, v, w]: edges) {
        if (dp[u] < LINF && dp[v] > dp[u] + w) {
            cycle = true;
            break;
        }
    }
    return {std::move(dp), std::move(parent), cycle};
}

// Исходный интерфейс с целевой вершиной и печатью сохранён как пример и перегрузка для совместимости.
void bellman_ford(int s, int target, int n, span<array<int, 3>> edges) {
    auto result = bellman_ford(s, n, edges);
    if (result.cycle) {
        cout << "Negative cycle found" << nn;
    } else if (result.dp[target] == LINF) {
        cout << "No path" << nn;
    } else {
        cout << "Path: " << result.get_path(target);
    }
}

struct FloydResult {
    vector<vll> dp;
    vector<vi> nxt;
    bool cycle;

    // Прежняя локальная функция восстановления теперь доступна вызывающему коду.
    // При наличии любого отрицательного цикла эта функция возвращает пустой путь.
    vi get_path(int u, int v) const {
        if (cycle || dp[u][v] == LINF) return {};
        vi path;
        for (int curr = u; curr != v; curr = nxt[curr][v]) {
            if (curr == -1) return {};
            path.pb(curr);
        }
        path.pb(v);
        return path;
    }
};

FloydResult floyd_yorshell(int n, span<vi> matrix) {
    vector dp(n, vll(n, LINF));
    vector nxt(n, vi(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] != INF) {
                dp[i][j] = matrix[i][j];
                nxt[i][j] = j;
            }
        }
        dp[i][i] = min(dp[i][i], 0LL);
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[i][k] < LINF && dp[k][j] < LINF && dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = max(-LINF, dp[i][k] + dp[k][j]);
                    nxt[i][j] = nxt[i][k];
                }
            }
        }
    }
    bool cycle = false;
    for (int i = 0; i < n; ++i) {
        if (dp[i][i] < 0) {
            cycle = true;
            break;
        }
    }
    return {std::move(dp), std::move(nxt), cycle};
}

// Алгоритм возвращает данные; исходная диагностическая печать вынесена отдельно.
void floyd_example(int n, span<vi> matrix) {
    auto result = floyd_yorshell(n, matrix);
    if (result.cycle) cout << "Negative cycle found" << nn;
    // Иначе используйте result.dp и result.get_path(u, v).
}

void solve() {}
