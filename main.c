#include "maze.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MISSING_ARG_ERR "my_mouse takes one or more arguments\nmy_mouse <maze_filepath>..."

int main(int argc, char* argv[])
{
    if (argc < 2) {
        dprintf(STDERR_FILENO, "%s\n", MISSING_ARG_ERR);
        return EXIT_FAILURE;
    }
    for (int i = 1; i < argc; i++) {
        Maze* maze = MazeClass.fromPath(argv[i]);
        maze->print(maze);
        puts("");
        maze->delete(maze);
    }
    return EXIT_SUCCESS;
}
