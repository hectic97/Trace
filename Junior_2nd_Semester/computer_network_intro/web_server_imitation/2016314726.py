from socket import *
import os
import datetime
import time 

PORT = 10080
last_str=b'\r\n\r\n'
authorized = 0
login_time = 0
user_id = ''
def main():
    run_server(PORT)

def run_server(PORT):
    serverSocket = socket(AF_INET, SOCK_STREAM)
    serverSocket.bind(('',PORT))
    serverSocket.listen(10)
    print('THE TCP SERVER IS READY TO RECEIVE!')
    while True:
        clientSocket, addr = serverSocket.accept()
        x = serverSocket.getsockopt(SOL_SOCKET,SO_KEEPALIVE)
        clientSocket.setsockopt(SOL_SOCKET,SO_KEEPALIVE,1)
        clientSocket.setsockopt(IPPROTO_TCP,TCP_KEEPIDLE,1440) #연결 활성화 상태유지 (default 14400=2h)
        clientSocket.setsockopt(IPPROTO_TCP,TCP_KEEPINTVL,100) # 연결 유효성 검사 주기
        clientSocket.setsockopt(IPPROTO_TCP,TCP_KEEPCNT,10) # 연결 종료전 유효성 검사 횟수
        handle_clientRequest(clientSocket)    

def handle_clientRequest(clientSocket):
    global authorized
    global login_time
    global user_id
    client_http = ''
    client_http = clientSocket.recv(4096)
    print(client_http)
    if b'Cookie: id=' in client_http:
        authorized = 1
    else:
        authorized = 0
    if client_http:
        http_list, headers = client_http.decode().split('\r\n', 1)
        http_list = http_list.split(' ',3)
        headers = headers.split('\r\n')
        if headers[-1] != '' and http_list[1] == '/login':  # IF LOGIN
            user_id = headers[-1][headers[-1].index('=')+1:headers[-1].index('&')]
            print('LOGIN')
            authorized = 1
            out = b'HTTP/1.1 302 OK\r\n'
            out += b"Connection: close\r\n"
            if user_id:
                out += "Set-Cookie: id={}; Max-Age=30\r\n".format(user_id).encode()
            out += b"Location: /secret.html\r\n\r\n"
            login_time = time.time()
            clientSocket.sendall(out)

        if not authorized:  # IF NOT LOGGED_IN
            if http_list[1] == '/': # IF TRY LOGIN
                index_size = os.path.getsize('index.html')
                out = b'HTTP/1.1 200 OK\r\n'
                out += b"Content-Length: "+str(index_size).encode()+b'\r\n'
                out += b"Content-Type: text/html\r\n"
                out += b"Connection: close\r\n\r\n"
                i_html = open('index.html','r+b')
                i_b = b""
                for _ in range(index_size):
                    i_b += i_html.read()
                out += i_b
                clientSocket.sendall(out)
                # clientSocket.close()

            else:   # IF NOT AUTHORIZED ACCESS
                clientSocket.sendall(b"HTTP/1.1 403 Forbiden\r\n\r\n")
                clientSocket.close()
        elif http_list[1] == '/image.png' or http_list[1] == '/image2.png' or http_list[1] == '/image3.png':
            # LOG IN AND STATIC FILES
            img_size = os.path.getsize(http_list[1][1:])
            out = b'HTTP/1.1 200 OK\r\n'
            out += b"Content-Length: "+str(img_size).encode()+b'\r\n'
            out += b"Content-Type: image/png\r\n"
            out += b"Connection: close\r\n\r\n"
            img = open(http_list[1][1:],'r+b')
            img_b = b""
            for _ in range(img_size):
                img_b += img.read()    
            out += img_b
            clientSocket.sendall(out)
            clientSocket.close()
        elif http_list[1] == '/':
            out = b'HTTP/1.1 302 OK\r\n'
            out += b"Connection: close\r\n"
            out += b"Location: /secret.html\r\n\r\n"
            clientSocket.sendall(out)
        elif http_list[1] == '/secret.html':
            secret_size = os.path.getsize('secret.html')
            out = b'HTTP/1.1 200 OK\r\n'
            out += b"Content-Length: "+str(secret_size).encode()+b'\r\n'
            out += b"Content-Type: text/html\r\n"
            out += b"Connection: close\r\n\r\n"
            i_html = open('secret.html','r+b')
            i_b = b""
            for _ in range(secret_size):
                i_b += i_html.read()
            out += i_b
            clientSocket.sendall(out)
            clientSocket.close()
            
        elif http_list[1] == '/cookie.html':
            content = make_cookie_html(user_id)
            content_size = len(content)
            out = 'HTTP/1.1 200 OK\r\n'
            out += "Content-Type: text/html\r\n"
            out += "Content-size: {}\r\n".format(content_size)
            out += "Connection: close\r\n\r\n"
            out += content
            clientSocket.sendall(out.encode())
            clientSocket.close()
        else: # LOGIN BUT ACCESS WRONG PATH
            clientSocket.sendall(b"HTTP/1.1 404 Not Found\r\n\r\n")
            clientSocket.close()
        
def make_cookie_html(id):
    global authorized
    return """<!DOCTYPE html>
    <html><head><title>Welcome {0}</title></head><body><br>Hello {0}<br><br>
    {1} seconds left until your cookie expires</body></html>""".format(id,max(0,int(30 - (time.time() - login_time))))



if __name__ == "__main__":
    main()    
