// g++ cpp.cpp -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define watch(x) cerr << "\n" << (#x) << " is " << (x) << endl

typedef unsigned long long int LL;
// clang-format on
int i, n, q;

char Q[1000001] = {};
list<int> sols[1000001];
list<int> sols2[1000001];

int countSol(int coeff[], int n, int rhs) {
    // Create and initialize a table
    // to store results of subproblems
    int dp[rhs + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;

    // Fill table in bottom up manner
    for (int i = 0; i < n; i++)
        for (int j = coeff[i]; j <= rhs; j++) {
            int isSol = dp[j - coeff[i]];
            sols2[isSol].push_back(i);
            // cout <<i<< "J " << j << " " << Q[j] << " "<< dp[j] <<  endl;
            if(isSol) {
                dp[j] += isSol;
                if (Q[j]) sols[j].push_back(i);

            }
        }

    return dp[rhs];
}


LL calSeqs(list<int> l) {
    if (l.size() == 0) return 0;

    LL s = 0;
    int last = -1;
    LL open = 0;
    LL skipped = 0;
    int size = l.size();
    rep(i, 0, size) {
        int ix = l.front();
        l.pop_front();
        skipped = (ix - (last + 1)) * (1 + open);
        open += skipped + 1;
        // open = (i + 1) + 1; // (i + 1) + ix - (last + 1) ;
        s += open;
        cout << ix << ":" << s << " ";
        last = ix;
    }
    skipped = (n - (last + 1)) * open;
    s += skipped;
    // cout << n << ":" << s << " "; 
    return s;
}

int main() {
    IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    // SOLVE
    {
        cin >> n;
        int A[n];
        rep(i, 0, n) cin >> A[i];

        cin >> q;
        int QQ[q];
        rep(i, 0, q) cin >> QQ[i], Q[QQ[i]] = '1';

        int maxQ = -1;
        rep(i, 0, q) maxQ = max(maxQ, QQ[i]);

        // map<int, int> m;
        // DP dp(n + 1, m);
        // rep(i, 0, n + 1) dp[0][i] = 1;

        // cout << maxQ << "++" << endl;
        // setup(A, n, maxQ);
        countSol(A, n, maxQ);

        // rep(i, 0, maxQ + 1) cout << dp[n][i] << ":" << endl;
        // cout << dp[5][8] << "++" << endl;
        // rep(i, 0, q) cout << Q[i] << ":" << dp[n][Q[i]] << endl;
        // rep(i, 0, q) cout << Q[i] << endl;
        rep(i, 0, q) cout << calSeqs(sols[QQ[i]]) << endl;
    }
}