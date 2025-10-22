import numpy as np

# Board Class
class Board:
    """This class defines boards for bingo game"""
    def __init__(self, numbers):
        self.board_width = 5
        self.board_height = 5
        self.numbers = numbers
        self.marked = np.zeros((self.board_width, self.board_height))

    def is_in_board(self, number):
        if number in self.numbers:
            return True
        return False

    def mark(self, number):
        for i in range(self.board_width):
            for j in range(self.board_height):
                if self.numbers[i, j] == number:
                    self.marked[i, j] = 1

    def is_win(self):
        for i in range(self.board_width):
            if sum(self.marked[i]) == self.board_height:
                return True
        for i in range(self.board_height):
            if sum(np.transpose(self.marked)[i]) == self.board_width:
                    return True
        return False

    def get_score(self, r):
        sum_unmarked = 0
        for i in range(self.board_width):
            for j in range(self.board_width):
                if self.marked[i, j] == 0:
                    sum_unmarked += self.numbers[i, j]
        return sum_unmarked * r 

    
    def get_board(self):
        return self.numbers
        

# Main
if __name__ == "__main__":
    # Read data
    with open("input.txt") as f:
        data = f.readlines()

    # Remove extra spaces, \n, ...
    for i in range(len(data)):
        data[i] = data[i].strip()

    # Random numbers
    rand_nums = [int(x) for x in data[0].split(",")] 

    # Define boards using Board class
    boards = []
    for i in range(2, len(data), 6):
        temp = []
        for j in range(5):
            line = data[i + j].split()
            for k in range(len(line)):
                line[k] = int(line[k])
            temp.append(line)
        boards.append(Board(np.array(temp)))
    
    # Begin the game
    winner_boards = [] 
    last_winning_number = []
    for r in rand_nums:
        for board in boards:
            if board.is_in_board(r):
                board.mark(r)
                if board.is_win():
                    if board not in winner_boards:
                        winner_boards.append(board)
                        last_winning_number.append(board.get_score(r))

    print(winner_boards[-1].get_board())
    print(last_winning_number[-1])





