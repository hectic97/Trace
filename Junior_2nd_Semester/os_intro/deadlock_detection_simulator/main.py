p = open('input.txt')
p = p.read()

p=p.split('\n')
head=p.pop(0)
alloc=p[:int(head[0])]
alloc=[list(map(int,f.split())) for f in alloc]
req = p[int(head[0]):]
req=[list(map(int,f.split())) for f in req]
n_ps = int(head[0])
n_rtypes = int(head[2])
n_runits = list(map(int,head[4:].split()))
print('# of ps:',n_ps)
print('# of R types:',n_rtypes)
print('# of R units:',n_runits)
print('Allocation matrix:',alloc)
print('Require matrix:',req)

def check_unblock(n_runits, alloc, req,unblock_state):
    unblock = unblock_state.copy()
    empty_runits = n_runits.copy()
    for al in alloc:
        for i,a in enumerate(al):
            empty_runits[i] -= a
    for j,re in enumerate(req):
        check = True
        for i,r in enumerate(re):
            if empty_runits[i] < r:
                check = False
        if check:
            if unblock[j] != -1:
                unblock[j] = 1
        
    return empty_runits,unblock

def graph_reduction(n_runits,alloc,req,unblock):
    for i,state in enumerate(unblock):
        if state == 1:
            alloc[i] = [0]*len(n_runits)
            req[i] = [0]*len(n_runits)
            unblock[i] = -1 # Release
            return (alloc,req,unblock)
    return (False,False,unblock)

state = [0]*len(alloc)
while True:
    empty,unblock=check_unblock(n_runits,alloc,req,state)
    alloc,req,state = graph_reduction(n_runits,alloc,req,unblock)
    if not alloc:
        print('DEADLOCK',state)
        deadlock_process = []
        for i,state in enumerate(state):
            if state==0:
                deadlock_process.append('P'+str(i+1))
        print('DEADLOCKED process list:',deadlock_process)
        break
    if all([x==-1 for x in state]):
        print('No Deadlocked process')
        break
    
        
    