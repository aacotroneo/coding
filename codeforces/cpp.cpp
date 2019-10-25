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

#include <bits/stdc++.h>

using namespace std;

// clang-format on
int n, girls, assistants;

int solve() {

    int maxBoys = min(boys, assistants);
    int maxGirls = min(girls, assistants);

    if(boys > assistants || girls > assistants) return assistants + 1;

    return min(boys, girls)

}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> boys >> girls >> assistants;

    
    cout << solve() << endl;
}