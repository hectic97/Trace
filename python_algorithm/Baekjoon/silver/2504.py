S = input()
S=S.replace('()','_2_')
S=S.replace('[]','_3_')
while S.find('__') > -1:
    i = S.find('__')
    for j in reversed(range(i)):
        if S[j] == '_':
            break
    for k in range(i+2,len(S)):
        if S[k] == '_':
            break
    S = S.replace(S[j:k+1],str(int(S[j+1:i])+int(S[i+2:k])))
print(S)
for i in range(len(S)):
    lst = []
    if S[i] == '(':
        lst.append('(')

def recur(S):
    st = S.find('(_')
    end = S.find('_)')
    if st > -1:
        num = int(S[st+1:end])
        S=S.replace(S[st:end+2],'_'+str(num)+'_')

recur(S)
print(S)