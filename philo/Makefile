NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread
RM          = rm -f

SRC         = main.c parse_input.c fork.c prepare.c philo_routine_utils.c philo_routine.c utils.c monitor.c
OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
