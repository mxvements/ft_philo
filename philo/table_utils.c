/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:05:23 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/26 20:49:23 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_table_finished(t_table *table)
{
	return (get_bool(&table->table_mtx, &table->is_finished));
}

int	error_print(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	return (-1);
}

/** t_table struct:
 * typedef struct s_table
	{
		long		philos_nbr;
		long		philos_running_nbr;
		pthread_t	monitor;
		long		t_start;
		long		t_to_die;
		long		t_to_eat;
		long		t_to_sleep;
		long		meal_limit;
		int			is_finished; 
		int			is_ready;
		t_fork		*forks;
		t_philo		*philos;
		t_mtx		table_mtx;
		t_mtx		write_mtx;
	}	
 */
void	table_print(t_table *table)
{
	printf("[table]\n");
	if (table->philos_nbr)
		printf("table->philo_nbr:\t%li\n", table->philos_nbr);
	if (table->t_to_die)
		printf("table->time_to_die:\t%li\n", table->t_to_die);
	if (table->t_to_eat)
		printf("table->time_to_eat:\t%li\n", table->t_to_eat);
	if (table->t_to_sleep)
		printf("table->time_to_sleep:\t%li\n", table->t_to_sleep);
	if (table->meal_limit)
		printf("table->meal_limit:\t%li\n", table->meal_limit);
	if (table->t_start)
		printf("table->time_start:v%li\n", table->t_start);
	if (table->is_finished)
		printf("table->end_flag:\t%i\n", table->is_finished);
}
