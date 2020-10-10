def Contact(index, state, N):
    if(state == -1):
        print("NO")
        return

    if(index == len(N) and (state == 5 or state == 6 or state == 7)):
        print("YES")
        return

    if(index == len(N)):
        print("NO")
        return

    if state == 0:
        if(N[index] == '0'):
            Contact(index + 1, 1, N)
        else:
            Contact(index + 1, 2, N)
    elif state == 1:
        if (N[index] == '0'):
            Contact(index + 1, -1, N)
        else:
            Contact(index + 1, 5, N)
    elif state == 2:
        if (N[index] == '0'):
            Contact(index + 1, 3, N)
        else:
            Contact(index + 1, -1, N)
    elif state == 3:
        if (N[index] == '0'):
            Contact(index + 1, 4, N)
        else:
            Contact(index + 1, -1, N)
    elif state == 4:
        if (N[index] == '0'):
            Contact(index + 1, 4, N)
        else:
            Contact(index + 1, 6, N)
    elif state == 5:
        if (N[index] == '0'):
            Contact(index + 1, 1, N)
        else:
            Contact(index + 1, 2, N)
    elif state == 6:
        if (N[index] == '0'):
            Contact(index + 1, 1, N)
        else:
            Contact(index + 1, 7, N)
    elif state == 7:
        if (N[index] == '0'):
            Contact(index + 1, 8, N)
        else:
            Contact(index + 1, 7, N)

    elif state == 8:
        if (N[index] == '0'):
            Contact(index + 1, 4, N)
        else:
            Contact(index + 1, 0, N)

def solution():
    N = str(input())
    Contact(0, 0, N)

T = int(input())

for i in range(T):
    solution()