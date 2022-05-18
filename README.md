# Conway's Game of Life
This is an implementation of John Conway's game of life in C. 
It uses gnuplot for the visualization of the system's evolution.

The game of life consists in an infinite 2-dimensional orthogonal grid of square cells.
Each cell can be in one of two possible states: alive (1) or dead (0).
Every cell interacts with its eight nearest neighbours (right, left, upper, bottom, upper-right, upper-left, bottom-right and bottom-left adjacent cells).
At each step in time, the following rules apply:

1) Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2) Any live cell with two or three live neighbours lives on to the next generation.
3) Any live cell with more than three live neighbours dies, as if by overpopulation.
4) Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

To run the simulation, all that it's needed is to provide an initial (seed) state.
Once the initial state is given, the evolution is determined by the sucessive application of the (1-4) rules to the whole grid.
Each generation depends only on the previous one.


# Adjusting parameters

You can alter the size of the grid (L) and the number of generations (tmax) in the gol.c code.

The default configuration is for a 100x100 grid and 10000 generations.

# Compiling the code

* $ gcc gol.c -o gol

# Running the code (using pipe with Gnuplot)

* $ ./gol | gnuplot

To interrupt code execution, use:
* Command^C

# Output Example
<figure><img align=midle src="images/hist1.gif" width="350"></figure>
