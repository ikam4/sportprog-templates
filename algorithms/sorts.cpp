#include <bits/stdc++.h>
#define nn '\n'
typedef long long ll;
using namespace std;

void bubble_sort(vector<int>& a) { // стабильна
    int n = (int) a.size();
    bool swapped;
    for (int i = 0; i < n - 1; ++i) {
        swapped = false;
        for (int j = 0; j < n - i - 1;
             ++j) { // мы пузырючим макс. элик в конец, поэтому у нас последние i эликов посорчены goddamn
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]), swapped = true;
        }
        if (!swapped) break;
    }
}

void selection_sort(vector<int>& a) { // нестабильна, т.к. по сути мы делаем global свапы здесь
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
