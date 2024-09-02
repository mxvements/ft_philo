#include "philo.h"

int	is_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->is_finished));
}
/**
 * using gettimeofday
 * t_time -> SECOND; MILLISECOND; MICROSECOND
 * 
 */
long	get_time(t_time time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (error_print("Failure on gettimeofday"));
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		return (error_print("Wrong time_code on get_time"));
	return (0);
}

int	error_print(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	return (-1);
}

/* exit not allowed*/
void	error_exit(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	exit(EXIT_FAILURE);
}
/**
 * only using usleep when reaching a thereshold
 * usec (microseconds) < 1000
 */
void	precision_usleep(t_table *table, long micro_s)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECOND);
	while ((get_time(MICROSECOND) - start) < micro_s )
	{
		if (is_finished(table) == 1)
			break ;
		elapsed = get_time(MICROSECOND) - start;
		remaining = micro_s - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while ((get_time(MICROSECOND) - start) < micro_s)
				;
		}
	}
}

/** t_table struct:
 * 
 * long philo_nbr
 * long time_to_die
 * long time_to_eat
 * long time_to_sleep
 * long	meal_limit
 * long time_start
 * int end_flag
 * t_fork *forks
 * t_phio *philos
 */
void	table_print(t_table *table)
{
	printf("[table]\n");
	if (table->philos_nbr)
		printf("table->philo_nbr:\t%li\n", table->philos_nbr);
	if (table->t_to_die)
		printf("table->time_to_die:\t%li\n", table->t_to_die);
	if (table->t_to_eat)
		printf("table->time_to_eat:\t%li\n", table->t_to_eat);
	if (table->t_to_sleep)
		printf("table->time_to_sleep:\t%li\n", table->t_to_sleep);
	if (table->meal_limit)
		printf("table->meal_limit:\t%li\n", table->meal_limit);
	if (table->t_start)
		printf("table->time_start:v%li\n", table->t_start);
	if (table->is_finished)
		printf("table->end_flag:\t%i\n", table->is_finished);	
}

/* ------------------------------------------------------------------------- */

static void forks_free(t_fork **fork)
{
	free(*fork);
	(*fork) = NULL;
}

// static void philos_free(t_philo **philos)
// {
// 	if (*(philos->left_fork))
// 		free(*(philos->left_fork));
// 	if (*(philos->right_fork))
// 		free(*(philos->right_fork));
// }

/**
 * free ptr on struct
 * no malloc on ptr to table, so no need to free that ptr
 */
void	table_free(t_table *table)
{
	/* WE NEED TO DESTOY ALL PHILOS MUTEX
		AND THE TABLE MUTEXes
		and then free the mallocs
	*/
	if (table->forks)
		forks_free(&(table->forks)); //those are the mutex
	// if (table->philos)
	// 	philos_free(&(table->philos));
}
