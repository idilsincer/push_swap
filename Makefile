NAME: push_swap.a

CC: cc

CFLAGS: -Wall -Wextra -Werror

SRCS: push_swap.c

OBJ: $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY all clean fclean re