// #include <bits/stdc++.h>
// g++ cpp.cpp -o a.out && ./a.out < input.txt
#include <algorithm>
#include <iostream>
#include <vector>

#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
#define debug(...) fprintf(stderr, __VA_ARGS__)

// 	vector<int> poss;
// 	for (auto res : poss) {
//     // res is an int
// 		sort(cnt.begin(), cnt.end());
// accumulate(cnt.begin(), cnt.begin() + k
for (auto& elem : vec)

typedef long long int LL;

struct son {
    int y;
    int m;
};
bool comp(const son &a, const son &b) { return a.y < b.y; }
using namespace std;
string solve() {
    int n, i;
    bool res;
    n = 3;

    vector<son> v;

    rep(i, n) {
        son temp;
        cin >> temp.y;
        v.push_back(temp);
    }
    rep(i, n) { cin >> v[i].m; }

    // rep(i, n) { cout << v[i].y << " " << v[i].m << endl;}

    std::sort(l.begin(), l.end(), [](int a, int b) {return a > b; }));

    std::sort(v.begin(), v.end(), comp);

    for (int i = 1; i < 3; i++) {
        if (v[i - 1].y < v[i].y) {
            if (v[i - 1].m >= v[i].m) return "NOT FAIR";
        } else {
            if (v[i - 1].m != v[i].m) return "NOT FAIR";
        }
    }

    return "FAIR";
}

int main() {
    int t;
    cin >> t;
    while (t > 0) {
        string res = solve();
        cout << res << endl;
        t--;
    }
    return 0;
}

LL perms(int n, int k) {
    if (k > n) return 0;
    if (k * 2 > n) k = n - k;
    if (k == 0) return 1;

    LL result = n;
    for (int i = 2; i <= k; ++i) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}
