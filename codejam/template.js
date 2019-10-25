function solve() {
    const N = +readline();
    for (var ix = 0; ix < N; ix++) {
        const result = solveCase()
        console.log(`Case #${ix + 1}: ${result}`)
    }
}
function solveCase() {
    var firstLine = readline().split(' ')
    var N = parseInt(firstLine[0])
    var P = parseInt(firstLine[1])

    var trie = new Trie()
    var prefixes = [];
    for (var p = 0; p < P; p++) {
        var line = readline();
        prefixes.push(line);
        trie.add(line);
    }

    if (trie.root.isPrefixEnded) {
        return 0
    }

    const initialTotal = Math.pow(2, N)
    const branches = getTrieBranchLengths(trie.root)

    const subtractValues = branches
        .map(b => {
            return Math.pow(2, N - b)
        })
        .reduce((acc, cur) => {
            return acc + cur
        }, 0)

    return initialTotal - subtractValues
}

function getTrieBranchLengths(node) {
    if (!node) {
        return []
    }

    if (node.isPrefixEnded) {
        return [0]
    }

    const branchB = getTrieBranchLengths(node.children.B).map(x => x + 1)
    const branchR = getTrieBranchLengths(node.children.R).map(x => x + 1)

    const result = [].concat(branchB).concat(branchR)

    return result
}

class TrieNode {
    constructor() {
        this.children = {}
        this.isPrefixEnded = false
    }
}

//
// Trie
//
class Trie {
    constructor() {
        this.root = new TrieNode()
    }

    add(prefix) {
        let currentTrieNode = this.root
        for (let index = 0; index < prefix.length; index++) {
            const char = prefix[index]

            if (index === prefix.length - 1) {
                currentTrieNode = this.preCheckLastNode(char, currentTrieNode)
            }

            if (currentTrieNode.isPrefixEnded) {
                return
            }

            currentTrieNode = this.checkAddNode(char, currentTrieNode)
        }

        currentTrieNode.isPrefixEnded = true
        currentTrieNode.children = {}
    }

    checkAddNode(char, node) {
        if (!node.children[char] && node.isPrefixEnded === false) {
            node.children[char] = new TrieNode()
        }

        return node.children[char]
    }

    preCheckLastNode(char, node) {
        const otherChar = this.getOtherChar(char)

        if (
            !node.children[char] &&
            node.children[otherChar] &&
            node.children[otherChar].isPrefixEnded
        ) {
            node.isPrefixEnded = true
            node.children = {}
        }

        return node
    }

    getOtherChar(char) {
        return char === 'B' ? 'R' : 'B'
    }
}



// Boilerplate
// const lines = [];
var lines =
    `4
3 2
BBB
RB
5 1
R
4 3
R
B
RBRB
50 5
BRBRBBBRBRRRBBB
BRBRBRRRBRRRBRB
BBBRBBBRBRRRBBB
BRBRBRRRBRRRB
BRBRBBBRBBBRB`.split('\n');

lines = [];
function readline() {
    return lines.shift();
}

function main() {
    const rl = require('readline').createInterface({
        input: process.stdin,
        output: process.stdout,
        terminal: false
    });
    var timer = setTimeout(() => rl.close(), 1000); // should be enough to read in the server
    rl.on('line', (line) => {
        lines.push(line);
    }).on('close', () => {
        clearInterval(timer);
        solve()
        process.exit(0)
    });
}

main();