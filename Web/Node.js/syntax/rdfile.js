var fs = require('fs');
fs.readFile('static/sample.txt','utf-8',function(err,data){
    console.log(data);
})