#ifndef PHILO_H
# define PHILO_H

// External functs libs
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <errno.h>

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

# define DEBUG	0
/* --------------------------------------------------------------------------*/
typedef pthread_mutex_t t_mtx;

/** Allowed functions:
 * 	threads:
 * 		pthread_create
 * 		pthread_detach
 * 		pthread_join
 * 	mutex: 
 * 		pthread_mutex_init
 * 		pthread_mutex_destroy,
 * 		pthread_mutex_lock
 * 		pthread_mutex_unlock
 */
typedef enum e_opthread
{
	CREATE,		//0
	DETACH,		//1
	JOIN,		//2
	INIT,		//3
	DESTROY,	//4
	LOCK,		//5
	UNLOCK		//6
}	t_opthread;

typedef enum e_time
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}	t_time;

typedef enum e_status
{
	EAT,
	SLEEP,
	THINK,
	FRST_FORK,
	SCND_FORK,
	DIE
}	t_status;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		id_thread; //a philo is a thread
	t_fork			*first_fork;
	t_fork			*secnd_fork;
	long			meals_count;
	long			t_last_meal; //time passed from last meal
	int				is_full; //(boolean)
	struct s_table	*table;
	t_mtx			philo_mtx;
}	t_philo;

typedef struct s_table
{
	long		philos_nbr;
	long		philos_running_nbr; //to monitor
	pthread_t	monitor;
	long		t_start;
	long		t_to_die;
	long		t_to_eat;
	long		t_to_sleep;
	long		meal_limit;
	int			is_finished; //boolean, when a philo dies or all philos are full
	int			is_ready; //are all philos ready, to synchro philosophers
	t_fork		*forks; //array, ptr to first element
	t_philo		*philos; //array, ptr to first element
	t_mtx		table_mtx;
	t_mtx		write_mtx;
}	t_table;

/* --------------------------------------------------------------------------*/

/* init philo & dinner (simulation) */
int		table_init(t_table *table, char **argv);
int		philo_dinner(t_table *table);
// void	*philo_routine(void *arg);

/* table utils */
void	table_print(t_table *table);
int		is_finished(t_table *table);
int		error_print(const char *error);
void	error_exit(const char *error); //NOT ALLOWED
long	get_time(t_time time_code);
void	precision_usleep(t_table *table, long usec);

/* philo utils */
void	*safe_malloc(size_t bytes);
void	set_bool(t_mtx *mtx, int *dst, int value);
int		get_bool(t_mtx *mtx, int *dst);
void	set_long(t_mtx *mtx, long *dst, long value);
void	add_long(t_mtx *mtx, long *dst, long value_to_add);
long	get_long(t_mtx *mtx, long *dst);
void	write_status(t_philo *philo, t_status status, int debug);

/** routine */
void	set_last_meal_time(t_philo *philo);
void	philo_wait(t_table *table);
void	philo_think(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

/* pthread hanlders */
int		safe_mutex_handle(t_mtx *mutex, t_opthread opthread);
int		safe_thread_handle(pthread_t *thread, void *(*f)(void *), void *data,
	t_opthread opthread);

/* monitor */
void	*philo_monitor(void *data);

/* aux functions*/
long	ft_atolf(char *s, int *flag);

#endif
