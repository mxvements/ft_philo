/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:18:33 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 19:19:50 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define YLLW "\x1b[33m"
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
typedef pthread_mutex_t	t_mtx;

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
typedef enum e_opthrd
{
	CREATE,
	DETACH,
	JOIN,
	INIT,
	DESTROY,
	LOCK,
	UNLOCK
}	t_opthrd;

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
	t_mtx	fork_mtx;
	int		id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	pthread_t		id_thread;
	t_fork			*first_fork;
	t_fork			*secnd_fork;
	long			meals_count;
	long			t_last_meal;
	int				is_full;
	struct s_table	*table;
	t_mtx			philo_mtx;
}	t_philo;

typedef struct s_table
{
	long		philos_nbr;
	long		philos_running_nbr;
	pthread_t	monitor;
	long		t_start;
	long		t_to_die;
	long		t_to_eat;
	long		t_to_sleep;
	long		meal_limit;
	int			is_finished;
	int			is_ready;
	t_fork		*forks;
	t_philo		*philos;
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
int		is_table_finished(t_table *table);
int		error_print(const char *error);
void	table_free(t_table *table);

/* philo utils */
void	*safe_malloc(size_t bytes);
void	set_bool(t_mtx *mtx, int *dst, int value);
int		get_bool(t_mtx *mtx, int *dst);
void	set_long(t_mtx *mtx, long *dst, long value);
void	add_long(t_mtx *mtx, long *dst, long value_to_add);
long	get_long(t_mtx *mtx, long *dst);
void	write_status(t_philo *philo, t_status status, int debug);
void	de_synchronize_philos(t_philo *philo);

/** routine */
void	philo_wait(t_table *table);
void	philo_think(t_philo *philo, int flag);
void	philo_sleep(t_philo *philo);
void	philo_eat(t_philo *philo);

/* pthread hanlders */
int		safe_mutex(t_mtx *mutex, t_opthrd opthread);
int		safe_thread(pthread_t *thr, void *(*f)(void *), void *data,
			t_opthrd opthr);

/* monitor */
void	*monitor(void *data);

/* aux functions*/
long	ft_atolf(char *s, int *flag);
long	ft_gettime(t_time time_code);
void	ft_usleep(t_table *table, long usec);

#endif
