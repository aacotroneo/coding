process.stdin.resume();
process.stdin.setEncoding('utf8');

process.stdin.on('data', function (chunk) {
    var lines = chunk.toString().split('\n');
    let n = lines.shift();
    lines.forEach(function (line) {
        if (line === '42') {
            process.exit();
        }
        const result = solveLine.apply(null, line.split(' '));
        // process.stdout.write(line + '\n');
        process.stdout.write(result + '\n');
    });
});

class Tree {

    constructor(size) {
        this.size = size;
        this.root = { pt: null };
    }

    insert(val, node, key) {
        if (!node.pt) {
            node.pt = { val, key, left: {}, right: {} };
            return key;
        } else {
            if (val < node.pt.val) {
                return this.insert(val, node.pt.left, 2 * key)
            } else {
                return this.insert(val, node.pt.right, 2 * key + 1);
            }
        }
    }
    remove(val, node, key) {
        if (!node.pt) {
            return -1;
        }
        if (val < node.pt.val) {
            return this.remove(val, node.pt.left, 2 * key);

        } else if (val > node.pt.val) {
            return this.remove(val, node.pt.right, 2 * key + 1);
        }
        //equals

        if (!node.pt.left.pt && !node.pt.right.pt) {
            node.pt = undefined;
        } else if (!node.pt.right.pt) { // && left
            node.pt = node.pt.left.pt;
        } else if (!node.pt.left.pt) { // && right
            node.pt = node.pt.right.pt;
        } else {
            let min = node.pt.right.pt;
            while (min.left.pt) { min = min.left.pt; }
            node.pt.val = min.val;
            this.remove(min.val, node.pt.right, 0);
        }

        return key;
    }

}

const t = new Tree(1000);
function solveLine(op, val) {
    // console.log(op, val);
    if (op === 'i') return t.insert(val, t.root, 1);
    return t.remove(val, t.root, 1);
}