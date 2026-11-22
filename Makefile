NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = push_swap.c s_operations.c p_operations.c r_operations.c rr_operations.c \
	main.c parse.c stack.c ops.c bench.c sort_simple_medium.c sort_complex.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
