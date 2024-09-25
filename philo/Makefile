NAME=philo
CC=gcc
CFLAGS=-Wall -Wextra -Werror -g3

#philo
PHILO_PATH=		./
PHILO_FILES=	philo.c \
				philo_utils.c \
				philo_utils_bool.c \
				philo_utils_long.c \
				philo_dinner.c \
				philo_dinner_functs.c \
				philo_monitor.c \
				pthread_handle.c \
				table_init.c \
				table_destroy.c \
				table_clean.c \
				table_utils.c \
				ft_atolf.c \
				ft_usleep.c \
				ft_gettime.c

#aux files
# AUX_PATH=	./
# AUX_FILES=	ft_atolh.c

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