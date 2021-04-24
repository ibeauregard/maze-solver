# my_mouse

## Description

`my_mouse` finds the shortest path between the entrance and the exit of a maze, while avoiding obstacles. Movements are horizontal or vertical, but cannot be diagonal.

## Compiling

To compile the application, run `make` from the project's root directory.

## Running the application

Run `./my_mouse <path_to_maze>...` from the project's root directory.

Example: `./my_mouse maze.txt maze0.txt`

## Generate a new maze

Run `ruby maze_generator.rb <height> <width> "<character map>" > <output_file_name>`.

Example: `ruby maze_generator.rb 16 16 "* o12" > maze.txt`

The character map is a sequence of exactly five *distinct* characters:

1. A character representing walls (or obstacles) in the maze
2. A character representing free squares (where one could walk)
3. A character representing the path taken from entrance to exit (once the maze is solved)
4. A character representing the entrance
5. A character representing the exit

## Definition of a valid maze file

The first line is a header, with the following format: `<height>x<width><char_map>`, e.g. `32x32* o12`.
The rest of the file displays the rows (one row per line), according to the format specified by the header. See `maze.txt` for an example.

A maze has to observe a number a number of constraints in order to be a valid one:
- The number of rows has to match the one specified in the header. 
- For each line, the number of columns has to match the one specified in the header. This number is limited to 1,000.
- There will be no more than one billion squares.
- There has to be exactly one entrance and exactly one exit.
- Only the characters specified in the header's character map (e.g. `* o12`) should appear in the maze.
- There must be a path between the entrance and the exit.

Any violation to these specifications will generate an error, and the program will move on handling the next maze given as an input.

## Warning

In practice, the application can only solve mazes where the distance between the entrance and the exit is relatively short.

The resolution starts to take more than a few seconds as soon as the [Manhattan distance](https://en.wikipedia.org/wiki/Taxicab_geometry) between the entrance and the exit approaches ~50.

If the maze has no solution, the path search algorithm is forced to explore a much greater number of possibilities before it can conclude that there is indeed no solution. Consequently, if you run the application with a maze that has no solution, the running time could be very long even for relatively small mazes.

## Implementation notes

This application uses an [iterative deepening A*](https://en.wikipedia.org/wiki/Iterative_deepening_A*) (IDA*) path search algorithm.

The time complexity of the algorithm is O(3<sup>m</sup>), where `m` is the number of steps needed to go from the entrance to the exit.

Its space complexity is O(m).

The code base also generally uses a coding style called "C-plus", emulating object-oriented programming and encapsulation of data with the C programming language.
