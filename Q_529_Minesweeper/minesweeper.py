"""
The goal is to build few classes and implement some methods 
for the game "Minesweeper".

Rules of the game:
  if click on mine: 
	game over
  elif click on a cell that has neighboring mines:
	reveal the cell whose value is the number of neighboring mines
  elif click on a cell that does not have any neighboring mines:
	recurssively click on its neighbors

Some possible classes:
- Position: an x-y coordinate
- Board: a collection of (x, y) positions
- State: the value displayed at the position to the user
- Game: a single instance of a game
These are just some suggestions. You can dicide to use any combination of
classes that makes sense to you.

You need to have at least the following methods publically accessible:
def initialize(self, height, width, num_mines, initial_click=None):
	# initialize a fix-sized board with given number of mines.
	# if the optional parameter initial_click is specified, no mine should be placed there
	pass

def click(self, position):
	# change the states of some points on the borad following the rules
		pass

def visualize(self):
	# "." for unexplored
	# " " for explored but no neighboring mines
	# "#" for explored with # of mines
	pass
"""
from numpy.random import randint
import numpy as np
import re

class Game:
	def __init__(self, height = 8, width = 8, num_mines = 8):
		self.explored = np.full((height, width), fill_value = -1, dtype = np.int8)
		self.mines = np.zeros((height, width), dtype = np.int8)
		self.finished = False
		self.height = height
		self.width = width
		for i in range(num_mines):
			x = randint(0, height)
			y = randint(0, width)
			while(self.mines[x][y] == 1):
				x = randint(0, height)
				y = randint(0, width)
			self.mines[x][y] = 1
		
	def printMines(self):
		print(self.mines)
		
	def count_neighboring_mines(self, x, y):
		neighbors = [(i, j) for i in range(x - 1, x + 2) for j in range(y - 1, y + 2)]
		count = 0
		for neighbor in neighbors:
			i, j = neighbor
			if 0 <= i and i < self.height and 0 <= j and j < self.width and self.mines[i][j] == 1:
				count += 1
		return count
	
	def explore(self, x, y):
		explore_queue = {(i, j) for i in range(x - 1, x + 2) for j in range(y - 1, y + 2)}
		while (len(explore_queue) > 0):
			i, j = explore_queue.pop()
			if not (0 <= i and i < self.height and 0 <= j and j < self.width):
				continue
			if self.mines[i][j] == 1:
				continue
			if self.explored[i][j] != -1:
				continue
			count = self.count_neighboring_mines(i, j)
			self.explored[i][j] = count
			if count == 0:
				explore_queue.update([
					(i - 1, j - 1),
					(i - 1, j),
					(i - 1, j + 1),
					(i, j - 1),
					(i, j + 1),
					(i + 1, j - 1),
					(i + 1, j),
					(i + 1, j + 1)])
	
	def check_win(self):
		return np.array_equal(np.where(self.explored == -1), np.where(self.mines == 1))
	
	def click(self, position):
		x, y = position
		# change the states of some points on the board following the rules
		if (self.mines[x][y] == 1):
			print("Game over")
			self.finished = True
			return
		
		count = self.count_neighboring_mines(x, y)
		print(f"{count} neighboring mines")
		self.explore(x, y)
		if self.check_win():
			self.finished = True
	
	def visualize(self):
		# "." for unexplored
		# " " for explored but no neighboring mines
		# "#" for explored with # of mines
		print("   " + " ".join([f"{i}" for i in range(self.width)]))
		print("   " + "--" * self.width)
		for i, row in enumerate(self.explored):
			row_str = "{}|".format(i)
			for col in row:
				if col == -1:
					row_str += " ."
				elif col == 0:
					row_str += "  "
				else:
					row_str += " " + str(col)
			print(row_str)
		print("\n")

def initialize(height, width, num_mines, initial_click=None):
	# initialize a fix-sized board with given number of mines.
	# if the optional parameter initial_click is specified, no mine should be placed there
	print("initializing game")
	game = Game()
	while (not game.finished):
		game.printMines()
		val = input("Enter a position to click on (row, column): ")
		val = re.split("[^0-9]", val.strip())
		game.click((int(val[0]), int(val[1])))
		game.visualize()
	game.printMines()
	if (game.check_win()):
		print("You won!")
	else:
		print("You lost")
	
if __name__ == "__main__":
	initialize(8, 8, 8)
