const solve = require('./codeforces/wrongSubstraction');

const assert = require('assert').strict;
const cases = [
    { in: 
`3
4 3`, out: '4' },
    { in: '3 3', out: '4' },
    // { in: '3', out: '1' },
];

let failed = 0;
cases.forEach(c => {
    const res = solve(c.in);
    try {
        assert(res.toString() === c.out, 'Expected ' + res + ' to equal ' + c.out);
        console.log('passed');
    } catch (e) {
        failed++;
        print(e.message);
    }
});
if (failed) {
    print(failed + ' failed');
} else {
    print("pass");
}
process.exit();


function print() {
    console.log(...arguments);
    // process.stdout.write(...args);
}