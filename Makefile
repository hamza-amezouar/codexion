NAME        = codexion
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
RM          = rm -f
FOLDER		= coders

F_SRC = $(FOLDER)/codexion.c  $(FOLDER)/parser.c   $(FOLDER)/utils.c \
		 $(FOLDER)/init.c  $(FOLDER)/simulation.c  $(FOLDER)/monitor.c  $(FOLDER)/heap.c  $(FOLDER)/dongles.c


OBJS        = $(F_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(FOLDER)/%.o: $(FOLDER)/%.c $(FOLDER)/codexion.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re