// g++ cpp.cpp -std=c++11 -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

typedef pair<int, int> ii; typedef vector<ii> vii;
typedef long long int LL;
typedef long double LD;
// clang-format on
#define MOD 1000000007
#define MAX 5000
struct node {
    int x;
    int y;
    LD w;
    LD w2;
    // int succesor;
};
typedef vector<node> VN;

int n, m, k;
VN N(MAX), M(MAX), K(MAX);
node start;
// vector<pair<int, LD>> NK(MAX);
// vector<pair<int, LD>> MK(MAX);
// vector<pair<int, LD>> MN(MAX);
// vector<pair<int, LD>> NM(MAX);

void calcDist(int n, int k, VN& N, VN& K, bool two) {
    node *from, *to;
    LL xx, yy;

    rep(nn, 0, n) {
        from = &N[nn];
        pair<int, LD> _min = {-1, 1e100};
        rep(kk, 0, k) {
            to = &K[kk];
            xx = (from->x - to->x), yy = from->y - to->y;
            LD dist = sqrt(xx * xx + yy * yy);  // memoize some pow/sqr?
            if (dist + to->w < _min.second) _min.second = dist + to->w, _min.first = kk;
        }
        if (two)
            from->w2 = _min.second;
        else
            from->w = _min.second;
        // from->succesor = _min.first;
    }
}
int main() {
    IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    SOLVE {
        int x, y;
        cin >> x >> y >> n >> m >> k, start.x = x, start.y = y;
        rep(i, 0, n) cin >> x >> y, N[i] = {x, y, 0};
        rep(i, 0, m) cin >> x >> y, M[i] = {x, y, 0};
        rep(i, 0, k) cin >> x >> y, K[i] = {x, y, 0};

        calcDist(n, k, N, K, false);
        calcDist(m, k, M, K, false);
        calcDist(m, n, M, N, true);
        calcDist(n, m, N, M, true);

        node* to;
        LL xx, yy;
        pair<int, LD> _min = {-1, 1e100};
        rep(nn, 0, n) {
            to = &N[nn], xx = (start.x - to->x), yy = start.y - to->y;
            LD dist = sqrt(xx * xx + yy * yy);  // memoize some pow/sqr?
            if (dist + to->w2 < _min.second) _min.second = dist + to->w2, _min.first = nn;
        }
        rep(mm, 0, m) {
            to = &M[mm], xx = (start.x - to->x), yy = start.y - to->y;
            LD dist = sqrt(xx * xx + yy * yy);  // memoize some pow/sqr?
            if (dist + to->w2 < _min.second) _min.second = dist + to->w2, _min.first = mm;
        }

        cout << setprecision(10) << fixed << _min.second << endl;
    }
}