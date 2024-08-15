#include "philo.h"

/**
 * flag -> checks ft_atolf
 * since we're working with time, no negatives are allowed
 * 
 * TODO: [video] time_to_die, time_to_eat and time_to_sleep should be < 60ms
 */
static void	check_parse(int flag, long nbr)
{
	if (flag == 1)
		philo_exit("Integer overflow or invalid number");
	if (nbr < 0)
		philo_exit("Negative number");
	if (nbr < 60)
		philo_exit("Use timestamps larger than 60ms");
}
/**
 * input is given in milliseconds
 * usleep works with microseconds
 * 
 * micro < milli
 * 1 microseconds = 0.001 milliseconds
*/
static void	parse_input(t_table *table, char **argv)
{
	int	flag;

	flag = 0;
	table->philo_nbr = ft_atolf(argv[1], &flag);
	check_parse(flag, table->philo_nbr);
	table->philo_nbr *= 1e3;
	table->time_to_die = ft_atolf(argv[2], &flag);
	check_parse(flag, table->time_to_die);
	table->time_to_die *= 1e3;
	table->time_to_eat = ft_atolf(argv[3], &flag);
	check_parse(flag, table->time_to_eat);
	table->time_to_eat *= 1e3;
	table->time_to_sleep = ft_atolf(argv[4], &flag);
	check_parse(flag, table->time_to_sleep);
	table->time_to_sleep *= 1e3;
	if (argv[5])
	{
		table->meal_limit = ft_atolf(argv[5], &flag);
		check_parse(flag, table->meal_limit);
	}
	else
		table->meal_limit = -1;
}

static init_forks_philos(t_table *table)
{
	table->end_flag = 0; //false
	table->philos = safe_malloc(table->philo_nbr * sizeof(t_philo));

}
int	init_table(t_table *table, char **argv)
{	
	//1 parse_input
	parse_input(table, argv);
	//2	forks and philos
	init_forks_philos(table);

	//3 start dinner

	//4 clean (forks and philos)

	return (0);
}

// int init_philo()
// {}