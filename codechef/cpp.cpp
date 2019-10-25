// g++ cpp.cpp -o a.out && ./a.out < input.txt
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rep1(i, n) for (int i = 1; i <= (n); i++)
#define watch(x) cerr << (#x) << " is " << (x) << endl

typedef long long int LL;
#define MAX 1000002
// clang-format on

int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
                101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211,
                223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347,
                349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479,
                487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631,
                641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787,
                797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947,
                953, 967, 971, 977, 983, 991, 997};
int p = sizeof(PRIMES) / sizeof(*PRIMES);
// vector<vector<int>> divisors(MAX);
vector<int> divisors(MAX);

void getDivisors(int n) {
    if (divisors[n]) return;

    int s = sqrt(n) + 1;
    // set<int> se;

    rep(i, p) {
        if (PRIMES[i] > s) break;
        if (n % PRIMES[i] == 0) {
            // int dd = n / PRIMES[i];
            // getDivisors(dd);

            // for (int d : divisors[dd]) se.insert(d);
            // if (divisors[dd].size() > 1) for (int d : divisors[dd]) se.insert(d * PRIMES[i]);

            // se.insert(PRIMES[i]);
            divisors[n] = PRIMES[i];
        }
    }
    // se.insert(n);
    // divisors[n].assign(se.begin(), se.end());
    // divisors[n].emplace_back(n);
    // rep(k, divisors[n].size()) cout << n << "n" << divisors[n][k] << endl;
}

int solve(vector<int> &A) {
    vector<int> divisibleBy(MAX);
    int n = A.size();
    int m = 0;
    rep(i, n) {
        int curr = A[i];
        int divBy = divisibleBy[curr];
        if (curr == 1) {
            divBy = i;
        }
        m = max(m, divBy);
        getDivisors(curr);
        auto d = divisors[curr];
        rep(j, d.size()) {
            divisibleBy[d[j]]++;
            // cout << "div " << curr << ":" << d[j] << ": " << divisibleBy[d[j]] << endl;
        }
    }
    // cout << m << endl;

    return m;
}

int main() {
    IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
#endif
    SOLVE {
        int n;
        cin >> n;

        // vector<int> A(n);
        // rep(i, n) cin >> A[i];

        n = 1000000;  // local test case
        vector<int> A(n);
        rep(j, n) A[j] = n - j + 1;
        clock_t begin = clock();

        cout << solve(A) << endl;
        // cout << solve(A) << endl;
        // cout << solveBF(A) << endl; cout << "e" << endl;
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << elapsed_secs << " elapsed" << endl;
    }
}
