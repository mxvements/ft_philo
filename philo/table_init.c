/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:15:19 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 19:18:09 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	convert_parse(long *data, char **argv, int argidx)
{
	int			flag;
	const int	t_min = 0;

	flag = 0;
	*data = ft_atolf(argv[argidx], &flag);
	if (flag == 1)
		return (error_print("Integer overflow or invalid number"));
	if (*data < 0)
		return (error_print("Negative number"));
	if (*data < t_min)
		return (error_print("Use timestamps larger than 60ms"));
	return (0);
}

/**
 * input is given in milliseconds
 * usleep works with microseconds
 * 
 * micro < milli
 * 1 microseconds = 0.001 milliseconds
*/
static int	parse_input(t_table *table, char **argv)
{
	if (convert_parse(&(table->philos_nbr), argv, 1) < 0)
		return (-1);
	if (convert_parse(&(table->t_to_die), argv, 2) < 0)
		return (-1);
	table->t_to_die *= 1e3;
	if (convert_parse(&(table->t_to_eat), argv, 3) < 0)
		return (-1);
	table->t_to_eat *= 1e3;
	if (convert_parse(&(table->t_to_sleep), argv, 4) < 0)
		return (-1);
	table->t_to_sleep *= 1e3;
	if (argv[5])
	{
		if (convert_parse(&(table->meal_limit), argv, 5) < 0)
			return (-1);
	}
	else
		table->meal_limit = -1;
	return (0);
}

static int	forks_init(t_table *table)
{
	int		i;
	t_fork	*fork;

	i = -1;
	while (++i < table->philos_nbr)
	{
		fork = &(table->forks[i]);
		table->forks[i].id = i;
		if (safe_mutex(&(fork->fork_mtx), INIT) < 0)
			return (error_print("Error on fork init"));
	}
	return (0);
}

/**
 * assing forks, 
 * 	all even philos pick 'even' fork first, there's a modulus 4the circularity
 * 	all odd philos pick 'odd' fork first
 */
static void	philos_init(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = &(table->philos[i]);
		philo->id = i + 1;
		philo->meals_count = 0;
		philo->is_full = 0;
		philo->t_last_meal = 0;
		philo->table = table;
		safe_mutex(&philo->philo_mtx, INIT);
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
	if (parse_input(table, argv) < 0)
		return (-1);
	table->is_finished = 0;
	table->is_ready = 0;
	table->philos_running_nbr = 0;
	table->philos = safe_malloc((table->philos_nbr) * sizeof(t_philo));
	if (!table->philos)
		return (-1);
	table->forks = safe_malloc((table->philos_nbr) * sizeof(t_fork));
	if (!table->forks)
		return (-1);
	if (safe_mutex(&table->table_mtx, INIT) < 0)
		return (-1);
	if (safe_mutex(&table->write_mtx, INIT) < 0)
		return (-1);
	forks_init(table);
	philos_init(table);
	return (0);
}
