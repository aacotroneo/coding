// nodejs is very slow!!! javascript version is much faster
module.exports = solve;

function solve() {
    var [n, m] = readline();
    var min = 999999;
    for (var i = 0; i < n; i++) {
        const [a, b]= readline();
        min = Math.min(min, a / b)
    }
    return min * m;
}

function readline(){
    return lines.shift();
}
const lines = [];
const rl = require('readline').createInterface({
    input: process.stdin,
    output: process.stdout,
    terminal: false
});
rl.on('line', (line) => {
    lines.push(line.split(' ').map(n => parseInt(n, 10)));    
    if(lines.length -1 === lines[0][0]) {
        console.log(solve());
        rl.close();
    }
});