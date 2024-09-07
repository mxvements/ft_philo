#include "philo.h"

void	set_last_meal_time(t_philo *philo)
{
	set_long(&philo->philo_mtx, &philo->t_last_meal, get_time(MILLISECOND));
}

void	philo_wait(t_table *table)
{
	while (get_bool(&table->table_mtx, &table->is_ready) == 0)
		;
}

void	philo_think(t_philo *philo)
{
	// long	t_eat;
	// long	t_sleep;
	// long	t_think;

	write_status(philo, THINK, DEBUG);
	// if (philo->table->philos_nbr % 2 == 0 && philo->id % 2 == 0)
	// 	return ;
	// if (philo->table->philos_nbr % 2 != 0 && philo->id % 2 == 0)
	// 	return ;
	// t_eat = philo->table->t_to_eat;
	// t_sleep = philo->table->t_to_sleep;
	// t_think = (t_eat * 2) - t_sleep;
	// if (t_think < 0)
	// 	t_think = 0;
	// precision_usleep(philo->table, t_think * 0.42); //think some time, make the sys
}

void	philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEP, DEBUG);
	precision_usleep(philo->table, philo->table->t_to_sleep);
}

/**
 * grab the forks
 * eat, write eat update last maeal, update last meal counter
 * release the forks
 */
void	philo_eat(t_philo *philo)
{
	//grab forks
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, FRST_FORK, DEBUG);
	safe_mutex_handle(&philo->secnd_fork->fork, LOCK);
	write_status(philo, SCND_FORK, DEBUG);
	
	//TODO: si los dos no están lockeados...

	//update last meal, update count, eat
	set_last_meal_time(philo);
	philo->meals_count++;
	write_status(philo, EAT, DEBUG);
	precision_usleep(philo->table, philo->table->t_to_eat);
	//is the philo full?, update if true
	if (philo->table->meal_limit > 0 
		&& philo->meals_count == philo->table->meal_limit)
		set_bool(&philo->philo_mtx, &philo->is_full, 1);
	//release forks
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->secnd_fork->fork, UNLOCK);
}
