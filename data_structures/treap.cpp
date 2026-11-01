// Лучший шаблон
#pragma GCC optimize("O3,unroll-loops")
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
static uint64_t sm_state =
    (uint64_t) chrono::steady_clock::now().time_since_epoch().count() ^ (uint64_t) (uintptr_t) new int;
inline uint64_t rnd() noexcept {
    sm_state += 0x9e3779b97f4a7c15ULL;
    return splitmix64(sm_state);
}

int main() {
    return 0;
}

struct Treap {
    struct Node {
        int x = 0, y = 0, sz = 0;
        array<int, 2> children{};
        int& operator[](int idx) { return children[idx]; }
    };
    int root = 0;
    vector<Node> tr;

    Treap() { tr.eb(); }

    void recalc(int node) {
        if (!node) return;
        tr[node].sz = 1 + tr[tr[node][0]].sz + tr[tr[node][1]].sz;
    }

    int make_node(int x) {
        tr.eb(x, (int) rnd(), 1);
        return sz(tr) - 1;
    }

    pair<int, int> split(int T, int x) {
        if (!T) {
            return {0, 0};
        }
        if (tr[T].x >= x) {
            auto [TLL, TLR] = split(tr[T][0], x);
            tr[T][0] = TLR;
            recalc(T);
            return {TLL, T};
        } else {
            auto [TRL, TRR] = split(tr[T][1], x);
            tr[T][1] = TRL;
            recalc(T);
            return {T, TRR};
        }
    }

    int merge(int TL, int TR) {
        if (TL == 0) return TR;
        if (TR == 0) return TL;
        if (tr[TL].y >= tr[TR].y) {
            tr[TL][1] = merge(tr[TL][1], TR);
            recalc(TL);
            return TL;
        } else {
            tr[TR][0] = merge(TL, tr[TR][0]);
            recalc(TR);
            return TR;
        }
    }

    int insert(int T, int node) {
        if (!T) return node;
        if (tr[node].y >= tr[T].y) {
            auto [TL, TR] = split(T, tr[node].x);
            tr[node][0] = TL;
            tr[node][1] = TR;
            recalc(node);
            return node;
        }
        if (tr[T].x >= tr[node].x) {
            tr[T][0] = insert(tr[T][0], node);
        } else {
            tr[T][1] = insert(tr[T][1], node);
        }
        recalc(T);
        return T;
    }

    void insert(int x) {
        int node = make_node(x);
        root = insert(root, node);
    }

    int erase(int T, int x) {
        if (!T) return 0;
        if (tr[T].x == x) {
            return merge(tr[T][0], tr[T][1]);
        } else if (tr[T].x > x) {
            tr[T][0] = erase(tr[T][0], x);
        } else {
            tr[T][1] = erase(tr[T][1], x);
        }
        recalc(T);
        return T;
    }

    void erase(int x) { root = erase(root, x); }

    int get_kth(int k) {
        int T = root;
        while (T) {
            int left_sz = tr[tr[T][0]].sz;
            if (left_sz > k) {
                T = tr[T][0];
            } else if (left_sz == k) {
                return T;
            } else {
                k -= left_sz + 1;
                T = tr[T][1];
            }
        }
        return 0;
    }

    int count_less(int x) {
        int T = root;
        int count = 0;
        while (T) {
            if (tr[T].x >= x) {
                T = tr[T][0];
            } else {
                count += tr[tr[T][0]].sz + 1;
                T = tr[T][1];
            }
        }
        return count;
    }

    bool contains(int x) {
        int T = root;
        while (T) {
            if (tr[T].x == x) {
                return true;
            } else if (tr[T].x > x) {
                T = tr[T][0];
            } else {
                T = tr[T][1];
            }
        }
        return false;
    }
};

struct ImplTreap {
    struct Node {
        int y = 0, val = 0, sz = 0;
        array<int, 2> children{};
        int& operator[](int idx) { return children[idx]; }
    };
    int root = 0;
    vector<Node> tr;

    ImplTreap() { tr.eb(); }

    void recalc(int node) {
        if (!node) return;
        tr[node].sz = 1 + tr[tr[node][0]].sz + tr[tr[node][1]].sz;
    }

    int make_node(int x) {
        tr.eb((int) rnd(), x, 1);
        return sz(tr) - 1;
    }

    pair<int, int> split(int T, int x) {
        if (!T) {
            return {0, 0};
        }
        if (tr[tr[T][0]].sz >= x) {
            auto [TLL, TLR] = split(tr[T][0], x);
            tr[T][0] = TLR;
            recalc(T);
            return {TLL, T};
        } else {
            auto [TRL, TRR] = split(tr[T][1], x - tr[tr[T][0]].sz - 1);
            tr[T][1] = TRL;
            recalc(T);
            return {T, TRR};
        }
    }

    int merge(int TL, int TR) {
        if (TL == 0) return TR;
        if (TR == 0) return TL;
        if (tr[TL].y >= tr[TR].y) {
            tr[TL][1] = merge(tr[TL][1], TR);
            recalc(TL);
            return TL;
        } else {
            tr[TR][0] = merge(TL, tr[TR][0]);
            recalc(TR);
            return TR;
        }
    }

    int insert(int T, int x, int node) {
        if (!T) return node;
        if (tr[node].y >= tr[T].y) {
            auto [TL, TR] = split(T, x);
            tr[node][0] = TL;
            tr[node][1] = TR;
            recalc(node);
            return node;
        }
        if (x <= tr[tr[T][0]].sz) {
            tr[T][0] = insert(tr[T][0], x, node);
        } else {
            tr[T][1] = insert(tr[T][1], x - tr[tr[T][0]].sz - 1, node);
        }
        recalc(T);
        return T;
    }

    void insert(int x, int val) {
        int node = make_node(val);
        root = insert(root, x, node);
    }

    int erase(int T, int x) {
        if (!T) return 0;
        if (x == tr[tr[T][0]].sz) {
            return merge(tr[T][0], tr[T][1]);
        } else if (x < tr[tr[T][0]].sz) {
            tr[T][0] = erase(tr[T][0], x);
        } else {
            tr[T][1] = erase(tr[T][1], x - tr[tr[T][0]].sz - 1);
        }
        recalc(T);
        return T;
    }

    void erase(int x) { root = erase(root, x); }

    int get_kth(int k) {
        int cur = root;
        while (cur) {
            int left_sz = tr[tr[cur][0]].sz;
            if (k == left_sz) return tr[cur].val;
            if (k < left_sz) {
                cur = tr[cur][0];
            } else {
                k -= left_sz + 1;
                cur = tr[cur][1];
            }
        }
        return -1;
    }

    void print(int v) {
        if (!v) return;
        print(tr[v][0]);
        cout << tr[v].val << ' ';
        print(tr[v][1]);
    }

    void print() {
        print(root);
        cout << nn;
    }
};
