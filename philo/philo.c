#include "philo.h"

/**
 * 	use example
 *  ./philo 5 800 200 200 [5]
 * 
 * 	arguments:
 * 	number_of_philosophers
 * 	time_to_die (ms)
 * 	time_to_eat (ms)
 * 	time_to_sleep (ms)
 * 	number_of_imes_each_philosopher_must_eat (optional)
 */
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		error_exit("Invalid number of arguments\
		\nExample: ./philo 5 800 200 200 (5)");
	//set table
	memset((void *)&table, 0, sizeof(t_table)); //ft_bzero
	table_init(&table, argv);
	table_print(&table);
	//start dinner
	philo_dinner(&table);
	//clean (forks and philos from table)
	return (0);
}
