/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:06:07 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 19:14:56 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_freenull(void **data)
{
	free(*data);
	*data = NULL;
}

static void	table_mtx_destroy(t_table *table)
{
	int		i;
	t_philo	*philo;
	t_fork	*fork;

	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = &(table->philos[i]);
		if (philo->id > 0 && safe_mutex(&philo->philo_mtx, DESTROY) < 0)
			error_print("Error destroying philo_mtx");
		fork = &(table->forks[i]);
		if (fork->id >= 0 && safe_mutex(&fork->fork_mtx, DESTROY) < 0)
			error_print("Error destroying fork_mtx");
	}
	if (safe_mutex(&table->table_mtx, DESTROY) < 0)
		error_print("Error destroying table_mtx");
	if (safe_mutex(&table->write_mtx, DESTROY) < 0)
		error_print("Error destroying write_mtx");
}

/**
 * free ptr on struct
 * no malloc on ptr to table, so no need to free that ptr
 */
void	table_free(t_table *table)
{
	table_mtx_destroy(table);
	if (table->forks)
		ft_freenull((void **)&table->forks);
	if (table->philos)
		ft_freenull((void **)&table->philos);
	return ;
}
