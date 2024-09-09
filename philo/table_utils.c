#include "philo.h"

int	is_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->is_finished));
}


int	error_print(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	return (-1);
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
