#include "maze.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        dprintf(STDERR_FILENO, "%s\n", "my_mouse takes exactly one argument (path to maze file)");
        return EXIT_FAILURE;
    }
    Maze* maze = MazeClass.fromPath(argv[1]);
    printf("%p\n", (void*) maze->_internals);
    maze->delete(maze);

    return EXIT_SUCCESS;
}
