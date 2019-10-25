// g++ cpp.cpp -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define repFrom(i, f, n) for (int i = (f); i < (n); i++)
typedef long long int LL;
// clang-format on

#define MAX_N 100000

struct segTree {
    int sgt[400400];

    segTree(int q) {
        rep(i, 4 * q) sgt[i] = 1 << 30;
    }

    void update(int nd, int l, int r, int s, int e, int val) {
        if (s <= l && r <= e) {
            sgt[nd] = min(sgt[nd], val);
            return;
        }
        int mid = (r + l) / 2;
        if (s <= mid) {
            update(2 * nd, l, mid, s, e, min(val, sgt[nd]));
        }
        if (mid + 1 <= e) {
            update(2 * nd + 1, mid + 1, r, s, e, min(val, sgt[nd]));
        }
    }

    int query(int nd, int l, int r, int ind) {
        if (l == r) return sgt[nd];
        int mid = (r + l) / 2;
        if (ind <= mid) {
            return min(sgt[nd], query(2 * nd, l, mid, ind));
        } else {
            return min(sgt[nd], query(2 * nd + 1, mid + 1, r, ind));
        }
    }
};

int n, q, k, l, r;
LL C[MAX_N], P[MAX_N];

int getTimeIn(int curr) {
    if (curr >= l) {
        // we are on the right
        if (curr <= r) return 0;
        if (k > r) return -1;  // we'll never reach the right
        return curr - r;
    }
    if (k < l) return -1;  // we'll never reach the left
    return l - curr;
}

int getTimeOut(int p) {
    if (k >= l && k <= r) return MAX_N;
    return k > r ? r - p : p - l;
}

int main() {
    IO;
    SOLVE {
        cin >> n >> q >> k >> l >> r;
        rep(i, n) cin >> C[i] >> P[i];

        segTree tree(q);

        rep(i, n) {
            int in = getTimeIn(C[i]);
            if (in >= 0 && in <= q) {
                int out = getTimeOut(C[i]);
                if (out >= 1) tree.update(1, 1, q, max(in, 1), min(out, q), P[i]);
            }
        }

        repFrom(i, 1, q + 1) {
            int h = tree.query(1, 1, q, i);
            if (h == 1 << 30)
                cout << "-1 ";
            else
                cout << h << " ";
        }
        cout << endl;
    }
}