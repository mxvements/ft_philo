#include "philo.h"

static void philo_wait(t_table *table)
{
	while (get_bool(&table->table_mtx, &table->is_ready) == 0)
		;
}
//TODO
static void	philo_think(t_philo *philo)
{
	write_status(philo, THINK, DEBUG);
}

static void philo_sleep(t_philo *philo)
{
	write_status(philo, SLEEP, DEBUG);
	precision_usleep(philo->table, philo->table->time_to_sleep);
}

/**
 * grab the forks
 * eat, write eat update last maeal, update last meal counter
 * release the forks
 */
static void	philo_eat(t_philo *philo)
{
	//grab forks
	safe_mutex_handle(&philo->first_fork->fork, LOCK);
	write_status(philo, FRST_FORK, DEBUG);
	safe_mutex_handle(&philo->secnd_fork->fork, LOCK);
	write_status(philo, SCND_FORK, DEBUG);
	//eat, update last meal, update count
	set_long(&philo->philo_mtx, &philo->last_meal_time, get_time(MILLISECOND));
	philo->meals_count++;
	write_status(philo, EAT, DEBUG);
	precision_usleep(philo->table, philo->table->time_to_eat);
	//is the philo full?, update if true
	if (philo->table->meal_limit > 0 && philo->meals_count == philo->table->meal_limit)
		set_bool(&philo->philo_mtx, &philo->is_full, 1);
	//release forks
	safe_mutex_handle(&philo->first_fork->fork, UNLOCK);
	safe_mutex_handle(&philo->secnd_fork->fork, UNLOCK);
}

/**
 * we need to
 * - wait all philos (sinchronization)
 * - endlees loop:
 * 	- check time to die
 * 	- time to eat
 * 	- time to sleep
*/
void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	dprintf(STDOUT_FILENO, "\n[philo_routine] [philo_id] %d\n", philo->id);
	philo_wait(philo->table);

	//increase the philo_running nbr
	add_long(&(table->table_mtx), &(table->philos_running_nbr), 1);
	
	while (is_finished(table) == 0)
	{
		if (philo->is_full) //THREAD SAFE?
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}

	return (NULL);
}
