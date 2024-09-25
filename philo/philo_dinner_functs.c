/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner_functs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:15:57 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/25 21:25:02 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_last_meal_time(t_philo *philo)
{
	set_long(&philo->philo_mtx, &philo->t_last_meal, ft_gettime(MILLISECOND));
}

void	philo_wait(t_table *table)
{
	while (get_bool(&table->table_mtx, &table->is_ready) == 0)
		;
}

/**
 * Logic of thinking:
 * 
 */
void	philo_think(t_philo *philo, int flag)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (flag == 0)
		write_status(philo, THINK, DEBUG);
	if (philo->table->philos_nbr % 2 == 0)
		return ;
	// if (philo->table->philos_nbr % 2 == 0 && philo->id % 2 == 0)
		// return ; //can we put the ft_usleep here?
	// if (philo->table->philos_nbr % 2 != 0 && philo->id % 2 == 0)
		// return ;
	t_eat = philo->table->t_to_eat;
	t_sleep = philo->table->t_to_sleep;
	t_think = (t_eat * 2) - t_sleep;  //formula
	if (t_think < 0)
		t_think = 0;
	ft_usleep(philo->table, t_think * 0.42); //think some time, make the system Fair
}

/**
 * Logic of sleeping:
 * 
 */
void	philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEP, DEBUG);
	ft_usleep(philo->table, philo->table->t_to_sleep);
}

/** 
 * Logic of eating:
 * 
 * 1 - grab the forks
 * 		lock the mutex of the forks
 * 		write the status of grabbing the forks
 * 2 - eat, write eat update last meal, update last meal counter
 * 		meal_count++
 * 		set_last_meak_time to the current time
 * 		write -> philo is eating
 * 		usleep t_to_eat
 * 		if there's meal_limit -> check if the philo is full
 * 3 - release the forks
 * 		unlock the mutex of the forks
 */
void	philo_eat(t_philo *philo)
{
	safe_mtx_handle(&philo->first_fork->fork_mtx, LOCK);
	write_status(philo, FRST_FORK, DEBUG);
	safe_mtx_handle(&philo->secnd_fork->fork_mtx, LOCK);
	write_status(philo, SCND_FORK, DEBUG);
	set_last_meal_time(philo);
	philo->meals_count++;
	write_status(philo, EAT, DEBUG);
	ft_usleep(philo->table, philo->table->t_to_eat);
	if (philo->table->meal_limit > 0 
		&& philo->meals_count == philo->table->meal_limit)
		set_bool(&philo->philo_mtx, &philo->is_full, 1);
	safe_mtx_handle(&philo->first_fork->fork_mtx, UNLOCK);
	safe_mtx_handle(&philo->secnd_fork->fork_mtx, UNLOCK);
}
