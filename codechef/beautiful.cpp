// g++ cpp.cpp -std=c++11 -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

typedef pair<int, int> ii; typedef vector<ii> vii;
typedef unsigned long long int LL;
// clang-format on
#define MOD 1000000007

int n;
vector<int> pows(9001);  // 9k^2 = 81M = 99999...999
map<int, int> roots = {{1, 1}, {4, 2}, {9, 3}, {16, 4}, {25, 5}, {36, 6}, {49, 7}, {64, 8}, {81, 9}};

vector<int> result(10);  // 1 indexed
map<string, bool> dd;
/**
7 + 3 + = 11
15 = 81 ==> 1111137
+8 = 16 
 * */
int Min[9001];                                 //
int coins[] = {80, 63, 48, 35, 24, 15, 8, 3};  // square - 1

int minCoins(int number, int d) {
    // cout << "dp: " << number << " : " << d << endl;
    if ()
        if (d == 0) return number == 0;
    if (d == 1) {
        int v = roots[number];
        if (v && d > 1) {
            result[v]++;
            return 1;
        } else
            return 0;
    }
    // if (number == d) return 1;
    if (number > d * 81) return 0;
    string key = to_string(number) + ':' + to_string(d);
    if (dd[key] == true) return 0;

    rep(i, 2, 10) {
        int num = number - pows[i];
        if (num <= 0 || num < d - 1) return 0;
        result[i]++;
        // cout << "dp: " << i << " : " << d << endl;
        if (dp(num, d - 1)) return 1;
        result[i]--;
    }
    dd[key] = true;
    return 0;
}

int cal(int len) {
    int target = pows[len];
    int remainder = target - len;  // all ones
    if (remainder == 0) {
        Min[len] = 0;  // all ones
    } else {
        Min[len] = minCoins(remainder, len);
    }
}

int main() {
    IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif

    int diff = 3;
    pows[1] = 1;
    rep(i, 2, 9001) {
        pows[i] = pows[i - 1] + diff;
        diff += 2;
        // calc(i);
    }
    rep(i, )
        // dp(36, 5);
        SOLVE {
        cin >> n;
        int r;
        LL points = 0;
        rep(i, ceil(sqrt(n)), floor(sqrt(n * 81) + 1)) {  // from 1 to 9k at most
            rep(x, 1, 10) result[x] = 0;

            int t = pows[i];
            int maxOnes = max(0, n - (t - n) / 3);
            minCoins(t);

            // cout << "try" << pows[i] << "- " << maxOnes << endl;
            for (int ones = maxOnes; ones >= 0; ones--) {
                int digits = n - ones;
                if (ones + (digits)*4 > t) break;
                // if (ones + (digits)*81 > t) break;
                result[1] = ones;
                int target = pows[i] - ones;
                // if (target != digits && target - digits < 3) break;
                // cout << "==================== " << ones << "- " << endl;

                int sol = target == digits || dp(target, digits);
                if (sol) {
                    rep(j, 1, 10) rep(k, 0, result[j]) cout << j;
                    cout << endl;
                    goto solve;
                }
            }
            // result.clear();
            // cout << pows[i];
        }

        cout << -1 << endl;
    }
}