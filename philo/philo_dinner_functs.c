/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner_functs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:15:57 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 18:21:38 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * Logic of waiting
 * 
 * before starting the main routine (eat, sleep, think), all philos' threads
 * must be initialized so they are kind of synchronized
 * 
 * spinlock (loop) until the table is ready (value changed on dinner funct, after
 * creating all threads)
 */
void	philo_wait(t_table *table)
{
	while (get_bool(&table->table_mtx, &table->is_ready) == 0)
		;
}

/**
 * @param flag, to know if need to write the think status of the philo
 * 
 * Logic of thinking:
 * 
 * 1 - write the status of the philo if needed (if this function is called 
 * from the routine function)
 * 
 * 2 - ft_usleep for a time that is calculated so the systems if fair (all
 * philos think in the routine cycle):
 * 		case of philos_nbr is EVEN -> 
 * 			we do not need this system, all philos regulate themselves
 *		case of philos_nbr is ODD ->
			we think (0.42 * ((t_eat * 2) - t_sleep))
			the 0.42 it's just a magic number, a way we force all philos to 
			sleep at least a little time, then they regulate themselves
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
	t_eat = philo->table->t_to_eat;
	t_sleep = philo->table->t_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(philo->table, t_think * 0.21);
}

/**
 * Logic of sleeping:
 * 
 * write te status of sleeps
 * ft_usleep to wait until the t_to_sleep is done
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
	safe_mutex(&philo->first_fork->fork_mtx, LOCK);
	write_status(philo, FRST_FORK, DEBUG);
	safe_mutex(&philo->secnd_fork->fork_mtx, LOCK);
	write_status(philo, SCND_FORK, DEBUG);
	set_long(&philo->philo_mtx, &philo->t_last_meal, ft_gettime(MILLISECOND));
	philo->meals_count++;
	write_status(philo, EAT, DEBUG);
	ft_usleep(philo->table, philo->table->t_to_eat);
	if (philo->table->meal_limit > 0
		&& philo->meals_count == philo->table->meal_limit)
		set_bool(&philo->philo_mtx, &philo->is_full, 1);
	safe_mutex(&philo->first_fork->fork_mtx, UNLOCK);
	safe_mutex(&philo->secnd_fork->fork_mtx, UNLOCK);
}
