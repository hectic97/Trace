var http = require('http');
var cookie = require('cookie');

http.createServer(function(request,response){
    var cookies = {};
    if (request.headers.cookie){
        cookies=cookie.parse(request.headers.cookie);    
    }
    response.writeHead(200,{
        'Set-Cookie':['aa_cookie=apple','bb_cookie=banana',
    `Permanent=per_cookie;Max-Age=${60*60}`,
    'Secure_cookie=sec_cookie; Secure;',
    'HTTP_only=http_only_cookie; HttpOnly', // Secure: https , HttpOnly: Can't access using console
    'Path=path_cookie; Path=/cookie',   // Set valid cookie address (only in path, only in domain)
    'Domain=dom_cookie; Domain=o2.org']

    });
    response.end('Cookie!!');
}).listen(3000); 