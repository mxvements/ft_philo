#include "philo.h"
static int check_flag(int flag)
{
	if (flag == 0)
		return (0);
	printf("Invalid arguments: long overflow\n");
	return (1);
}
/**
 * TODO: last argument, optinal, in brackets
 */
int init_table(t_table *table, char **argv)
{	
	int	flag;

	flag = 0;
	table->philo_nbr = ft_atolf(argv[1], &flag);
	if (check_flag(flag) == 1)
		return (1);
	table->time_to_die = ft_atolf(argv[2], &flag);
	if (check_flag(flag) == 1)
		return (1);
	table->time_to_eat = ft_atolf(argv[3], &flag);
	if (check_flag(flag) == 1)
		return (1);
	table->time_to_sleep = ft_atolf(argv[4], &flag);
	if (check_flag(flag) == 1)
		return (1);
	return (0);
}

// int init_philo()
// {}