# import necessary modules.
import random
import pygame
import sys


# set constants for size and colors.
board_size = 600
square_size = 55
line_color = pygame.Color("black")
board_color = pygame.Color("white")
rect_color = pygame.Color("orange")
sketch_color = pygame.Color("grey")
added_num_color = pygame.Color("blue")
highlight_color = pygame.Color("red")

# initialize pygame, create the display screen and fill it with white.
pygame.init()
screen = pygame.display.set_mode((board_size, board_size))
screen.fill(board_color)

# set window caption and initialize game fonts.
pygame.display.set_caption("Sudoku")
number_font = pygame.font.Font(None, 50)
welcome_font = pygame.font.Font(None, 75)
option_font = pygame.font.Font(None, 50)
sketch_font = pygame.font.Font(None, 35)
small_line = 2
big_line = 4 


# required class
class SudokuGenerator:

    # initialize instance variables
    def __init__(self, removed_cells, row_length=9):
        self.row_length = int(row_length)
        self.removed_cells = removed_cells
        # create an empty list for the board
        self.board = []
        # create nested loops and fill those loops with zeros.
        for i in range(self.row_length):
            self.board.append([])
        for item in self.board:
            for j in range(self.row_length):
                item.append(0) 
        self.box_length = 3

    # method to return the board.
    def get_board(self): 
        return self.board 

    # method to print the board.
    def print_board(self):
        print(self.board)

    # method to check if a given number is valid in a given row.
    def valid_in_row(self, row, num):
        # if the number is already in the row, the number is not valid.
        if num in self.board[row]:
            return False
        else:
            return True

    # method to check if a given number is valid in a given column.
    def valid_in_col(self, col, num):
        # for each row...
        for i in range(0, 9):
            # check the column position and see if it is equal to num. If
            # is it, then the number is not valid.
            if self.board[i][col] == num:
                return False
        return True

    # method to check if a given number is valid in a given box.
    def valid_in_box(self, row_start, col_start, num):
        # for each 3 by 3, check if the number belongs to any of the positions in the box.
        for i in range(row_start, row_start + 3):
            for j in range(col_start, col_start + 3):
                if self.board[i][j] == 0:
                    continue
                elif self.board[i][j] == num:
                    return False
        return True

    # checks if a given number is valid at some position.
    def is_valid(self, row, col, num):

        if not self.valid_in_row(row, num):
            return False
        if not self.valid_in_col(col, num):
            return False

        # if/ elif statements to determine which box must be checked based on the starting row
        # and column.
        if 0 <= row <= 2:
            if 0 <= col <= 2:
                if not self.valid_in_box(0, 0, num):
                    return False
            elif 3 <= col <= 5:
                if not self.valid_in_box(0, 3, num):
                    return False
            elif 6 <= col <= 8:
                if not self.valid_in_box(0, 6, num):
                    return False
        elif 3 <= row <= 5:
            if 0 <= col <= 2:
                if not self.valid_in_box(3, 0, num):
                    return False
            elif 3 <= col <= 5:
                if not self.valid_in_box(3, 3, num):
                    return False
            elif 6 <= col <= 8:
                if not self.valid_in_box(3, 6, num):
                    return False
        elif 6 <= row <= 8:
            if 0 <= col <= 2:
                if not self.valid_in_box(6, 0, num):
                    return False
            elif 3 <= col <= 5:
                if not self.valid_in_box(6, 3, num):
                    return False
            elif 6 <= col <= 8:
                if not self.valid_in_box(6, 6, num):
                    return False

        return True

    # method to fill a box with randomly generated numbers.
    def fill_box(self, row_start, col_start):

        board = self.board 

        # for each position in the 3 by 3 box...
        for i in range(row_start, (row_start + 3)):
            for j in range(col_start, (col_start + 3)):
                # generate a random number.
                random_num = random.randint(1, 9)
                # if the number has already been used in the box, generate a new one
                # until it's a new number
                while self.used_in_box(board, random_num, row_start, (row_start + 3), col_start, (col_start + 3)):
                    random_num = random.randint(1, 9)
                # assign that number to the current position in the box.
                board[i][j] = random_num 

    # new method to determine if a number has been used in a box.
    @staticmethod
    def used_in_box(board, num, start_row, end_row, start_col, end_col):

        # for each position in the 3 by 3 box, check if the number there
        # is equal to the current random number.
        for i in range(start_row, end_row):
            for j in range(start_col, end_col):
                if board[i][j] == num:
                    return True
                else:
                    continue
        return False

    # method that fills the diagonal boxes on the board.
    def fill_diagonal(self):

        self.fill_box(0, 0)
        self.fill_box(3, 3)
        self.fill_box(6, 6)

    # given method that fills the remaining boxes in the board.
    def fill_remaining(self, row, col):
        if col >= self.row_length and row < self.row_length - 1:
            row += 1
            col = 0
        if row >= self.row_length and col >= self.row_length:
            return True
        if row < self.box_length:
            if col < self.box_length:
                col = self.box_length
        elif row < self.row_length - self.box_length:
            if col == int(row // self.box_length * self.box_length):
                col += self.box_length
        else:
            if col == self.row_length - self.box_length:
                row += 1
                col = 0
                if row >= self.row_length:
                    return True

        for num in range(1, self.row_length + 1):
            if self.is_valid(row, col, num):
                self.board[row][col] = num
                if self.fill_remaining(row, col + 1):
                    return True
                self.board[row][col] = 0
        return False

    # given method that fills the whole board.
    def fill_values(self):
        self.fill_diagonal() 
        self.fill_remaining(0, self.box_length)

    # method to remove a certain number of cells from a board based
    # on a given difficulty.
    def remove_cells(self):

        count = 0

        # loop that will continue to remove numbers from cells until the number of empty
        # cells reached the number that should be removed based on the difficulty
        # (30 - easy, 40 - medium, 50 - hard).
        while count < self.removed_cells:
            # generate a random column and random row.
            row_to_remove = random.randint(0, 8)
            col_to_remove = random.randint(0, 8)
            # to_change keeps track of that col and row.
            to_change = self.board[row_to_remove][col_to_remove]
            # while the number at that position is equal to zero...
            while to_change == 0:
                # generate a new row and col until one is selected that contains a nonzero number.
                row_to_remove = random.randint(0, 8)
                col_to_remove = random.randint(0, 8)
                to_change = self.board[row_to_remove][col_to_remove]
            # set that position on the board equal to zero.
            self.board[row_to_remove][col_to_remove] = 0
            # increase the count so the loop can terminate at the proper time.
            count += 1


# given function to generate the sudoku board,
def generate_sudoku(removed, size):
    sudoku = SudokuGenerator(removed, size)
    sudoku.fill_values()
    answer = [[j for j in sudoku.board[index]] for index, i in enumerate(sudoku.board)]
    sudoku.remove_cells()
    board = sudoku.get_board()
    return board, answer


# recommended Board class to allow the user to change the board.
class Board:

    # initialize instance variables.
    def __init__(self, board, solution, width, height, display, difficulty):
        self.width = width
        self.height = height
        self.screen = display
        self.difficulty = difficulty
        self.board = board
        # board copy for altering the board.
        self.board_copy = [[j for j in self.board[index]] for index, i in enumerate(board)]
        # board copy for sketching values but not yet altering the board.
        self.board_copy_sketch = [[j for j in self.board[index]] for index, i in enumerate(board)]
        self.solution = solution

    # method to draw the board.
    def draw(self):

        cell_center_x = 28
        cell_center_y = 28

        # for loops to draw the grid.
        for i in range(10):
            pygame.draw.line(screen, line_color,
                             (55, i * square_size),
                             (board_size - 50, i * square_size),
                             small_line)

        for i in range(1, 11):
            pygame.draw.line(screen, line_color,
                             (i * square_size, 0),
                             (i * square_size, board_size - 105),
                             small_line)

        for i in range(0, 10, 3):
            pygame.draw.line(screen, line_color,
                             (55, i * square_size),
                             (board_size - 50, i * square_size),
                             big_line)

        for i in range(1, 11, 3):
            pygame.draw.line(screen, line_color,
                             (i * square_size, 0),
                             (i * square_size, board_size - 105),
                             big_line)

        # for loop to draw each number in the current board onto the grid.
        for row, i in enumerate(self.board):
            for col, j in enumerate(self.board[row]):
                cell_center_x += 55
                # if the number is zero, no number should be drawn.
                if self.board[row][col] == 0:
                    continue 
                else:
                    number_surf = number_font.render(f"{self.board[row][col]}", 0, line_color)
                    number_rect = number_surf.get_rect(center=(cell_center_x, cell_center_y))
                    screen.blit(number_surf, number_rect)
            cell_center_x = 28
            cell_center_y += 55

        pygame.display.update()

    # method that allows user to select and edit cells in the grid.
    def select(self, row, col, x, y):

        start_x, start_y = 0, 0
        mid_x, mid_y = 0, 0

        # y coordinates based on a given row found by the click() method.
        if row == 1:
            start_y = 0
            mid_y = 28
        elif row == 2:
            start_y = 55
            mid_y = 83
        elif row == 3:
            start_y = 110
            mid_y = 138
        elif row == 4:
            start_y = 165
            mid_y = 193
        elif row == 5:
            start_y = 220
            mid_y = 248
        elif row == 6:
            start_y = 275
            mid_y = 303
        elif row == 7:
            start_y = 330
            mid_y = 358
        elif row == 8:
            start_y = 385
            mid_y = 413
        elif row == 9:
            start_y = 440
            mid_y = 468

        # x coordinates based on a given row found by the click() method.
        if col == 1:
            start_x = 55
            mid_x = 83
        elif col == 2:
            start_x = 110
            mid_x = 138
        elif col == 3:
            start_x = 165
            mid_x = 193
        elif col == 4:
            start_x = 220
            mid_x = 248
        elif col == 5:
            start_x = 275
            mid_x = 303
        elif col == 6:
            start_x = 330
            mid_x = 358
        elif col == 7:
            start_x = 385
            mid_x = 413
        elif col == 8:
            start_x = 440
            mid_x = 468
        elif col == 9:
            start_x = 495
            mid_x = 523

        # set cell equal to the current position the user has clicked.
        cell = self.board[row - 1][col - 1]
        # highlight the cell
        pygame.draw.rect(screen, highlight_color, pygame.Rect(start_x, start_y, 57, 57), 2)
        pygame.display.update()

        # while the board is not full...
        while not self.is_full():

            key = "0"

            # for every action...
            for action in pygame.event.get():

                if action.type == pygame.KEYDOWN:
                    num_keys = [pygame.K_1, pygame.K_2, pygame.K_3, pygame.K_4, pygame.K_5,
                                pygame.K_6, pygame.K_7, pygame.K_8, pygame.K_9]
                    if action.key == pygame.K_1:
                        key = "1"
                    elif action.key == pygame.K_2:
                        key = "2"
                    elif action.key == pygame.K_3:
                        key = "3"
                    elif action.key == pygame.K_4:
                        key = "4"
                    elif action.key == pygame.K_5:
                        key = "5"
                    elif action.key == pygame.K_6:
                        key = "6"
                    elif action.key == pygame.K_7:
                        key = "7"
                    elif action.key == pygame.K_8:
                        key = "8"
                    elif action.key == pygame.K_9:
                        key = "9"

                    # allows users to sketch their answer.
                    if action.key in num_keys and cell == 0:
                        self.sketch(key, start_x, start_y, row, col)

                        # determine the next action.
                        not_actual_action = pygame.event.wait()
                        next_action = pygame.event.wait()

                        if next_action.type == pygame.KEYDOWN:
                            # users can enter their answer
                            if next_action.key == pygame.K_RETURN:
                                self.place_number(key, mid_x, mid_y, start_x, start_y, row, col)
                                self.draw()
                                pygame.display.update()
                                # return zero to bring the user back to the loop in main().
                                return 0
                            # user can delete their sketch
                            elif next_action.key == pygame.K_BACKSPACE:
                                self.clear(start_x, start_y, row, col)
                                return 0
                            # user can move to the cell below with the arrow keys.
                            elif next_action.key == pygame.K_DOWN:
                                if row != 9:
                                    self.draw()
                                    return self.select(row + 1, col, x, y + 55)
                                else:
                                    self.draw()
                                    pygame.display.update()
                            # user can move to the cell to the left with the arrow keys.
                            elif next_action.key == pygame.K_LEFT:
                                if col != 1:
                                    self.draw()
                                    return self.select(row, col - 1, x - 55, y)
                                else:
                                    self.draw()
                                    pygame.display.update()
                            # user can move to the cell to the right with the arrow keys.
                            elif next_action.key == pygame.K_RIGHT:
                                if col != 9:
                                    self.draw()
                                    return self.select(row, col + 1, x + 55, y)
                                else:
                                    self.draw()
                                    pygame.display.update()
                            # user can move to the cell above with the arrow keys.
                            elif next_action.key == pygame.K_UP:
                                if row != 1:
                                    self.draw()
                                    return self.select(row - 1, col, x, y - 55)
                                else:
                                    self.draw()
                                    pygame.display.update()
                        # user can unselect the cell
                        elif next_action.type == pygame.MOUSEBUTTONDOWN:
                            self.draw()
                            pygame.display.update()
                            return 0
                    # user can enter the sketched answer.
                    elif action.key == pygame.K_RETURN:
                        if cell == 0:
                            self.place_number(key, mid_x, mid_y, start_x, start_y, row, col)
                            self.draw()
                            pygame.display.update()
                            return 0
                    # user can delete their answer.
                    elif action.key == pygame.K_BACKSPACE:
                        if self.board[row - 1][col - 1] == 0:
                            return self.clear(start_x, start_y, row, col)
                    # user can switch cell with the arrow keys.
                    elif action.key == pygame.K_DOWN:
                        if row != 9:
                            self.draw()
                            return self.select(row + 1, col, x, y + 55)
                        else:
                            self.draw()
                            pygame.display.update()
                    elif action.key == pygame.K_LEFT:
                        if col != 1:
                            self.draw()
                            return self.select(row, col - 1, x - 55, y)
                        else:
                            self.draw()
                            pygame.display.update()
                    elif action.key == pygame.K_RIGHT:
                        if col != 9:
                            self.draw()
                            return self.select(row, col + 1, x + 55, y)
                        else:
                            self.draw()
                            pygame.display.update()
                    elif action.key == pygame.K_UP:
                        if row != 1:
                            self.draw()
                            return self.select(row - 1, col, x, y - 55)
                        else:
                            self.draw()
                            pygame.display.update()
                # user can deselect the cell and select a new one.
                elif action.type == pygame.MOUSEBUTTONDOWN:
                    self.draw()
                    pygame.display.update()
                elif action.type == pygame.MOUSEBUTTONUP:
                    x, y = action.pos
                    # if the space where the user clicked is on the grid, then a new cell
                    # will be selected.
                    if 0 < y < 500 and 59 < x < 547:
                        new_row, new_col = self.click(x, y)
                        return self.select(new_row, new_col, x, y)
                # user can quit the game.
                elif action.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

    # method to find what row and column the user clicked based on x and y coordinates.
    @staticmethod
    def click(x, y):

        # nested function to determine column based on x coordinate.
        def check_x(x_coord):

            if 59 < x_coord < 110:
                return 1
            if 111 < x_coord < 165:
                return 2
            if 166 < x_coord < 220:
                return 3
            if 221 < x_coord < 276:
                return 4
            if 277 < x_coord < 331:
                return 5
            if 332 < x_coord < 384:
                return 6
            if 385 < x_coord < 441:
                return 7
            if 442 < x_coord < 495:
                return 8
            if 496 < x_coord < 547:
                return 9

        # determine the row based on y coordinate.
        if 0 < y < 55:
            row = 1
            col = check_x(x)
        elif 56 < y < 109:
            row = 2
            col = check_x(x)
        elif 110 < y < 167:
            row = 3
            col = check_x(x)
        elif 168 < y < 219:
            row = 4
            col = check_x(x)
        elif 220 < y < 274:
            row = 5
            col = check_x(x)
        elif 275 < y < 328:
            row = 6
            col = check_x(x)
        elif 329 < y < 385:
            row = 7
            col = check_x(x)
        elif 386 < y < 439:
            row = 8
            col = check_x(x)
        elif 440 < y < 500:
            row = 9
            col = check_x(x)
        else:
            return 0, 0

        # return the row and column.
        return row, col

    # method to clear a cell.
    def clear(self, start_x, start_y, row, col):

        # clear the cell by drawing a rectangle...
        pygame.draw.rect(screen, board_color, pygame.Rect(start_x + 5, start_y + 5, 48, 48))
        pygame.display.update()
        # and update the board copy to be zero at the position again.
        if self.board_copy[row][col] != 0:
            self.board_copy[row][col] = 0

    # method to sketch an answer into a cell.
    def sketch(self, value, start_x, start_y, row, col):

        # set the position on the board copy sketch as the input value.
        self.board_copy_sketch[row - 1][col - 1] = int(value)
        # clear the cell in case there was something already there.
        pygame.draw.rect(screen, board_color, pygame.Rect(start_x + 5, start_y + 5, 48, 48))
        # display the sketched value.
        sketch_surf = sketch_font.render(f"{value}", 0, sketch_color)
        sketch_rect = sketch_surf.get_rect(center=(start_x + 10, start_y + 15))
        screen.blit(sketch_surf, sketch_rect)

        pygame.display.update()

    # method to commit the answer to the board.
    def place_number(self, value, x, y, start_x, start_y, row, col):

        # as long as the current position of board_copy is zero, it can be altered to be the
        # same value as the sketched value at that position. This is so that numbers that are
        # given to the user cannot be changed.
        if self.board_copy[row - 1][col - 1] == 0:
            self.board_copy[row - 1][col - 1] = self.board_copy_sketch[row - 1][col - 1]
        # clear the grid to remove the sketched value.
        pygame.draw.rect(screen, board_color, pygame.Rect(start_x + 5, start_y + 5, 48, 48))
        pygame.display.update()
        # draw the commited value.
        sketch_surf = number_font.render(f"{self.board_copy_sketch[row - 1][col - 1]}", 0, added_num_color)
        sketch_rect = sketch_surf.get_rect(center=(x, y))
        screen.blit(sketch_surf, sketch_rect)

        pygame.display.update()

    # method to reset the board to its original state.
    def reset_to_original(self):

        # create a new list for board copy that deletes all user input values and reverts the
        # board_copy back to the original board.
        self.board_copy = [[j for j in self.board[index]] for index, i in enumerate(self.board)]
        # draw a white rectangle over all the current board and draw the board again.
        pygame.draw.rect(screen, board_color, pygame.Rect(0, 0, 550, 500))
        self.draw()

    # method to check if the board is full.
    def is_full(self):

        # for loops to read over every position in the board_copy. If any positions are still
        # zero, then the user has not entered a value in every cell and the method can return
        # false because the board is not yet full.
        for row, i in enumerate(self.board_copy):
            for col, j in enumerate(self.board_copy[row]):
                if self.board_copy[row][col] == 0:
                    return False
        return True

    # method to check if the board was solved correctly.
    def check_board(self):

        # if every position in the board_copy is equal to the solution then the board was
        # solved correctly and the method can return true.
        if self.board_copy == self.solution:
            return True
        else:
            return False


# function to print the menu.
def menu():

    # display welcome message
    start_surf = welcome_font.render("Welcome to Sudoku!", 0, line_color)
    start_rect = start_surf.get_rect(center=(board_size // 2, board_size // 2 - 150))
    screen.blit(start_surf, start_rect)

    # display game selections.
    option_select = option_font.render("Select Game Mode:", 0, line_color)
    option_rect = option_select.get_rect(center=(board_size // 2, board_size // 2 + 50))
    screen.blit(option_select, option_rect)

    pygame.draw.rect(screen, rect_color, pygame.Rect(100, 390, 100, 60))
    pygame.draw.rect(screen, rect_color, pygame.Rect(225, 390, 145, 60))
    pygame.draw.rect(screen, rect_color, pygame.Rect(400, 390, 100, 60))


    options = option_font.render("Easy     Medium     Hard", 0, line_color)
    options_rect = options.get_rect(center=(board_size // 2, board_size // 2 + 120))
    screen.blit(options, options_rect)


# function to draw the options that appear at the bottom of the screen during the game.
def draw_options():

    pygame.draw.rect(screen, rect_color, pygame.Rect(75, 525, 130, 60))
    pygame.draw.rect(screen, rect_color, pygame.Rect(235, 525, 140, 60))
    pygame.draw.rect(screen, rect_color, pygame.Rect(405, 525, 130, 60))

    reset_surf = option_font.render("Reset", 0, line_color)
    reset_rect = reset_surf.get_rect(center=(board_size // 2 - 160, board_size // 2 + 255))
    screen.blit(reset_surf, reset_rect)

    restart_surf = option_font.render("Restart", 0, line_color)
    restart_rect = restart_surf.get_rect(center=(board_size // 2 + 5, board_size // 2 + 255))
    screen.blit(restart_surf, restart_rect)

    exit_surf = option_font.render("Exit", 0, line_color)
    exit_rect = exit_surf.get_rect(center=(board_size // 2 + 170, board_size // 2 + 255))
    screen.blit(exit_surf, exit_rect)


# function to draw the win screen and the option to exit the game.
def draw_win():

    screen.fill(board_color)

    start_surf = welcome_font.render("Game Won!", 0, line_color)
    start_rect = start_surf.get_rect(center=(board_size // 2, board_size // 2 - 150))
    screen.blit(start_surf, start_rect)

    pygame.draw.rect(screen, rect_color, pygame.Rect(230, 390, 140, 60))

    options = option_font.render("Exit", 0, line_color)
    options_rect = options.get_rect(center=(board_size // 2, board_size // 2 + 120))
    screen.blit(options, options_rect)


# function to draw the lose screen and the option to restart.
def draw_lose():

    screen.fill(board_color)

    start_surf = welcome_font.render("Game Over :(", 0, line_color)
    start_rect = start_surf.get_rect(center=(board_size // 2, board_size // 2 - 150))
    screen.blit(start_surf, start_rect)

    pygame.draw.rect(screen, rect_color, pygame.Rect(230, 390, 140, 60))

    options = option_font.render("Restart", 0, line_color)
    options_rect = options.get_rect(center=(board_size // 2, board_size // 2 + 120))
    screen.blit(options, options_rect)


def main():

    # display the menu
    menu()
    pygame.display.update()
    # initialize variables
    cells_removed = None
    difficulty = None
    game_over = False
    win = False

    while True:

        # for users first selection....
        event = pygame.event.wait()
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
        # if they clicked...
        elif event.type == pygame.MOUSEBUTTONDOWN and not game_over:
            x, y = event.pos
            # and they clicked over where the options are...
            if 380 < y < 450:
                # at one of theses x coordinates, then a difficulty will be selected.
                if 100 < x < 200:
                    cells_removed = 30
                    difficulty = "Easy"
                elif 225 < x < 370:
                    cells_removed = 40
                    difficulty = "Medium"
                elif 400 < x < 500:
                    cells_removed = 50
                    difficulty = "Hard"
                else:
                    continue

                # once selected, the board can clear the menu display.
                screen.fill(board_color)
                pygame.display.update()
                break

    # call generate_sudoku() and save the results as sudoku and solution.
    sudoku, solution = generate_sudoku(cells_removed, 9)
    print(solution)
    # create an instance of class Board so the user can edit the board.
    board = Board(sudoku, solution, 9, 9, screen, difficulty)
    # draw the options
    draw_options()
    # draw the grid and numbers in the board.
    board.draw()
    pygame.display.update()

    # loop player options.
    while not game_over:

        for event in pygame.event.get():
            # the user can exit.
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            # the user can click the board...
            if event.type == pygame.MOUSEBUTTONDOWN:
                x, y = event.pos
                # if the coordinates where they click are where the options are located...
                if 520 < y < 590:
                    if 75 < x < 205:
                        # the user can reset the board...
                        board.reset_to_original()
                        draw_options()
                    if 230 < x < 370:
                        # restart the whole game...
                        screen.fill(board_color)
                        main()
                        break
                    if 405 < x < 535:
                        # or quit the program.
                        quit()
                elif 0 < y < 500 and 59 < x < 547:
                    # if the user clicks somewhere in the grid...
                    # determine the row and column of the cell they clicked.
                    row, col = board.click(x, y)
                    # then use that to call the select() method from board so that they can edit the
                    # cell.
                    returned = board.select(row, col, x, y)
                    # once they have edited the cell, determine if the board is full.
                    if board.is_full():
                        # if the board is full, the game is over and the current loop will terminate.
                        game_over = True
                        # then determine if the user has won or not.
                        if board.check_board():
                            win = True
                        else:
                            win = False

    # wait half a second before proceeding.
    pygame.time.wait(500)

    # if the user won...
    if win:
        # display the win screen
        draw_win()
        pygame.display.update()
        # loop so they can select a new option.
        while True:

            for action in pygame.event.get():
                # if the user clicks...
                if action.type == pygame.MOUSEBUTTONDOWN:
                    # and if the click is on top of the exit button...
                    x, y = action.pos
                    if 390 < y < 450:
                        if 230 < x < 390:
                            # the program will exit.
                            quit()
                elif action.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()

    # if the user lost...
    elif not win:
        # display the losing screen.
        draw_lose()
        pygame.display.update()
        # loop so they can select an option.
        while True:

            for action in pygame.event.get():
                # if the user clicks...
                if action.type == pygame.MOUSEBUTTONDOWN:
                    x, y = action.pos
                    # and the click is above the restart button...
                    if 390 < y < 450:
                        if 230 < x < 390:
                            # reinitialize game_over to False
                            game_over = False
                            screen.fill(board_color)
                            pygame.display.update()
                            # and call main to restart the game.
                            main()
                # otherwise the user can still quit.
                elif action.type == pygame.QUIT:
                    pygame.quit()
                    sys.exit()




if __name__ == '__main__':
    main()
