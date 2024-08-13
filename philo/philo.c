
#include "philo.h"

static int err_arguments(void)
{
	printf("Invaid number of arguments\n");
	printf("Use exmapl: ./philo 5 800 200 200 [5]\n");
	return (1);
}
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
	t_table table;

	if (argc < 5 || argc > 6 )
		return (err_arguments());

	memset((void *)&table, 0, sizeof(t_table)); //ft_bzero
	init_table(&table, argv);
	// init_philo();
	return (0);
}
