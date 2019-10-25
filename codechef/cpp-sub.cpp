// g++ cpp.cpp -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

typedef unsigned long long int LL;
// clang-format on
#define MOD 1000000007

int i, n, k;

LL countSeq(vector<int> groups, int n, int k) {
    vector<LL> seqsOfLen(k + 1, 0);
    seqsOfLen[0] = 1;
    rep(i, 0, n) for (int j = min(k, n); j >= 1; j--)
        seqsOfLen[j] = (seqsOfLen[j] + seqsOfLen[j - 1] * groups[i]) % MOD;

    LL sum = 0;
    rep(i, 0, n) {
        sum = (sum + seqsOfLen[i]); // % MOD;
    }
    return sum;
}
int main() {
    IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    // SOLVE
    {
        cin >> n >> k;
        map<int, int> m;
        int x;
        rep(i, 0, n) {
            cin >> x;
            m[x]++;
        }
        vector<int> groups;
        for (auto i = m.begin(); i != m.end(); i++) groups.emplace_back(i->second);

        cout << countSeq(groups, groups.size(), k) << endl;
    }
}