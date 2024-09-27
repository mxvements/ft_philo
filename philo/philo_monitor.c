/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:52:35 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 19:36:24 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Checks if philos_running == philos_nbr,
 * philos_running_nbr is updated on philo_routine
 *
 * Returns
 * 		0	-> OK
 * 		-1	-> mutex handle error
 */
static int	are_all_philos_running(t_table *table)
{
	int	rslt;

	rslt = 0;
	if (safe_mutex(&(table->table_mtx), LOCK) < 0)
		return (-1);
	if (table->philos_running_nbr == table->philos_nbr)
		rslt = 1;
	if (safe_mutex(&(table->table_mtx), UNLOCK) < 0)
		return (-1);
	return (rslt);
}

static int	is_philo_dead(t_philo *philo)
{
	long	t_last_meal;
	long	elapsed;
	long	t_to_die;

	if (get_bool(&(philo->philo_mtx), &(philo->is_full)) == 1)
		return (0);
	t_last_meal = get_long(&(philo->philo_mtx), &(philo->t_last_meal));
	elapsed = ft_gettime(MILLISECOND) - (t_last_meal);
	t_to_die = (((t_table *)(philo->table))->t_to_die) / 1e3;
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

/**
 * Conditions for the dinner to be running:
 * - All philos alive
 * - Dinner not finished (variable updated on dinner funct)
 * 
 * If a philo dies, then we update that variable
 */
static int	is_dinner_running(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philos_nbr && is_table_finished(table) == 0)
	{
		philo = &(table->philos[i]);
		if (is_philo_dead(philo) == 1)
		{
			set_bool(&(table->table_mtx), &(table->is_finished), 1);
			write_status(philo, DIE, DEBUG);
			return (-1);
		}
	}
	return (0);
}

/**
 * Monitor logic
 *
 * 1 - Spinlock until all philos are running their routine
 * 2 - Checks if a philo must die while dinner isn't finished
 *
 */
void	*monitor(void *data)
{
	int		status;
	t_table	*table;

	table = data;
	status = are_all_philos_running(table);
	while (status == 0)
	{
		status = are_all_philos_running(table);
		if (status < 0)
			return ((void *)-1);
	}
	while (is_table_finished(table) == 0)
	{
		if (is_dinner_running(table) < 0)
			return ((void *)0);
	}
	return (NULL);
}
