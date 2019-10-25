'use strict';
var input = readline().split(' ').map(i => +i);
var n = input[0], w = input[1], h = input[2];

var cache = { fits: {} };
var envs = new Array(n);
for (var i = 0; i < n; i++) {
    var l = readline().split(' ').map(i => +i);
    envs[i] = [...l, i]; // w, h, i
}

envs = envs.filter(v => v[0] > w && v[1] > h).sort((a, b) => {
    if (a[0] == b[0]) return a[1] - b[1]; // order by widht, then height
    return a[0] - b[0];
});

function doDP(envs) {
    if (!envs.length) return [];
    // -- DP
    var dp = new Array(envs.length);
    dp[0] = { max: 1, i: 0 };
    var best = 0;
    for (var i = 1; i < envs.length; i++) {
        var envI = envs[i];
        var max = 0;
        var maxJ = -1;
        for (var j = 0; j < i; j++) {
            var envJ = envs[j];
            var fits = envI[0] > envJ[0] && envI[1] > envJ[1];
            if (fits && dp[j].max > max) {
                max = dp[j].max;
                maxJ = j;
            }
        }
        dp[i] = { max: max + 1, i: maxJ };
        if (dp[i].max > dp[best].max) {
            best = i;
        }
    }
    // - end DP

    // build path from indexes in reverse
    var index = best;
    var path = [];

    // print(dp, index)

    while (index > 0) {
        path.unshift(envs[index][2] + 1);
        index = dp[index].i
    }
    if (index === 0) {
        path.unshift(envs[index][2] + 1); // 0
    }
    return path;
}

const p = doDP(envs);

print(p.length);
if (p.length) {
    print(p.join(' '));
} 
