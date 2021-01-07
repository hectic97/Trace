s = input()
lst = []
st = 0
for i,ch in enumerate(s):
    if not ch.isdigit():
        lst.append(int(s[st:i]))
        lst.append(ch)
        st = i+1
lst.append(int(s[st:]))

def cal(lst):
    result = 0
    if len(lst) ==1:
        print(lst[0])
        return
    st = 0
    cur = 0
    while cur < len(lst):
        while lst[cur] != '-':
            cur += 1
            if cur >= len(lst):
                break
        result += sum([lst[i] for i in range(st,cur,2)])

        if cur >= len(lst):
            print(result)
            return
        st = cur+1
        cur = st
        while True:
            while lst[cur] != '-':
                cur += 1
                if cur >= len(lst):
                    break
            result -= sum([lst[i] for i in range(st,cur,2)])
            if cur >= len(lst):
                print(result)
                return
            st = cur+1
            cur = st      
cal(lst)





