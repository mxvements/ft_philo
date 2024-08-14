#include "philo.h"

static void	check_parse(int flag, long nbr)
{
	if (flag == 1)
		philo_exit("Integer overflow or invalid number");
	if (nbr < 0)
		philo_exit("Negative number");
}
/**
 * input is given in milliseconds
 * usleep works with microseconds
 * 
 * micro < milli
 * 1 microseconds = 0.001 milliseconds
*/
int	init_table(t_table *table, char **argv)
{	
	int	flag;

	flag = 0;
	table->philo_nbr = ft_atolf(argv[1], &flag);
	check_parse(flag, table->philo_nbr);
	table->time_to_die = ft_atolf(argv[2], &flag);
	check_parse(flag, table->time_to_die);
	table->time_to_eat = ft_atolf(argv[3], &flag);
	check_parse(flag, table->time_to_eat);
	table->time_to_sleep = ft_atolf(argv[4], &flag);
	check_parse(flag, table->time_to_sleep);
	if (argv[5])
	{
		table->meal_limit = ft_atolf(argv[5], &flag);
		check_parse(flag, table->meal_limit);
	}
	return (0);
}

// int init_philo()
// {}