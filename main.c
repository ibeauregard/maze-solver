#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        dprintf(STDERR_FILENO, "%s\n", "my_mouse takes exactly one argument (path to maze file)");
        return EXIT_FAILURE;
    }
    printf("%s\n", argv[1]);
    return EXIT_SUCCESS;
}
