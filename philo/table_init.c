#include "philo.h"

/**
 * flag -> checks ft_atolf (int overflow)
 * since we're working with time, no negatives are allowed
 * 
 * TODO: [video] time_to_die, time_to_eat and time_to_sleep should be < 60ms
 */
static void	check_parse(int flag, int min_value, long nbr)
{
	if (flag == 1)
		error_exit("Integer overflow or invalid number");
	if (nbr < 0)
		error_exit("Negative number");
	if (nbr < min_value)
		error_exit("Use timestamps larger than 60ms");
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
	table->philos_nbr = ft_atolf(argv[1], &flag);
	check_parse(flag, 0, table->philos_nbr);
	table->time_to_die = ft_atolf(argv[2], &flag);
	check_parse(flag, 60, table->time_to_die);
	table->time_to_die *= 1e3;
	table->time_to_eat = ft_atolf(argv[3], &flag);
	check_parse(flag, 60, table->time_to_eat);
	table->time_to_eat *= 1e3;
	table->time_to_sleep = ft_atolf(argv[4], &flag);
	check_parse(flag, 60, table->time_to_sleep);
	table->time_to_sleep *= 1e3;
	if (argv[5])
	{
		table->meal_limit = ft_atolf(argv[5], &flag);
		check_parse(flag, 0, table->meal_limit);
	}
	else
		table->meal_limit = -1;
}

static void forks_init(t_table *table)
{
	int	i;
	t_fork *fork;

	dprintf(STDOUT_FILENO, "\n[phorks_init]\n");
	i = -1;
	while (++i < table->philos_nbr)
	{
		fork = table->forks + (i * sizeof(t_fork));
		table->forks[i].fork_id = i;

		dprintf(STDOUT_FILENO, "[fork_id] %d [mutex init, fork] ", table->forks[i].fork_id);
		safe_mutex_handle(&fork->fork, INIT);
	}
}
/**
 * assing forks, 
 * 	all even philos pick 'even' fork first, there's a modulus 4the circularity
 * 	all odd philos pick 'odd' fork first
 */
static void	philos_init(t_table *table)
{
	int	i;
	t_philo *philo;

	i = -1;
	dprintf(STDOUT_FILENO, "\n[philos_init]\n");
	while (++i < table->philos_nbr)
	{
		philo = table->philos + (i * sizeof(t_philo));
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->is_full = 0;//false
		philo->last_meal_time = 0;
		philo->table = table;

		dprintf(STDOUT_FILENO, "[philo_id] %d [mutex init, philo_mtx] ", philo->id);
		safe_mutex_handle(&philo->philo_mtx, INIT);
		
		if (philo->id % 2)
		{
			philo->first_fork = &table->forks[(i + 1) % table->philos_nbr];
			philo->secnd_fork = &table->forks[i];
		}
		else
		{
			philo->first_fork = &table->forks[i];
			philo->secnd_fork = &table->forks[(i + 1) % table->philos_nbr];
		}
	}
}

int	table_init(t_table *table, char **argv)
{	
	dprintf(STDOUT_FILENO, "\n[table_init]\n");
	parse_input(table, argv);
	table->is_finished = 0; //false
	table->is_ready = 0; //false
	table->philos = safe_malloc(table->philos_nbr * sizeof(t_philo)); //array of philos
	table->forks = safe_malloc(table->philos_nbr * sizeof(t_fork)); //array of forks
	table->philos_running_nbr = 0;

	dprintf(STDOUT_FILENO, "[mutex init, table_mtx]\t");
	safe_mutex_handle(&table->table_mtx, INIT); //thread to monitor table
	
	dprintf(STDOUT_FILENO, "[mutex init, write_mtx]\t");
	safe_mutex_handle(&table->write_mtx, INIT);
	
	forks_init(table);
	philos_init(table);
	return (0);
}
