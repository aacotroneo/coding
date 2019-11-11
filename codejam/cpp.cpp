// g++ cpp.cpp -std=c++11 -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define printV(v) cout << "vec[ "; for(auto vi: (v)) {cout << vi << " ";} cout << "]" << endl;

typedef unsigned long long int LL;
// clang-format on
#define MOD 1000000007

int main() {
    IO;
    int testCase = 1;
    // freopen("input.txt", "r", stdin);
    SOLVE {
        int n, p;
        cin >> n >> p;
        vector<int> v(n), sum(n + 1);
        rep(i, 0, n) cin >> v[i];
        sort(v.begin(), v.end(), [](int a, int b) { return a > b; });

        sum[0] = 0;
        rep(i, 0, n) sum[i + 1] = sum[i] + v[i];
        // printV(v); printV(sum);
        int min_ = 1e9;
        rep(i, p, n + 1) {
            // for (int j = p - 1; j < n; ++j) {
            int s = sum[i] - sum[i - p];
            int cost = v[i - p] * p - s;
            min_ = min(min_, cost);
        }
        cout << "Case #" << testCase++ << ": " << min_ << endl;
    }
}