
# required method to print the board.
def print_board(board):
    # first you must reverse the list so that the tokens act like they're falling down the board, even though
    # in reality we're adding the player's input to the next available space in the column they chose starting from
    # the top and going down.
    board.reverse()
    # this for loop allows the program to print every element of the list. starting with each row (or each main
    # item in the list)...
    for row in range(len(board)):
        # ... then working into each column in each row (the nested list inside each main lists' elements)
        for column in range(len(board[row])):
            # if there are still more columns to print, then there will not be a newline after the item has been
            # printed.
            if (column + 1) < len(board[row]):
                print(f'{board[row][column]}', end='')
            # if there are no more columns to print, then there will be a new line so that the pattern creates
            # a board.
            else:
                print(f'{board[row][column]}')
    # then flip the board back around so that we can continue adding tokens as normal.
    board.reverse()
    print()


# required method to initialize the board, or the list that contains the '-' character.
def initialize_board(num_rows, num_cols):

    # list comprehension statement to create a list that inputs the proper amount of rows depending on the
    # number specified by the user, and the proper amount of columns per row that was also specified by the user.
    board_list = [['-' for col in range(num_cols)] for row in range(num_rows)]
    # return the list so that it can be used in the main function.
    return board_list


# required method used for inserting tokens into the list.
def insert_chip(board, col, chip_type):

    # for each row on the board...
    for row in range(len(board)):
        # ... this loop checks if the space at the column specified by the user is a free space. If it is...
        if board[row][col] == '-':
            # ... then the token (x or o depending on which player's turn it is) will be inserted into that free space.
            board[row][col] = f'{chip_type}'
            break
        # if the space is anything other than '-', the loop continues until it finds a row that has a free space.
        else:
            continue

    # once the addition has been made, the changed board will be printed to show where the player's token landed.
    print_board(board)
    # return the board so that it can continue to be used throughout the main function.
    return board


# method to find the row in which the player has inserted a token. the reason I felt this was necessary is I
# couldn't return both the board and the row in which the token was inserted from the insert_chip method, so I
# wrote another method that would return the row.
def find_row(board, col, chip_type):

    # this loop will read through every row at the specified (by the user) column.
    for r in range(len(board)):
        # if the space is occupied, then the loop will continue.
        if board[r][col] == chip_type:
            continue
        elif board[r][col] != '-':
            continue
        # if the space is not occupied, that means that the current iteration is reading the row right above the
        # entry, so then the loop will return the row of the current iteration - 1,
        # because that is where the chip is (one row below)
        else:
            return r - 1

    # if the for loop iterates completely (meaning that every row of a column is occupied, then we must
    # return the amount of rows in the board -1 (to account for indexing) because the row the chip is in is the
    # top row
    return len(board) - 1


# required method to check if the last move awarded the player the win.
def check_if_winner(board, col, row, chip_type):

    # initialize variables. in_a_row counts how many pieces of the same chip type are adjacent. current_token
    # indicates what the current token is. not_current_token will track how many spaces in a row or column
    # are not the current token, and win is initialized to false.
    in_a_row = 0
    current_token = board[row][col]
    not_current_token = 0
    win = False

    # this loop will read every row of a given column of the board.
    for r in range(len(board)):
        # if the current iteration is on a row that has the same chip type as the current chip...
        if board[r][col] == current_token:
            # ... then there is one additional chip of that type "in a row"
            in_a_row += 1
            # if there are four in a row...
            if in_a_row == 4:
                # the player has won and the loop will exit.
                win = True
                break
        # if the current iteration is on a row that does NOT have the same chip type as the current
        # chip, then there is one more chip in the row that is not the current chip, or there's just an
        # unoccupied space, which is still not the current chip. the in_a_row variable must also be reinitialized
        # because if the token being read is not the same as the current, then we have to make sure that the
        # loop knows that even if there are other tokens in the column of the same type, that they're no longer
        # adjacent or "in a row".
        else:
            not_current_token += 1
            in_a_row = 0

        # if we've reached a point where there are too many spaces in the column that are not the same as the current
        # token for there to be 4 tokens of the same kind in a row , then this if statement
        # will make sure that the win variable remains false and will break the loop, since there's no point in
        # reading the rest. it also re-initializes not_current_token, so that the next part of this method gets
        # a new count.
        if not_current_token > (len(board) - 4):
            win = False
            not_current_token = 0
            break
        # if there is still a possibility to have 4 of the same tokens in a row, the loop will continue.
        else:
            continue

    # this is the next part of the method that will only execute if win is still False.
    if not win:
        # this loop will read through all the columns of the given (by find_row) row. this loop mostly
        # follows the same logic as the previous loop, except is reads from left to right and not from top to bottom
        for c in range(len(board[row])):
            # if the current iteration is reading a column that has the same chip type as the current token
            # (which is still the same from the beginning of the method)...
            if board[row][c] == current_token:
                # ... then there's an additional token in a row.
                in_a_row += 1
                # if there are 4 of the same token in a row, the player has won and the loop will break.
                if in_a_row == 4:
                    win = True
                    break
            # otherwise, it is recorded as a space that is not the same as the current token, and we have
            # to make sure that in_a_row stays or if reinitialized to 0.
            else:
                not_current_token += 1
                in_a_row = 0

            # if there are too many spaces that are not the current token for it to be possible to get 4 in a row,
            # then win stays as false and the loop breaks since there is no point in continuing to read.
            if not_current_token > (len(board[row]) - 4):
                win = False
                break
            # if it is still possible to get 4 in a row, the loop continues.
            else:
                continue

    # if a player has gotten 4 in a row and win has been changed to True...
    if win:
        # ... then we figure out which player has won.
        # if the chip type is x then player 1 has won.
        if chip_type == 'x':
            print('Player 1 won the game!')
            # win is returned so that the loop in the main function will no longer iterate because the
            # condition is no longer false.
            return win
        # but if the chip is o then player 2 has won.
        elif chip_type == 'o':
            print('Player 2 won the game!')
            return win
    # if win is still False, then we return win anyway so that we can make sure the variable that is assigned
    # to the result of this function isn't assigned with None.
    else:
        return win


# method to check if there is a draw
def check_draw(board):

    # initialize variables. free_space will keep track of the free space on the board.
    free_space = 0

    # this loop will read every single item in the list
    for row in range(len(board)):
        for column in range(len(board[row])):
            # if an item is a free space (as in a token hasn't been put there yet)...
            if board[row][column] == '-':
                # ... then free_space is incremented by 1
                free_space += 1
            # if the space is occupied, however, than the loop can continue.
            else:
                continue

    # if there were no free spaces in the entire list, then the whole board has been filled with tokens
    # and the player's have drawn...
    if free_space == 0:
        print('Draw. Nobody wins.')
        # ... then there will be a variable 'draw' that is true.
        draw = True
    # if there is some free space still remaining, then the game hasn't ended and the players
    # can proceed.
    else:
        draw = False

    # we return the status of draw so that the main function loop knows if it can continue because
    # there is still room to play, or if it must stop because there is no room to play (even
    # if there isn't technically a singular winner).
    return draw







def main():

    # first we gather the input from the user on what they want the height and length of their
    # board to be. these transfer to the amount of rows and columns.
    board_height = int(input("What would you like the height of the board to be? "))
    board_length = int(input("What would you like the length of the board to be? "))

    # we assign the result of initialize_board() with the arguments board_height and board_length
    # to a variable called 'board' so that this main function is able to use the list created
    # by the method.
    board = initialize_board(board_height, board_length)
    # then we use print_board() to print the board we just initialized.
    print_board(board)

    # let the players know which one gets which chip
    print('Player 1: x\n' +
          'Player 2: o\n')

    # initialize the 'winner' variable to false so that the following while loop can continue to
    # iterate while there is no winner.
    winner = False
    while not winner:

        # player one tells the program in which column they want to put their chip.
        player_1_column = int(input("Player 1: Which column would you like to choose? "))
        # based on their selection, the board variable will be reassigned to the changed board
        # that results from adding the player's chip to the board at the column chosen.
        board = insert_chip(board, player_1_column, 'x')
        # then the row variable is assigned with the row that that chip lands in.
        row = find_row(board, player_1_column, 'x')

        # next, we determine if the chip that was added creates 4 in a row
        # if it does, winner will be assigned True, and if it does not, winner is assigned False.
        winner = check_if_winner(board, player_1_column, row, 'x')
        # if the player won, then the loop will break.
        if winner:
            break

        # same logic as steps above.
        player_2_column = int(input("Player 2: Which column would you like to choose? "))
        board = insert_chip(board, player_2_column, 'o')
        row = find_row(board, player_2_column, 'o')

        winner = check_if_winner(board, player_2_column, row, 'o')
        if winner:
            break

        # after both players have gone, we check to see if there is a draw as a result of using
        # all the space on the board.
        # if there is a draw, then winner will be assigned True and the loop will not iterate
        # again (even if there technically is not a single winner), but if there's no draw,
        # it's assigned with False and the loop can continue.
        winner = check_draw(board)


if __name__ == "__main__":

    main()
