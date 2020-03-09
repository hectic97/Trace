import random  # to make computer decide ramdomly

def WhoIsWinner(state):   # function that judge the state that game has ended

    if (state[0][0] == state[1][1] == state[2][2] or
    state[2][0] == state[1][1] == state[0][2]) and state[1][1] == 'O': # if diagonal bingo occurs by player

        return 2               # return 2   means player's win
    elif (state[0][0] == state[1][1] == state[2][2] or
        state[2][0] == state[1][1] == state[0][2]) and state[1][1] == 'X': # if diagonal bingo occurs by computer

        return 1                # return 1  means player's defeat

    for i in range(3):
        if ('').join(state[i]) == 'OOO' or ('').join([x[i] for x in state]) == 'OOO':
            # 'O' appears 3 times in a row at row of state   OR  'O' appears 3 times in a row at column of state
            return 2
        elif ('').join(state[i]) == 'XXX' or ('').join([x[i] for x in state]) == 'XXX':
            # 'X' appears 3 times in a row at row of state   OR  'X' appears 3 times in a row at column of state
            return 1

    return 0 # return 0 (False) means game is not over yet


def ShowState(state):  #function to show mid-state
    for i in range(3):
        print(state[i])


count = 0    # if 3x3 Tic-Tac-Toe field is fully occupied by player and computer
state=[]     # Initialize state
for _ in range(3):
    state.append([' ', ' ', ' ']) # Initialize state to (3,3)  shape list

while not WhoIsWinner(state): # If game is not over
    count += 2      # a loop contain two turns

    print('Computer\'s Turn')
    while True:
        i = random.randrange(0, 3) # i is random integer 0 or 1 or 2
        j = random.randrange(0, 3) # j is random integer 0 or 1 or 2
        if state[i][j] == ' ':     # if state[i][j] is blank break or pick another numbers
            break
    state[i][j] = 'X'   # computer's marker is 'X'
    ShowState(state)    # Show mid-state
    if WhoIsWinner(state):  # Check the game is over
        break               # if  return 1 or 2 that means the game is over, break the loop
    if count == 10:     # count == 10 means that Tic Tac Toe board is full when computer's turn ends
        print('tie')    # so print 'tie'
        exit()          # end the program
    while True:

        player_input = input('Your Turn\n')
        try:
            player_input = tuple(map(int, [player_input[1], player_input[3]])) # Input's shape should be like a tuple!!
            if state[player_input[0]][player_input[1]] == ' ':  # if inputted tuple's position of state == blank  break
                break
        except (IndexError, ValueError):                        # If input is not a tuple shape 2,3(x)  2 3(x) (2,3)(O)
            print('Please input tuple | ex) (2,3)')             # print error message and input again
            continue

        print('Invalid input (occupied)')                       # else print error message and input again
    state[player_input[0]][player_input[1]] = 'O'               # player's marker is 'O'
    ShowState(state)                                            # Show mid-state

if WhoIsWinner(state) == 2:  # return 2 means that player's win
    print('win')       # print win
else:
    print('lose')       # if computer win


