N = int(input())
pw = input()
def getCount(letter,degree):
    i = ord(letter) - ord('a')
    num = 0
    for x in range(degree):
        num += 26**x
    return num*i
result = 0

for i,letter in enumerate(pw):
    result += getCount(letter,N-i)
print(result+len(pw))