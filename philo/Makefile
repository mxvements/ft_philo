NAME=philo
CC=gcc
CFLAGS=-Wall -Wextra -Werror -g3

#philo
PHILO_PATH=		./philo/
PHILO_FILES=	philo.c

#objs
OBJ_PATH=	obj/
OBJ=		$(PHILO_FILES:%.c=$(OBJ_PATH)%.o)

#rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)

$(OBJ_PATH)%.o: $(PHILO_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean