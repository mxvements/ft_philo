/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:15:59 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 18:49:55 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>

/**
 * Philo routine logic:
 *
 * 1 - Before the exercise routine
 * 		wait until all threads are ready
 * 		update t_last_meal
 * 		update philo_running_nbr -> check how many are already on the routine
 * 		de_synchronize_philos ->
 * 		check any philo needs to start thinking (ft_usleep) without the status
 *
 * 2 - eat, sleep, think
 * 		while nobody has finished (in case of meal_limit)
 * 		* this is where the infinite loop of the philos happens
 * 		(table->is-finished) only gets updated when a philo dies or they're full
 */
static void	*routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	philo_wait(philo->table);
	set_long(&philo->philo_mtx, &philo->t_last_meal, ft_gettime(MILLISECOND));
	add_long(&(table->table_mtx), &(table->philos_running_nbr), 1);
	de_synchronize_philos(philo);
	while (is_table_finished(table) == 0)
	{
		if (get_bool(&philo->philo_mtx, &philo->is_full) == 1)
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo, 0);
	}
	return (NULL);
}

static int	philos_launch(t_table *table)
{
	int		i;
	int		j;
	t_philo	*philo;

	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = &(table->philos[i]);
		if (safe_thread(&(philo->id_thread), routine, philo, CREATE) < 0)
		{
			j = -1;
			while (++j < i)
			{
				philo = &(table->philos[j]);
				safe_thread(&(philo->id_thread), NULL, NULL, DETACH);
			}
			return (-1);
		}
	}
	return (0);
}

static int	philos_join(t_table *table)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = &(table->philos[i]);
		if (safe_thread(&(philo->id_thread), NULL, NULL, JOIN) < 0)
			return (-1);
	}
	return (0);
}

/**
 * Dinner logic:
 *
 * - launch monitor thread
 * - launch each philo thread
 * - set time of dinner start
 * - set is ready bool
 * 			now is when all philos do their routine until the monitor founds
 * 			someone dead
 * - join philos (terminate all threads)
 * - join monitor -> get the return value (status, check if there were errors)
 */
int	philo_dinner(t_table *table)
{
	int		*status;

	status = NULL;
	if (table->meal_limit == 0)
		return (0);
	if (safe_thread(&(table->monitor), monitor, table, CREATE) < 0)
		return (-1);
	if (philos_launch(table) < 0)
		return (-1);
	table->t_start = ft_gettime(MILLISECOND);
	if (table->t_start < 0)
		return (-1);
	set_bool(&table->table_mtx, &table->is_ready, 1);
	if (philos_join(table) < 0)
		return (-1);
	set_bool(&table->table_mtx, &table->is_finished, 1);
	if (safe_thread(&table->monitor, NULL, (void *)&status, JOIN) < 0)
		return (-1);
	if (status && (intptr_t)status < 0)
		return (-1);
	return (0);
}
