A = [3, 2, 1]  # Starting State of 3 rod
B = [0, 0, 0]
C = [0, 0, 0]
def ShowState():  # function that prints state
    print('A:',A)
    print('B:',B)
    print('C:', C, '\n')


def Sort():  # function that sorts the list
    A.sort()
    A.reverse()
    B.sort()
    B.reverse()
    C.sort()
    C.reverse()
def Hanoi(numOfDisk, start_rod , via_rod, target_rod):  # Recursion Function (move  disks from start_rod to target_rod)
    Hanoi.counter+=1                    # variable to count the fuction call
    if numOfDisk == 1:                  # recursion function exits condition
        i = 2                           # move the disk to the top of start_rod and move it to the top of target_rod
        while not start_rod[i]:
            i -= 1
        target_rod[-1] = start_rod[i]
        start_rod[i] = 0
        Sort()                          #Call Sort function to sort the element of list
        ShowState()                     #print the state after  moving



    else:
        Hanoi(numOfDisk-1,start_rod, target_rod,via_rod)   # To achieve the goal (move the floor disk of the start_rod,

        index = start_rod.index(numOfDisk)                 # have to move numOfDisk-1 disks from start_rod to via_rod
        target_rod[-1] = start_rod[index]
        start_rod[index] = 0
        Sort()
        ShowState()                                        # Move the floor disks of start_rod to target_rod


        Hanoi(numOfDisk-1,via_rod,start_rod,target_rod)   # Move the numOfDisk -1 disks from via_rod to target_rod



Hanoi.counter = 0 #variable that contains the number of moves

Hanoi(3, A, C, B) #Call recursion function : Hanoi (start_rod == A , via_rod = C , target_rod = B)

print("NUMBER OF MOVES:",Hanoi.counter) # print number of moves of the disks











