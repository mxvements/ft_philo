NAME=philo_test
CC=gcc
CFLAGS=-Wall -Wextra -Werror -g3
	
all: t1 t2 t3

t1:
	$(CC) $(CFLAGS) t1.c -o $(NAME)_t1

t2:
	$(CC) $(CFLAGS) t2.c -o $(NAME)_t2

t3:
	$(CC) $(CFLAGS) t3.c -o $(NAME)_t3

clean:
	rm -rf $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)*

re: fclean all

.PHONY: re fclean clean