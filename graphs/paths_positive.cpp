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

namespace shortest_path {
    template<typename T>
    T dijkstra(int s, int v, span<vector<pair<int, T>>> graph) {
        priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;
        vector<T> d(graph.size(), numeric_limits<T>::max() / 2);
        d[s] = 0;
        q.emplace(0, s);
        while (!q.empty()) {
            auto [dist, cur] = q.top();
            q.pop();
            if (dist > d[cur]) continue;
            for (auto [u, w]: graph[cur]) {
                if (d[u] > d[cur] + w) {
                    d[u] = d[cur] + w;
                    q.emplace(d[u], u);
                }
            }
        }
        return (d[v] == numeric_limits<T>::max() / 2 ? -1 : d[v]);
    }

    int bfs01(int s, int v, span<vector<pii>> graph) {
        deque<int> q;
        vector<bool> used(graph.size(), false);
        vi d(graph.size(), INF / 2);
        d[s] = 0;
        q.emplace_back(s);
        while (!q.empty()) {
            int cur = q.front();
            q.pop_front();
            if (used[cur]) continue;
            used[cur] = true;
            for (auto [u, w]: graph[cur]) {
                if (d[u] > d[cur] + w) {
                    d[u] = d[cur] + w;
                    if (w == 0) {
                        q.emplace_front(u);
                    } else {
                        q.emplace_back(u);
                    }
                }
            }
        }
        return (d[v] == INF / 2 ? -1 : d[v]);
    }

    int bfs0k(int s, int v, int k, span<vector<pii>> graph) {
        vector<queue<int>> q(k + 1);
        vi d(graph.size(), INF / 2);
        int pos = 0, cnt = 1;
        d[s] = 0;
        q[0].push(s);
        while (cnt > 0) {
            while (q[pos % (k + 1)].empty()) {
                ++pos;
            }
            int cur = q[pos % (k + 1)].front();
            q[pos % (k + 1)].pop();
            --cnt;
            if (pos > d[cur]) continue;
            for (auto [u, w]: graph[cur]) {
                if (d[u] > d[cur] + w) {
                    d[u] = d[cur] + w;
                    q[d[u] % (k + 1)].push(u);
                    ++cnt;
                }
            }
        }
        return (d[v] == INF / 2 ? -1 : d[v]);
    }
};

void solve() {}
