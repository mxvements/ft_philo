#ifndef PHILO_H
# define PHILO_H

// External functs libs
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

// Color: Foreground (text)
# define BLACK "\x1B[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1B[37m"
# define ORANGE "\x1B[38;2;255;128;0m"
# define ROSE "\x1B[38;2;255;151;203m"
# define LBLUE "\x1B[38;2;53;149;240m"
# define LGREEN "\x1B[38;2;17;245;120m"
# define GRAY "\x1B[38;2;176;174;174m"
# define RESET "\x1b[0m"

// Color: Background 
# define BG_BLACK "\x1B[40m"
# define BG_RED "\x1B[41m"
# define BG_GREEN "\x1B[42m"
# define BG_YELLOW "\x1B[43m"
# define BG_BLUE "\x1B[44m"
# define BG_MAGENTA "\x1B[45m"
# define BG_CYAN "\x1B[46m"
# define BG_WHITE "\x1B[47m"
# define BG_ORANGE "\x1B[48;2;255;128;0m"
# define BG_LBLUE "\x1B[48;2;53;149;240m"
# define BG_LGREEN "\x1B[48;2;17;245;120m"
# define BG_GRAY "\x1B[48;2;176;174;174m"
# define BG_ROSE "\x1B[48;2;255;151;203m"

typedef pthread_mutex_t t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meals_count;
	int				full; //(boolean)
	long			last_meal_time; //time passed from last meal
	struct s_fork	*left_fork;
	struct s_fork	*right_fork;
	pthread_t		thread_id; //a philo is a thread
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	long			philo_nbr;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			meal_limit;
	long			time_start;
	int				end_flag; //  boolean, when a philo dies or all philos are full
	struct s_fork	*forks;
	struct s_philo	*philos;

}	t_table;


/* init philo*/
void	philo_exit(const char *error);
int		init_table(t_table *table, char **argv);
void	print_table(t_table *table);
// int init_philo();

/* aux functions*/
long	ft_atolf(char *s, int *flag);

#endif