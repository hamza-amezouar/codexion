# varaibels
NAME        = codexion
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

F_SRC = codexion.c parser.c  utils.c init.c simulation.c monitor.c heap.c dongles.c


OBJS        = $(F_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c codexion.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re