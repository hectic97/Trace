import random  # to make computer decide ramdomly


def WhoIsFirst():   # function that decides who is first

    if random.randrange(0, 2) == 1:    # 0 or 1 is the result
        return 'computer', 'player'
    else:
        return 'player', 'computer'


def WhoIsWinner(state):   # function that judge the state that game has ended

    if (state[0][0] == state[1][1] == state[2][2] or
    state[2][0] == state[1][1] == state[0][2]) and state[1][1] == markers['player']: # if diagonal bingo occurs by player

        return 2               # return 2   means player's win
    elif (state[0][0] == state[1][1] == state[2][2] or
        state[2][0] == state[1][1] == state[0][2]) and state[1][1] == markers['computer']: # if diagonal bingo occurs by computer

        return 1                # return 1  means player's defeat

    for i in range(3):
        if ('').join(state[i]) == markers['player']*3 or ('').join([x[i] for x in state]) == markers['player']*3:
            # 'O' appears 3 times in a row at row of state   OR  'O' appears 3 times in a row at column of state
            return 2
        elif ('').join(state[i]) == markers['computer']*3 or ('').join([x[i] for x in state]) == markers['computer']*3:
            # 'X' appears 3 times in a row at row of state   OR  'X' appears 3 times in a row at column of state
            return 1

    return 0 # return 0 (False) means game is not over yet


def ShowState(state):  #function to show mid-state
    for i in range(3):
        print(state[i])


count = 0    # if 3x3 Tic-Tac-Toe field is fully occupied by player and computer
state = []     # Initialize state
for _ in range(3):
    state.append([' ', ' ', ' ']) # Initialize state to (3,3)  shape list

player_order = WhoIsFirst()  # Decide who is first player
markers = {player: marker for player, marker in zip(player_order, ['X', 'O'])} # first player gets 'X' marker
ShowState(state)
while count < 9:  # If game is not over

    if player_order[count % 2] == 'computer':
        print('Computer\'s Turn')
        while True:
            i = random.randrange(0, 3)  # i is random integer 0 or 1 or 2
            j = random.randrange(0, 3)  # j is random integer 0 or 1 or 2
            if state[i][j] == ' ':  # if state[i][j] is blank break or pick another numbers
                break
        state[i][j] = markers['computer']  # computer's marker is markers['computer']
        ShowState(state)  # Show mid-state
        if WhoIsWinner(state):  # Check winner has decided
            break  # if  return 1 or 2 (True) that means the game is over, break the loop
    else:
        while True:

            player_input = input('Your Turn\n')
            try:
                player_input = tuple(
                    map(int, [player_input[1], player_input[3]]))  # Input's shape should be like a tuple!!
                if state[player_input[0]][
                    player_input[1]] == ' ':  # if inputted tuple's position of state == blank  break
                    break
            except (IndexError, ValueError):  # If input is not a tuple shape 2,3(x)  2 3(x)  (2,3)(O)
                print('Please input tuple | ex) (2,3)')  # print error message and input again
                continue

            print('Invalid input (occupied)')  # else print error message and input again
        state[player_input[0]][player_input[1]] = markers['player']  # player's marker is markers['player']
        ShowState(state)
        if WhoIsWinner(state):  # Check the game is over
            break  # if  return 1 or 2 that means the game is over, break the loop

    count += 1


if WhoIsWinner(state) == 2:  # return 2 means that player's win
    print('win')       # print win
elif WhoIsWinner(state) == 1:
    print('lose')       # if computer win
else:
    print('tie')        # winner has not decided and 9 turn has passed

