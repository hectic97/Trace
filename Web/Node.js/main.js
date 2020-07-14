var http = require('http');
var fs = require('fs');
var url = require('url');
var qs = require('querystring');
var template = require('./lib/template.js');
var path = require('path');
var cookie = require('cookie');
// var sanitizeHtml = require('sanitize-html');
function authIsOwner(request,response){
    var isOwner = false;
    var cookies = {}
    if (request.headers.cookie){
      cookies = cookie.parse(request.headers.cookie);
    }
    
    if (cookies.email === 'hello' && cookies.password === 'world'){
      isOwner = true;
    }
    return isOwner;
}
function authStatusUI(request,response){
  var authStatusUI = `<a href="/login">login</a>`;
  if (authIsOwner(request,response)){
    authStatusUI = `<a href="/logout_process">logout</a>`;
    
  }
  return authStatusUI;
}
function notAuthrized(request,response){
  if (authIsOwner(request,response)===false)
      {
        response.end('Login Required');
        return false
      }
}

var app = http.createServer(function(request,response){
    var _url = request.url;
    var queryData = url.parse(_url,true).query;
    var pathname = url.parse(_url,true).pathname;
    if (pathname === '/') //homepage
    {
      if(queryData.id === undefined)
      {
        fs.readdir('./data',function(error,filelist)
        {
          var title = 'Welcome';
          var description = 'Hello, Node.js';
          var list = template.list(filelist); 
          var html = template.html(title, list, `<h2>${title}</h2>${description}`,
          `<a href ="/create">create</a>`,authStatusUI(request,response)); 
          // console.log(__dirname+url);
          // response.end(fs.readFileSync(__dirname + _url)) // response user data
          // Produce the data for responsing <- Power of Node.js , Django, etc. API
          response.writeHead(200);
          response.end(html);
       }) //fs.readdir end
        
      }
      else // not  hompage
      {
        fs.readdir('./data',function(error,filelist){
          var filteredId = path.parse(queryData.id).base;
          fs.readFile(`data/${filteredId}`,'utf-8',function(err,description){ 
            var title = queryData.id;
            // var sanitizedTitle = sanitizeHtml(title);
            // var sanitizedDescription = sanitizeHtml(description);
            var list = template.list(filelist);
            var html= template.html(title, list, `<h2>${title}</h2>${description}`,
            `<a href ="/create">create</a> <a href="/update?id=${title}">update</a>
            <form action="/delete_process" method="POST">
            <input type="hidden" name="id" value="${title}">
            <input type= "submit" value="delete">
            </form>`,authStatusUI(request,response));
            
            // console.log(__dirname+url);
            // response.end(fs.readFileSync(__dirname + _url)) // response user data
            // Produce the data for responsing <- Power of Node.js , Django, etc. API
            response.writeHead(200);
            response.end(html);
          });
        }); //readdir end
      };
    }
    else if (pathname === '/create')
    {
      notAuthrized(request,response)
      fs.readdir('./data',function(error,filelist)
        {
          var title = 'Web - Create';
          var description = 'Hello, Node.js';
          var list = template.list(filelist); 
          var html = template.html(title, list, `
          <form action="/create_process" method="POST">
              <p><input type="text" name="title" placeholder="title"></p>
              <p>
                <textarea name="description" placeholder="description"></textarea>
              </p>
              <p>
               <input type="submit">
              </p>
          </form>`, '',authStatusUI(request,response)); 
          // console.log(__dirname+url);
          // response.end(fs.readFileSync(__dirname + _url)) // response user data
          // Produce the data for responsing <- Power of Node.js , Django, etc. API
          response.writeHead(200);
          response.end(html);
       })
    }
    else if (pathname === '/create_process')
    {
      if (authIsOwner(request,response)===false)
      {
        response.end('Login Required');
        return false
      }
      var body = '';
      request.on('data',function(data){
        body = body + data;
      
      });
      request.on('end',function(){
        var post = qs.parse(body);
        var title = post.title;
        var description = post.description;
        fs.writeFile(`data/${title}`,description,'utf8',
        function(err){
          response.writeHead(302,{Location: `/?id=${title}`});
          response.end('Success');
        });
        
      });
      
    }
    else if (pathname === '/update')
    {
      if (authIsOwner(request,response)===false)
      {
        response.end('Login Required');
        return false
      }
      var filteredId = path.parse(queryData.id).base;
      fs.readdir('./data',function(error,filelist){
        fs.readFile(`data/${filteredId}`,'utf8',function(err, description){
          var title = queryData.id;
          var list = template.list(filelist);
          var html = template.html(title, list,
            `<form action="/update_process" method="POST">
            <input type = "hidden" name = "id" value = "${title}">
            <p><input type="text" name="title" placeholder="title" value = "${title}"></p>
            <p>
              <textarea name="description" placeholder="description">${description}</textarea>
            </p>
            <p>
             <input type="submit">
            </p>
            </form>`,
            `<a href = "/create">create</a> <a href = "/update?id=${title}">update</a>`
            ,authStatusUI(request,response))
            response.writeHead(200);
        response.end(html);
        });//readfile
        

      });//readdir
    }
    else if (pathname === '/update_process')
    {
      if (authIsOwner(request,response)===false)
      {
        response.end('Login Required');
        return false
      }
      var body = '';
      request.on('data',function(data){
        body = body + data;
      
      });
      request.on('end',function(){
        var post = qs.parse(body);
        var id = post.id;
        var title = post.title;
        var description = post.description;
        fs.rename(`data/${id}`,`data/${title}`,function(err){
          fs.writeFile(`data/${title}`,description,'utf8',
        function(err){
          response.writeHead(302,{Location: `/?id=${title}`});
          response.end('Success');
        });
          
        });
        
        // var description = post.description;
        
        
      });

    }
    else if (pathname === '/delete_process')
    {
      if (authIsOwner(request,response)===false)
      {
        response.end('Login Required');
        return false
      }
      var body = '';
      request.on('data',function(data){
        body = body + data;
      
      });
      request.on('end',function(){
        var post = qs.parse(body);
        var id = post.id;
        var filteredId = path.parse(id).base;
        fs.unlink(`data/${filteredId}`,function(err){
          response.writeHead(302, {Location: '/'});
          response.end();
        });
      });

    }
    else if (pathname === '/login')
    {
      fs.readdir('./data',function(error,filelist)
        {
          var title = 'Login'; 
          var list = template.list(filelist); 
          var html = template.html(title, list,`
          <form action="login_process" method="post">
            <p><input type="text" name="email" placeholder="email"></p>
            <p><input type="password" name="password" placeholder="password"></p>
            <p><input type="submit"></p>
          </form>`,`<a href="/create">create</a>`); 
          response.writeHead(200);
          response.end(html);
       }) //fs.readdir end
    }
    else if (pathname === '/login_process')
    {
      var body = '';
      request.on('data',function(data){
        body = body + data;
      
      });
      request.on('end',function(){
        var post = qs.parse(body);
        if(post.email === 'hello' && post.password === 'world')
        {
          response.writeHead(302,{
            'Set-cookie':[
              `email=${post.email}`,
              `password=${post.password}`,
              `nickname=aa`
            ],
            Location:'/'
          });
          response.end();
        }
        else
        {
          response.end('Not Authorized');
        }
        
        
      });

    }
    else if (pathname === '/logout_process')
    {
      var body = '';
      request.on('data',function(data){
        body = body + data;
      
      });
      request.on('end',function(){
        var post = qs.parse(body);
        response.writeHead(302,{
          'Set-cookie':[
            `email=;Max-Age=0`,
            `password=;Max-Age=0`,
            `nickname=;Max-Age=0`
          ],
          Location:'/'
        });
        response.end();
      });
    }
    else
    { 
      response.writeHead(404);
      response.end('Not Found');
    }
  
});
app.listen(3000);
//  app.listen(80); default web server port :80
// pm2 log
// pm2 start main
// pm2 stop main
// pm2 list
// pm2 start main.js --watch 
//XSS - Cross Site Scripting