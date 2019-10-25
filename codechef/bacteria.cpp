// g++ cpp.cpp -o a.out && ./a.out < input.txt
/**
5 8
4 3
3 1
5 2
1 2
1 10 4 9 4
? 2
+ 1 6
? 3
+ 3 5
? 3
+ 2 2
+ 5 10
? 5
? 4
**/
#include <bits/stdc++.h>
using namespace std;
// clang-format off
#define SOLVE int TT; cin >> TT; solve:while (TT--)
#define IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rep1(i, n) for (int i = 1; i <= (n); i++)
#define watch(x) cerr << (#x) << " is " << (x) << endl

typedef long long int LL;
// max is time spread + total depth - 1M is worst case - we can do better if we need
#define MAX 1000001
// clang-format on
//https://cp-algorithms.com/data_structures/fenwick.html
struct FenwickTree {
    vector<LL> bit;  // binary indexed tree
    int n;

    FenwickTree(int n) {
        this->n = n;
        bit.assign(n, 0);
    }

    // FenwickTree(vector<int> a) : FenwickTree(a.size()) {
    //     for (size_t i = 0; i < a.size(); i++)
    //         add(i, a[i]);
    // }

    LL sum(int r) {
        LL ret = 0;
        for (; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }

    LL sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, LL delta) {
        for (; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
};
FenwickTree tree(MAX);

struct node {
    vector<int> children;
    int parent;
    int depth;
    vector<pair<int, LL>> addBacteria;
    vector<int> queries;  // pointer to global list
};
vector<node> nodes;
vector<pair<int, LL>> queries;

int globalTime = 0;
void calcTreeInfoDfs(int v, int parent, int depth) {
    node *n = &nodes[v];
    int parentIndex = -1;
    n->depth = depth;
    rep(i, n->children.size()) {
        int u = n->children[i];
        if (u == parent) {
            parentIndex = i;
        } else {
            calcTreeInfoDfs(u, v, depth + 1);
        }
    }
    // remove parent
    if (parentIndex >= 0) {
        n->children.erase(n->children.begin() + parentIndex);
        n->parent = parent;
    }
}

LL query(int ix, int time) {
    // int adjustedTime = time - nodes[ix].depth;

    if (nodes[ix].children.size() == 0) {  // leaf
        return tree.sum(0, time);
    } else {
        return tree.sum(time, time);
    }
}

void traverseTreeDfs(int v) {
    node *n = &nodes[v];
    rep(i, n->addBacteria.size()) {  // add bacteria to the tree
        tree.add(n->addBacteria[i].first, n->addBacteria[i].second);
    }
    rep(i, n->queries.size()) {  // solve queries in node
        int time = queries[n->queries[i]].first;
        LL res = query(v, time);
        queries[n->queries[i]].second = res;
    }

    rep(i, n->children.size()) {  // solve queries in children
        traverseTreeDfs(n->children[i]);
    }

    rep(i, n->addBacteria.size()) {  // remove my queries to continue in parent
        tree.add(n->addBacteria[i].first, -n->addBacteria[i].second);
    }
}
void addBacteria(int ix, LL amount, int time) {
    int adjustedTime = time - nodes[ix].depth;
    nodes[ix].addBacteria.emplace_back(make_pair(adjustedTime, amount));
}

void addQuery(int ix, int time) {
    int adjustedTime = time - nodes[ix].depth;
    queries.emplace_back(make_pair(adjustedTime, -1));  // to return result
    nodes[ix].queries.emplace_back(queries.size() - 1);
}

int main() {
    IO;
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);  // freopen("output.txt", "w", stdout);
#endif
    // SOLVE
    {
        int n, q;
        int u, v;

        cin >> n >> q;

        nodes.resize(n + 1);

        rep(i, n - 1) {
            cin >> u >> v;
            nodes[u].children.emplace_back(v);
            nodes[v].children.emplace_back(u);
        }

        calcTreeInfoDfs(1, -1, 0);

        globalTime = 500000 - 1;  // we'll deduct depth -
        LL bacteria;
        rep1(i, n) {
            cin >> bacteria;
            addBacteria(i, bacteria, globalTime);
        }

        char op;
        LL x, y;

        rep(i, q) {
            cin >> op;
            globalTime++;
            if (op == '+') {
                cin >> x >> y;
                addBacteria(x, y, globalTime);
            } else {
                cin >> x;
                addQuery(x, globalTime);
                // cout << query(x) << endl;
            }
        }
        traverseTreeDfs(1);

        rep(i, queries.size()) {
            cout << queries[i].second << endl;
        }
    }
}