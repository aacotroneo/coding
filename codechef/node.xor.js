process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('end', start);

var data =``
    `4
3
5 2 7
6
4 2 7 1 1 1
7
1000 4 2 7 1 1 1
8
1000 4 2 7 1 1 1 1000
`;
var lines = '';
// 2
// 10
// 10
// 17
process.stdin.on('data', function (chunk) {
    data += chunk;
});

var line = 0;
function readline() {
    return lines[line++];
}
var localTimer = setTimeout(() => { console.log('start local', data); start() }, 1000); // should be enough to read in the server
function start() {
    clearTimeout(localTimer);
    lines = data.split('\n');
    var t = +readline();
    for (var i = 0; i < t; i++) {
        console.log(solveCase())
    }
}

function solveCase() {
    var n = +readline();
    var As = readline().split(' ');
    var vals = new Array(n + 2);
    vals[As[0]] = [0]; 
    vals[0] = [-1];

    var cache = new Array(n + 2);
    cache[As[0]] = 0
    cache[0] = 0
    
    
    var perm = 0;
    var prev = As[0];
    for (var i = 1; i < n; i++) {
        var v = prev ^ As[i];
        var curr = vals[v] || new Array(0); 
        var l = curr.length;
        if(l) {
            if(l === 1) {
                var perms = i - ( curr[0] + 1);
                perm += perms;
                cache[v] = perms;
            } else {
                var lastVal = cache[v];
                var newVal = lastVal + (i - curr[l - 1]) * (l) - 1
                perm += newVal;
                cache[v] = newVal;    
            }
        }
        curr.push(i);
        vals[v] = curr; 
        prev = v;
    }

    // non -optimized
    // var acc = new Array(n);
    // acc[0] = As[0];
    // var perm2 = 0;
    // for (var i = 0; i < n; i++) {
    //     acc[i] = As[i];
    //     vals[i] = vals[i] && vals[i].push()
    //     for (var j = i + 1; j < n; j++) {
    //         acc[j] = acc[j - 1] ^ As[j];
    //         if (acc[j] === 0) {
    //             perm2 += (j - i)
    //         }
    //     }
    // } 1 4  = 2 
    // 1 4 9 ==>  4 + 7 => 11 = 
    // 1 4 9  10 => 0 + 5 + 8 => 13 = 11 + 1 * 2
    // 1 4 9  10 11 => 1 + 6 + 9 => 16 = 13 + 1 * 3 
    // 1 4 9 15 => 5 + 10 + 14 = 29  = 11 + 6 * 2 + 6
    return perm;
}


