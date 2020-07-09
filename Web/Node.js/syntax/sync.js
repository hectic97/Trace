var fs = require('fs');

//readFileSync
// console.log('A');
// var result=fs.readFileSync('static/sample.txt','utf-8');
// console.log(result);
// console.log('C');

console.log('A');
fs.readFile('static/sample.txt', 'utf-8', function(err,result){   
    // 비동기적 실행, function을 실행 (병렬), err있으면 첫째 인자,결과는 둘째
    console.log(result);
});
console.log('C');