process.stdin.resume();
process.stdin.setEncoding('utf8');
process.stdin.on('end', start);
// 1
// 1
// 3
// 18
// 10
// 3
// 6
// 15
// 24
// 28

var data =
    `10
4
2 1 3
1 2
2 3
2 4
4
2 1 3
1 2
2 3
2 4
10
2 1 3
7 1
5 7
2 7
7 3
4 7
6 7
8 7
9 7
10 7
10
3 2 1
7 1
5 7
2 7
7 3
4 7
6 7
8 7
9 7
10 7
6
1 1 2
2 1 
2 4
1 5
2 6
3 2
6
3 2 1
1 2
2 3
2 4
1 5
2 6
8
1 3 2
8 1
8 7
1 2
2 3
2 4
1 5
2 6
10
2 3 3
7 1
7 2
7 3
7 4
7 5
7 6
7 8
7 9
7 10
8
2 1 3
8 7
7 6
6 5
5 1
1 2
2 3
3 4
11
2 2 3
1 7
5 7
2 7
3 7
4 7
6 7
8 7
9 7
10 7
11 6
`;

data = `1
3000
1 2 3
`
for(c = 1; c < 3000; c++) {
    data += c + ' ' + (c + 1) + `\n`;
}

var lines = '';
process.stdin.on('data', function (chunk) {
    data += chunk;
});

var l = 0;
function readline() {
    return lines[l++];
}
// const { performance } = require('perf_hooks');

var localTimer = setTimeout(() => { console.log('start local', data); start() }, 1000); // should be enough to read in the server
function start() {
    clearTimeout(localTimer);
    lines = data.split('\n');
    var t = +readline();

    var time = process.hrtime();

    for (var i = 0; i < t; i++) {
        console.log(solveCase());
        var diff = process.hrtime(time);
        console.log(diff[0] * 1e3 + diff[1] / 1e6);
    }
    process.exit(0);
}

function solveCase() {
    var n = +readline();
    var Ps = readline();

    var type = +Ps.split(' ')[1]

    var nodes = new Array(n + 1);

    for (var i = 1; i <= n + 1; i++) {
        nodes[i] = { ch: SortedList.create({ unique: true }) }// l: SortedList.create(), r: SortedList.create() };
    }
    for (var i = 1; i < n; i++) {
        var e = readline().split(' ');
        var n1 = +e[0];
        var n2 = +e[1];
        var N1 = nodes[n1];
        var N2 = nodes[n2];

        N1.ch.insertOne(n2);
        N2.ch.insertOne(n1);
    }

    // var start = nodes[i];
    var tuples = 0;
    var startingNode = n;
    getChildren(startingNode);
    function getChildren(currentNode, from) {
        var node = nodes[currentNode];
        var parLoc = node.ch.key(from);
        if (parLoc != null) {
            node.ch.remove(parLoc); // remove parent from children
        }
        var groups = [];

        for (var i = 0; i < node.ch.length; i++) {
            var child = node.ch[i];
            var chNode = nodes[child];
            if (child === from) {
                parLoc = i;
                continue;
            }
            if (chNode.ch.length === 1) {
                groups.push([child]);
            } else {
                var grandCh = getChildren(child, currentNode);
                grandCh.insertOne(child)
                groups.push(grandCh);
            }
        }
       // if (parLoc >= 0) node.ch.key(parLoc);

        if (currentNode === startingNode && node.ch.length === 1) {
            return;
        }

        var sizesMore = new Array();
        var sizesLess = new Array();
        var moreIx = 0;
        var lessIx = 0;
        var moreOnes = 0;
        var lessOnes = 0;
        var sumMore = 0;
        var sumLess = 0;

        for (var j = 0; j < groups.length; j++) {
            var group = groups[j];
            if (group.length === 1) {
                if (group[0] > currentNode) {
                    moreOnes++;
                    sumMore++;
                } else {
                    lessOnes++;
                    sumLess++;
                }
            } else {
                var pos = group.bsearch(currentNode);
                var belowLess = pos + 1;
                var belowMore = group.length - pos - 1;

                // console.log(pos, belowLess, belowMore, group.toArray());
                sizesMore[moreIx] = belowMore;
                sizesLess[lessIx] = belowLess;
                sumMore += sizesMore[moreIx];
                sumLess += sizesLess[lessIx];
                moreIx++;
                lessIx++;

                // node.ch.insert(...group);
                if(node.ch.length > group.length) {
                    for (var m = 0; m < group.length; m++) {
                        node.ch.insertOne(group[m]);
                    }
                }else {
                    for (var m = 0; m < node.ch.length; m++) {
                        group.insertOne(node.ch[m]);
                    }
                    node.ch = group;
                }
                
            }
        }

        sizesMore[moreIx] = n - currentNode - sumMore; // parent path.
        sumMore += sizesMore[moreIx];
        moreIx++;
        // moreOnes++;

        sizesLess[lessIx] = currentNode - sumLess - 1; // parent path.
        sumLess += sizesLess[lessIx];
        lessIx++;
        // lessOnes++;
        var tups = 0;
        // console.log(sizesMore, moreIx);

        if (type === 1) {
            for (var k = 0; k < moreIx; k++) {
                for (var l = k + 1; l < moreIx; l++) {
                    tups += (sizesMore[k]) * (sizesMore[l]);
                    // tups += (moreOnes) * (sizesMore[k]);
                }
                // tups += (sumMore - sizesMore[k] - moreOnes) * (sizesMore[k] - 1);
                tups += (moreOnes) * (sizesMore[k]);
            }
            tups += moreOnes * (moreOnes - 1) / 2;
            tuples += tups;
        } else if (type === 2) {
            for (var k = 0; k < moreIx; k++) {
                // if(sizesMore[k] == 0) continue;
                for (var l = 0; l < lessIx; l++) {
                    if (l === k) {
                        tups += (moreOnes) * (sizesLess[l]);
                        tups += (lessOnes) * (sizesMore[k]);
                    } else {
                        // if(sizesLess[l] == 0) continue;
                        tups += sizesLess[l] * sizesMore[k];
                    }
                }
            }

            tups += (moreOnes * lessOnes);
            tuples += tups;
        } else if (type === 3) {
            for (var k = 0; k < lessIx; k++) {
                for (var l = k + 1; l < lessIx; l++) {
                    tups += (sizesLess[k]) * (sizesLess[l]);
                    // tups += (lessOnes) * (sizesless[k]);
                }
                // tups += (sumless - sizesless[k] - lessOnes) * (sizesless[k] - 1);
                tups += (lessOnes) * (sizesLess[k]);
            }
            tups += lessOnes * (lessOnes - 1) / 2;
            tuples += tups;
        }

        // console.log( node.ch.toArray())
        return node.ch;

    }

    return tuples;
}


/*package.json
{
  "volo": {
    "dependencies": {
      "sortedlist": "github:shinout/SortedList"
    }
  }
}
*/

/**
 * SortedList : constructor
 */
var SortedList = function SortedList() {
    var arr = null,
        options = {},
        args = arguments;

    ["0", "1"].forEach(function (n) {
        var val = args[n];
        if (Array.isArray(val)) {
            arr = val;
        }
        else if (val && typeof val == "object") {
            options = val;
        }
    });

    if (typeof options.filter == 'function') {
        this._filter = options.filter;
    }

    if (typeof options.compare == 'function') {
        this._compare = options.compare;
    }
    else if (typeof options.compare == 'string' && SortedList.compares[options.compare]) {
        this._compare = SortedList.compares[options.compare];
    }

    this._unique = !!options.unique;

    if (options.resume && arr) {
        arr.forEach(function (v, i) { this.push(v) }, this);
    }
    else if (arr) this.insert.apply(this, arr);
};

/**
 * SortedList.create(val1, val2)
 * creates an instance
 **/
SortedList.create = function (val1, val2) {
    return new SortedList(val1, val2);
};


SortedList.prototype = new Array();
SortedList.prototype.constructor = Array.prototype.constructor;

/**
 * sorted.insertOne(val)
 * insert one value
 * returns false if failed, inserted position if succeed
 **/
SortedList.prototype.insertOne = function (val) {
    var pos = this.bsearch(val);
    if (this._unique && this.key(val, pos) != null) return false;
    if (!this._filter(val, pos)) return false;
    this.splice(pos + 1, 0, val);
    return pos + 1;
};

/**
 * sorted.insert(val1, val2, ...)
 * insert multi values
 * returns the list of the results of insertOne()
 **/
SortedList.prototype.insert = function () {
    return Array.prototype.map.call(arguments, function (val) {
        return this.insertOne(val);
    }, this);
};

/**
 * sorted.remove(pos)
 * remove the value in the given position
 **/
SortedList.prototype.remove = function (pos) {
    this.splice(pos, 1);
    return this;
}

/**
 * sorted.bsearch(val)
 * @returns position of the value
 **/
SortedList.prototype.bsearch = function (val) {
    if (!this.length) return -1;
    var mpos,
        mval,
        spos = 0,
        epos = this.length;
    while (epos - spos > 1) {
        mpos = Math.floor((spos + epos) / 2);
        mval = this[mpos];
        var comp = this._compare(val, mval);
        if (comp == 0) return mpos;
        if (comp > 0) spos = mpos;
        else epos = mpos;
    }
    return (spos == 0 && this._compare(this[0], val) > 0) ? -1 : spos;
};

/**
 * sorted.key(val)
 * @returns first index if exists, null if not
 **/
SortedList.prototype.key = function (val, bsResult) {
    if (bsResult == null) bsResult = this.bsearch(val);
    var pos = bsResult;
    if (pos == -1 || this._compare(this[pos], val) < 0)
        return (pos + 1 < this.length && this._compare(this[pos + 1], val) == 0) ? pos + 1 : null;
    while (pos >= 1 && this._compare(this[pos - 1], val) == 0) pos--;
    return pos;
};

/**
 * sorted.key(val)
 * @returns indexes if exists, null if not
 **/
SortedList.prototype.keys = function (val, bsResult) {
    var ret = [];
    if (bsResult == null) bsResult = this.bsearch(val);
    var pos = bsResult;
    while (pos >= 0 && this._compare(this[pos], val) == 0) {
        ret.push(pos);
        pos--;
    }

    var len = this.length;
    pos = bsResult + 1;
    while (pos < len && this._compare(this[pos], val) == 0) {
        ret.push(pos);
        pos++;
    }
    return ret.length ? ret : null;
};

/**
 * sorted.unique()
 * @param createNew : create new instance
 * @returns first index if exists, null if not
 **/
SortedList.prototype.unique = function (createNew) {
    if (createNew) return this.filter(function (v, k) {
        return k == 0 || this._compare(this[k - 1], v) != 0;
    }, this);
    var total = 0;
    this.map(function (v, k) {
        if (k == 0 || this._compare(this[k - 1], v) != 0) return null;
        return k - (total++);
    }, this)
        .forEach(function (k) {
            if (k != null) this.remove(k);
        }, this)
    return this;
};

/**
 * sorted.toArray()
 * get raw array
 **/
SortedList.prototype.toArray = function () {
    return this.slice();
};


/**
 * default filtration function
 **/
SortedList.prototype._filter = function (val, pos) {
    return true;
};


/**
 * comparison functions 
 **/
SortedList.compares = {
    "number": function (a, b) {
        var c = a - b;
        return (c > 0) ? 1 : (c == 0) ? 0 : -1;
    },

    "string": function (a, b) {
        return (a > b) ? 1 : (a == b) ? 0 : -1;
    }
};

/**
 * sorted.compare(a, b)
 * default comparison function
 **/
SortedList.prototype._compare = SortedList.compares["string"];