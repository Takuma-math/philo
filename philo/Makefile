NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# SRC_DIR     = philo/
# SRC         = $(SRC_DIR)main.c

SRC         = main.c parse_input.c fork.c philo_prepare.c philo_routine.c utils.c
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
