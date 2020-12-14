import sys
import socket
from threading import *
import pickle

serverIP = '10.0.0.3'
serverPort = 10080
clientPort = 10081

class Client:
    def __init__(self, serverIP, serverPort, clientPort):
        
        self.serverIP = serverIP
        self.serverPort = serverPort
        self.clientPort = clientPort

        self.init_ipconfig()
        self.skt = self.init_skt()
        
        self.init_client_dict()
        self.init_same_NAT()
        
        self.init_boolean_var()
        self.get_id()
        
        self.timeout = 10

    def init_skt(self):
        skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        skt.bind(('',self.clientPort))
        return skt

    def init_same_NAT(self):
        self.same_NAT = list()

    def init_boolean_var(self):
        self.alive = True
        self.receiving = False

    def init_ipconfig(self):
        # get local 
        self.ip = '127.0.0.1'
        try:
            # connect Broadcast IP
            temp_skt = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            temp_skt.connect(('10.255.255.255', 1))
            self.ip = temp_skt.getsockname()[0]
            temp_skt.close()
        except:
            pass
        # print('private',self.ip)

    def init_client_dict(self):
        self.client_dict = {}

    def get_id(self):
        self.client_id = input('Enter ID : ')

    def thread_time_check(self,timeout):
        thread_time_check = Timer(timeout, self.keep_alive)
        thread_time_check.start()  
        # EXIT OCCUR
        # STOP TIMIER
        if not self.alive:
            thread_time_check.cancel()
        
    def keep_alive(self):
        mode = 'K'
        data = mode+':'+str(self.client_id)
        encoded_data = data.encode()

        self.skt.sendto(encoded_data, (self.serverIP, self.serverPort))
        self.thread_time_check(self.timeout)


    def receive(self):
        while self.alive:
            received_data, _ = self.skt.recvfrom(1000)
            unpacked_received_data = pickle.loads(received_data)

            try:
                receive_mode,data = unpacked_received_data
            except:
                receive_mode = unpacked_received_data
            
            if receive_mode == 'E':
                # EXIT MODE
                
                print("Successfully Terminated")
                break


            elif receive_mode == 'C':
                # CHAT MODE
                
                send_id, send_content = data.split(":")
                # Receive chat data
                send_id = str(send_id)
                
                send_content = str(send_content)

                # print sender id and content
                print('From',send_id,'['+send_content+']')


            elif receive_mode == 'S':
                
                self.client_dict = data
                for id_, addr_ in self.client_dict.items():
                    print(str(id_) + "\t" + str(addr_[1])+":"+str(addr_[2]))
            elif receive_mode == 'U':
                self.client_dict = data
                # initialize same NAT list
                self.init_same_NAT()
                
                u_ip = self.client_dict[self.client_id][1]
                u_port = self.client_dict[self.client_id][2]
                for c_id, c_addr in self.client_dict.items():
                    
                    # check same ip and different port condition
                    if (u_ip == c_addr[1]) and (self.clientPort != c_addr[2]) and (self.clientPort != u_port):
                        # add same NAT client id to list
                            self.same_NAT.append(c_id)
            self.receiving = True

            
    def thread_receiving_start(self):
        # Start Threading receiving for multiprocessing
        thread_receiving = Thread(target=self.receive)
        thread_receiving.start()
    
    def register_client(self):
        # Register new client 
        mode = 'R'
        data = mode+':'+str(self.client_id)+':'+str(self.ip)
        encoded_data = data.encode()
        self.skt.sendto(encoded_data, (self.serverIP,self.serverPort))

    def send_chat(self,dt,d_ip,d_port):
        self.skt.sendto(dt,(d_ip,d_port))
        self.receiving=True

    def command_process(self,command,chat_id=None,chat_content=None):
        if command == "@chat":
            SAME_NAT = True if chat_id in self.same_NAT else False
            mode = 'C'
            packed_dt = pickle.dumps([mode,str(self.client_id)+':'+str(chat_content)])
            if SAME_NAT:
                dest_ip = self.client_dict[chat_id][0]
                dest_port = self.clientPort
            else:
                dest_ip = self.client_dict[chat_id][1]
                dest_port = self.client_dict[chat_id][2]
            self.send_chat(packed_dt,dest_ip,dest_port)

        elif command == "@show_list":
            for client_id, client_addr in self.client_dict.items():
                client_id = str(client_id)
                client_ip = str(client_addr[1])
                client_port = str(client_addr[2])
                printout_client_info = client_ip+':'+client_port
                print(client_id+"\t"+printout_client_info)

        elif command == "@exit":
            mode = 'E'
            
            send_dt = mode+':'+str(self.client_id)
            encoded_send_dt = send_dt.encode()
            self.alive = False
            
            self.skt.sendto(encoded_send_dt, (self.serverIP, self.serverPort))
            c_send_dt = [mode,self.client_id]
            packed_c_dt = pickle.dumps(c_send_dt)
            self.skt.sendto(packed_c_dt, (self.ip, self.clientPort))
            return True
        return False

    def handle_command(self):
        command = input()
        # Set maxsplit for chatting message space
        command = command.split(" ", maxsplit=2)
        if command[0] == '@chat':
            exit_condition = self.command_process(command=command[0],chat_id=command[1],chat_content=command[2])
        else:
            exit_condition = self.command_process(command=command[0])
        return exit_condition


    def start_receive(self):

        self.keep_alive()
        self.thread_receiving_start()
        self.register_client()

        while True:
            if self.receiving:
                if self.handle_command():
                    break

"""
Don't touch the code below
"""

if __name__ == '__main__':
    client = Client(serverIP,serverPort,clientPort)
    client.start_receive()
