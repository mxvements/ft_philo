
#include "philo.h"

/**
 * long philo_nbr
 * long time_to_die
 * long time_to_eat
 * long time_to_sleep
 * long	meal_limit
 * 
 */
void	print_table(t_table *table)
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
	if (table->end_flag)
		printf("table->end_flag:\t%i\n", table->end_flag);
}
