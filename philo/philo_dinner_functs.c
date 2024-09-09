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

void	philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEP, DEBUG);
	ft_usleep(philo->table, philo->table->t_to_sleep);
}

/**
 * grab the forks
 * eat, write eat update last maeal, update last meal counter
 * release the forks
 */
void	philo_eat(t_philo *philo)
{
	//grab forks
	safe_mtx_handle(&philo->first_fork->fork_mtx, LOCK);
	write_status(philo, FRST_FORK, DEBUG);
	safe_mtx_handle(&philo->secnd_fork->fork_mtx, LOCK);
	write_status(philo, SCND_FORK, DEBUG);
	
	//TODO: si los dos no están lockeados...

	//update last meal, update count, eat
	set_last_meal_time(philo);
	philo->meals_count++;
	write_status(philo, EAT, DEBUG);
	ft_usleep(philo->table, philo->table->t_to_eat);
	//is the philo full?, update if true
	if (philo->table->meal_limit > 0 
		&& philo->meals_count == philo->table->meal_limit)
		set_bool(&philo->philo_mtx, &philo->is_full, 1);
	//release forks
	safe_mtx_handle(&philo->first_fork->fork_mtx, UNLOCK);
	safe_mtx_handle(&philo->secnd_fork->fork_mtx, UNLOCK);
}
