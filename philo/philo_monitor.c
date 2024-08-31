#include "philo.h"

static int are_all_philos_running(t_table *table)
{
	int	rslt;

	rslt = 0;
	safe_mutex_handle(&(table->table_mtx), LOCK);
	if (table->philos_running_nbr == table->philos_nbr)
		rslt = 1;
	safe_mutex_handle(&(table->table_mtx), UNLOCK);
	return (rslt);
}


static int philo_died(t_philo *philo)
{
	long	t_last_meal;
	long	elapsed;
	long	t_to_die;

	if (get_bool(&(philo->philo_mtx), &(philo->is_full)) == 1)
		return (0);
	t_last_meal = get_long(&(philo->philo_mtx), &(philo->t_last_meal)); //MILLISECONDS
	elapsed = get_time(MILLISECOND) - (t_last_meal);
	//convert back to millisecond
	t_to_die = (((t_table *)(philo->table))->t_to_die)/1e3;	
	if (elapsed > t_to_die)
		return (1);
	return (0);
}

void	*philo_monitor(void *data)
{
	t_table *table;
	t_philo	*philo;
	int		i;

	table = data;
	//make sure all philos running, spinlock until all threads are running
	while (are_all_philos_running(table) == 0)
		;
	while (is_finished(table) == 0)
	{
		i = -1;
		while (++i < table->philos_nbr
			&& get_bool(&table->table_mtx, &table->is_finished) == 0)
		{
			philo = table->philos + (i * sizeof(t_philo));
			if (philo_died(philo) == 1)
			{
				set_bool(&(table->table_mtx), &(table->is_finished), 1);
				write_status(philo, DIE, DEBUG);
				exit(0);
			}
		}
	}
	return (NULL);
}
