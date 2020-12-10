import sys
import socket
from threading import *
from time import sleep
import time
import pickle

serverPort = 10080

class Server:
    def __init__(self, serverPort):
        self.serverPort = serverPort
        self.skt = self.init_skt()
        self.init_client_dict()
        self.init_time_dict()
    def init_skt(self):
        skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        skt.bind(('',self.serverPort))
        return skt

    def init_client_dict(self):
        self.client_dict = {} 
    
    def init_time_dict(self):
        self.time_dict = {}

    def detect_disconnect(self):
        detect_thread = Thread(target=self.disconnect_state, args=())
        detect_thread.start()

    def disconnect_state(self,timeout=30):
        disconnect_occur = False
        while not disconnect_occur:
            try:
                disconnect_occur=self.timeout_check(timeout,disconnect_occur)
            except:
                pass


    def timeout_check(self,timeout,disconnect_occur):
        for client_id, client_time in self.time_dict.items():
            cur_time = time.time()
            if (cur_time - client_time) > timeout:
                disconnect_occur = True
                # remove timeout client
                removed_id = client_id
                removed_client_addr = str(self.client_dict[removed_id][1])+':'+\
                    str(self.client_dict[removed_id][2])
                removed_id = str(removed_id)
                self.time_dict.pop(client_id)
                self.client_dict.pop(client_id)
                
                print(removed_id,"is disappeared"+'\t'+removed_client_addr)
                mode = 'U'
                for _, u_client_addr in self.client_dict.items():
                    packed_dt = pickle.dumps([mode,self.client_dict])
                    ip = u_client_addr[1]
                    port = u_client_addr[2]
                    self.skt.sendto(packed_dt,(ip,port))
        return disconnect_occur

    def start_receive(self):
        # start detecting disconeect client
        self.detect_disconnect()

        while True:
            # receive data from client
            data, client_addr = self.skt.recvfrom(500)
            parsed_receive_data = self.received_data_parsing(data)
            if len(parsed_receive_data) == 2:
                mode,client_id = parsed_receive_data
                self.handle_received_data(receive_mode=mode, client_id=client_id, client_addr=client_addr)
            else:
                mode,client_id,client_ip = parsed_receive_data
                self.handle_received_data(receive_mode=mode, client_id=client_id, client_addr=client_addr,client_ip=client_ip)
                



    def received_data_parsing(self,data):
        dt = data.decode()
        dt = str(dt).split(':')
        return dt

    def handle_received_data(self,receive_mode,client_id,client_addr,client_ip=None):
        if receive_mode == 'E': # client send EXIT
            receive_ip = str(self.client_dict[client_id][1])
            receive_port = str(self.client_dict[client_id][2])
            self.client_dict.pop(client_id)
            self.time_dict.pop(client_id)
            
            receive_addr = receive_ip+':'+receive_port
            print(str(client_id),'is deregistered'+'\t'+receive_addr)
            send_mode = 'U'
            for _, u_client_addr in self.client_dict.items():
                packed_dt = pickle.dumps([send_mode,self.client_dict])
                ip = u_client_addr[1]
                port = u_client_addr[2]
                self.skt.sendto(packed_dt,(ip,port))

        elif receive_mode == 'R': # client send REGISTER
            receive_ip = str(client_addr[0])
            receive_port = str(client_addr[1])
            recieve_addr = receive_ip+':'+receive_port
            
            print(str(client_id)+'\t'+recieve_addr)
            self.client_dict[client_id] = [client_ip, client_addr[0], client_addr[1]]

            send_mode = 'U'
            for _, u_client_addr in self.client_dict.items():
    
                packed_dt = pickle.dumps([send_mode,self.client_dict])
                ip = u_client_addr[1]
                port = u_client_addr[2]
                self.skt.sendto(packed_dt,(ip,port))

            send_mode = 'S' # SHOW_REGISTERED_CLIENT_LIST
            packed_dt = pickle.dumps([send_mode,self.client_dict])
            s_client_ip = client_addr[0]
            s_client_port = client_addr[1]
            self.skt.sendto(packed_dt, (s_client_ip,s_client_port))
        
        elif receive_mode == 'S': # SHOW_REGISTERED_CLIENT_LIST
            
            send_mode = 'S' # SHOW_REGISTERED_CLIENT_LIST
            packed_dt = pickle.dumps([send_mode,self.client_dict])
            s_client_ip = client_addr[0]
            s_client_port = client_addr[1]
            self.skt.sendto(packed_dt, (s_client_ip,s_client_port))
        
        elif receive_mode == 'K': # KEEP_ALIVE_CLIENT
            cur_time= time.time()
            self.time_dict[client_id] = cur_time
        






"""
Don't touch the code below
"""
if  __name__ == '__main__':
    server = Server(serverPort=serverPort)
    server.start_receive()



