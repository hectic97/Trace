import sys
class VirtualMemoryManagement():
    def __init__(self,memory_info_file,log_file):
        self.file = open(memory_info_file,'r')
        self.N, self.M, self.W, self.K = list(map(int,self.file.readline().split()))
        self.ref = [0]+list(map(int,self.file.readline().split()))
        self.log_path = log_file
        self.log = open(log_file,'w')
        self.page_load_time= dict()
        self.pointer = 0


    def check_argv(self):
        print('N: ',self.N)
        print('M: ',self.M)
        print('W: ',self.W)
        print('K: ',self.K)
        print('ref: ',self.ref)
    
    def operate(self,algorithm):
        time = 1
        total_pf = 0
        self.memory_state = [-1]*self.M
        if algorithm == 'Clock':
            self.log.write('|{:^8}|{:^5}|{:^16}| {}\n'.format('Time','P.f','Pclock  Qclock','Memory state  [page, reference bit]'))
            self.memory_state = [[p,1] for p in range(self.M)]
        elif algorithm == 'WS':
            self.log.write('|{:^8}|{:^5}|{:^6}|{:^6}|{:^17}|{}\n'.format('Time','P.f','P.ws','Q.ws','Num.alloc.frame','Memory state'))
            self.memory_state = [[p,-1] for p in range(self.N)]
        else:
            self.log.write('|{:^8}|{:^5}|{:^8}| {}\n'.format('Time','P.f','Victim','Memory state'))
        while time <= self.K:
            victim, page_fault = self.replace_process(algorithm,time)
            if page_fault:
                total_pf += 1
            self.write_log(time,page_fault,victim,algorithm)
            time += 1
        self.log.close()
        with open(self.log_path,'r') as f:
            entire_log = f.read()
        with open(self.log_path,'w') as f:
            f.write('Total Page Fault: {:<6}\n\n{}'.format(total_pf,entire_log))


    def replace_process(self,algorithm,time):
        page_fault = False
        victim = ''
        if algorithm == 'MIN':
            if self.ref[time] not in self.memory_state:
                try:
                    self.memory_state[self.memory_state.index(-1)] = self.ref[time]
                    page_fault = True
                except:
                    ref_period = [0]*self.M
                    for i,page in enumerate(self.memory_state):
                        if page in self.ref[time:]:
                            ref_period[i] = self.ref[time:].index(page)
                        else:
                            ref_period[i] = 1000000
                    mx = -1
                    mx_page = -1
                    for j,period in enumerate(ref_period):
                        if period > mx:
                            mx = period
                            mx_page = self.memory_state[j]
                        elif period == mx:
                            mx_page = self.memory_state[j] if self.memory_state[j] < mx_page else mx_page
                    victim = mx_page
                    self.memory_state[self.memory_state.index(mx_page)] = self.ref[time]
                    page_fault = True
        elif algorithm == 'FIFO':       
            if self.ref[time] not in self.memory_state:
                self.page_load_time[self.ref[time]] = time
                try:
                    self.memory_state[self.memory_state.index(-1)] = self.ref[time]                    
                    page_fault = True
                except:
                    loaded_page_dict = {k:v for k,v in self.page_load_time.items() if k in self.memory_state}
                    replace_page = min(loaded_page_dict.items(),key= lambda x: x[1])[0]
                    victim = replace_page
                    self.memory_state[self.memory_state.index(replace_page)] = self.ref[time]
                    page_fault = True
            
        
        elif algorithm == 'LRU':
            if self.ref[time] not in self.memory_state:
                try:
                    self.memory_state[self.memory_state.index(-1)] = self.ref[time]                    
                    page_fault = True
                except:
                    ref_period = [0]*self.M
                    reversed_past_ref = self.ref[:time].copy()
                    reversed_past_ref.reverse()
                    for i,page in enumerate(self.memory_state):    
                        ref_period[i] = reversed_past_ref.index(page)
                    mx = -1
                    mx_page = -1
                    for j,period in enumerate(ref_period):
                        if period > mx:
                            mx = period
                            mx_page = self.memory_state[j]
                    victim = mx_page
                    self.memory_state[self.memory_state.index(mx_page)] = self.ref[time]
                    page_fault = True
        
        elif algorithm == 'LFU':
            if self.ref[time] not in self.memory_state:
                try:
                    self.memory_state[self.memory_state.index(-1)] = self.ref[time]                    
                    page_fault = True
                except:
                    min_ref = 1000000
                    min_ref_page = -1
                    for page in self.memory_state:
                        if min_ref > self.ref[:time].count(page):
                            min_ref = self.ref[:time].count(page)
                            min_ref_page = page
                        elif min_ref == self.ref[:time].count(page):
                            if self.ref[:time][::-1].index(page) > self.ref[:time][::-1].index(min_ref_page):
                                min_ref_page = page


                    victim = min_ref_page
                    self.memory_state[self.memory_state.index(min_ref_page)] = self.ref[time]
                    page_fault = True
        
        elif algorithm == 'Clock':
            if self.ref[time] not in [x[0] for x in self.memory_state]:
                while True:
                    if self.pointer == self.M:
                        self.pointer = 0
                    if self.memory_state[self.pointer][1] == 0:
                        victim = [self.ref[time],self.memory_state[self.pointer][0]]
                        self.memory_state[self.pointer] = [self.ref[time],1]
                        page_fault = True
                        self.pointer += 1
                        break
                    else:
                        self.memory_state[self.pointer][1] = 0
                        self.pointer += 1 
            else:
                self.memory_state[[x[0] for x in self.memory_state].index(self.ref[time])][1] = 1  

                        
        elif algorithm == 'WS':
            victim = ['']*2
            for i,m in enumerate(self.memory_state):
                if m[1] >= 0:
                    self.memory_state[i][1] += 1

            for i,mem in enumerate(self.memory_state):
                if (mem[1] == self.W+1) and (mem[0] != self.ref[time]):
                    mem[1] = -1
                    victim[1] = mem[0]


            if self.memory_state[[x[0] for x in self.memory_state].index(self.ref[time])][1] == -1:
                page_fault = True
                self.memory_state[[x[0] for x in self.memory_state].index(self.ref[time])][1] = 0
                victim[0] = self.ref[time]
            else:
                self.memory_state[[x[0] for x in self.memory_state].index(self.ref[time])][1] = 0
            
            
            


        return victim, page_fault


    def write_log(self,time,page_fault,victim,algorithm):
        memory = self.memory_state.copy()
        while -1 in memory:
            memory.remove(-1)
        if page_fault:
            pf = 'F'
        else:
            pf = ' '
        if algorithm == 'Clock':
            self.log.write('|{:^8}|{:^5}|{:^16}| {}\n'.format(time,pf,(' '*7).join(list(map(str,victim)))+'',' '.join(list(map(str,memory)))))
        elif algorithm == 'WS':
            num_alloc = self.N
            memory = [x[:] for x in self.memory_state]
            for i,page in enumerate(memory):
                if page[1] < 0:
                    memory[i][0] = ' '
                    num_alloc -= 1
            
            self.log.write('|{:^8}|{:^5}|{:^6}|{:^6}|{:^17}| {}\n'.format(time,pf,victim[0],victim[1],num_alloc,' '.join(list(map(str,[m[0] for m in memory])))))
        else:
            self.log.write('|{:^8}|{:^5}|{:^8}| {}\n'.format(time,pf,victim,' '.join(list(map(str,memory)))))


            
        
        

def main():
    vmm = VirtualMemoryManagement('input.txt','log.txt')
    vmm.check_argv()
    vmm.operate(sys.argv[1])



if __name__ == "__main__":
    main()