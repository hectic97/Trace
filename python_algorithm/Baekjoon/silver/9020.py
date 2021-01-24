N = int(input())
lst = [int(input()) for _ in range(N)]

def get_prime():
    prime_list = [1]*(10000+1)
    # prime_list[2] = 0
    # prime_list[3] = 0

    for i in range(2,int(10001**0.5)):
        if prime_list[i]:
            # prime_list[i] = 0
            for j in range(i+i,10001,i):
                prime_list[j] = 0
    return prime_list

prime_list = get_prime()

for x in lst:
    for i in range(int(x/2),1,-1):
        if prime_list[i] and prime_list[x-i]:
            print(min(i,x-i),max(i,x-i))
            break

