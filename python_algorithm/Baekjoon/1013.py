N = int(input())
def case_1(signal):
    if len(signal) < 4 :
        return False
    if signal[:3] != '100':
        return False
    for ind in range(3,len(signal)-1):
        if signal[ind] == '1' and signal[ind+1] == '0':
            return ind
    if signal[-1] == '1':
        return len(signal)-1
    return False
def case_2(signal):
    if len(signal) < 2 :
        return False
    if signal[0] == '0' and signal[1] == '1':
        return True
    return False

for _ in range(N):
    signal = input()
    while(signal)
        if case_2(signal):
            signal = signal[2:]
        elif case_1(signal):
            signal = signal[case_1(signal)+1:]
        else:


        
