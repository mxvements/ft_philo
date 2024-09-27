/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:06:26 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 19:01:19 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Make the system Fair
 * TODO: explain why this function is needed
 */
void	de_synchronize_philos(t_philo *philo)
{
	if (((t_table *)philo->table)->philos_nbr % 2 == 0 && philo->id % 2 == 0)
		ft_usleep(philo->table, 3e4);
	else
	{
		if (philo->id % 2 == 0)
			philo_think(philo, 1);
	}
}

void	*safe_malloc(size_t bytes)
{
	void	*rslt;

	rslt = malloc(bytes);
	if (!rslt)
	{
		error_print("Malloc error");
		return (NULL);
	}
	return (rslt);
}

static void	write_status_debug(t_philo *philo, t_status status, long elapsed)
{
	t_table	*table;

	table = philo->table;
	if (status == FRST_FORK && is_table_finished(table) == 0)
		printf(YLLW"%-6ld %d has taken the 1st fork [%d]\n"RESET, elapsed,
			philo->id, philo->first_fork->id);
	else if (status == SCND_FORK && is_table_finished(table) == 0)
		printf(YLLW"%-6ld %d has taken the 2nd fork [%d]\n"RESET, elapsed,
			philo->id, philo->secnd_fork->id);
	else if (status == EAT && is_table_finished(table) == 0)
		printf(GREEN"%-6ld %d is eating [count: %ld]\n"RESET, elapsed,
			philo->id, philo->meals_count);
	else if (status == SLEEP && is_table_finished(table) == 0)
		printf(CYAN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINK && is_table_finished(table) == 0)
		printf(GRAY"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIE)
		printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
}

/**
 * Output format:
 * 		[time_millisec] [philo_id] [action]
 */
void	write_status(t_philo *philo, t_status status, int debug)
{
	t_table	*table;
	long	elapsed;

	table = philo->table;
	elapsed = ft_gettime(MILLISECOND) - ((t_table *)philo->table)->t_start;
	if (get_bool(&philo->philo_mtx, &philo->is_full) == 1)
		return ;
	safe_mutex(&table->write_mtx, LOCK);
	if (debug)
		write_status_debug(philo, status, elapsed);
	else
	{
		if ((status == FRST_FORK || status == SCND_FORK)
			&& is_table_finished(table) == 0)
			printf(YLLW"%-6ld %d has taken a fork\n"RESET, elapsed, philo->id);
		else if (status == EAT && is_table_finished(table) == 0)
			printf(ORANGE"%-6ld %d is eating\n"RESET, elapsed, philo->id);
		else if (status == SLEEP && is_table_finished(table) == 0)
			printf(CYAN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
		else if (status == THINK && is_table_finished(table) == 0)
			printf(GREEN"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
		else if (status == DIE)
			printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
	}
	safe_mutex(&table->write_mtx, UNLOCK);
}
