var http = require('http');
var fs = require('fs');
var url = require('url');

var app = http.createServer(function(request,response){
    var url = request.url;
    console.log(url);
    if(url == '/'){
      url = '/index.html';
    }
    if(url == '/favicon.ico'){
      response.writeHead(404);
      response.end();
      return;
    }
    response.writeHead(200);
    // console.log(__dirname+url);
    response.end(fs.readFileSync(__dirname + url)); // response user data
    // Produce the data for responsing <- Power of Node.js , Django, etc. API
 
});
app.listen(3000);
// app.listen(80); default web server port : 80