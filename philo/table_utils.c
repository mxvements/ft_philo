#include "philo.h"

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
	if (table->philo_nbr)
		printf("table->philo_nbr:\t%li\n", table->philo_nbr);
	if (table->time_to_die)
		printf("table->time_to_die:\t%li\n", table->time_to_die);
	if (table->time_to_eat)
		printf("table->time_to_eat:\t%li\n", table->time_to_eat);
	if (table->time_to_sleep)
		printf("table->time_to_sleep:\t%li\n", table->time_to_sleep);
	if (table->meal_limit)
		printf("table->meal_limit:\t%li\n", table->meal_limit);
	if (table->time_start)
		printf("table->time_start:v%li\n", table->time_start);
	if (table->is_end)
		printf("table->end_flag:\t%i\n", table->is_end);	
}

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
	if (table->forks)
		forks_free(&(table->forks)); //those are the mutex
	// if (table->philos)
	// 	philos_free(&(table->philos));
}