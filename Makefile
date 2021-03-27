CC = gcc
CFLAGS += -Wall -Wextra -Werror -Wpedantic -g3 -O3
SANITIZE = -fsanitize=address
LINKERFLAG = -lm
SRCS = $(wildcard *.c) $(wildcard */*.c)
OBJS = $(SRCS:.c=.o)
MAIN = my_mouse

.PHONY = all clean fclean re

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(SANITIZE) -o $@ $(LINKERFLAG) $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(MAIN)

re: fclean all
