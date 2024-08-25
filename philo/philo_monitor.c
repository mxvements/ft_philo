#include "philo.h"

static int are_all_philos_running(t_table *table)
{
	int	rslt;
	int	i;

	rslt = 0;
	safe_mutex_handle(&(table->table_mtx), LOCK);
	if (table->philos_running_nbr == table->philos_nbr)
		rslt = 1;
	safe_mutex_handle(&(table->table_mtx), UNLOCK);
	return (rslt);
}

/** TODO:
 * Check last meal time
 */
static int philo_died(t_philo *philo)
{

}

void	*philo_monitor(void *data)
{
	t_table *table;
	t_philo	*philo;

	table = data;
	//make sure all philos running, spinlock until all threads are running
	while (are_all_philos_running(table) == 0)
		;
	while (is_finished(table) == 0)
	{
		i = -1;
		while (++i < table->philos_nbr && table->is_finished == 0)
		{
			philo = table->philos + (i * sizeof(t_philo));
			if (philo_died(philo) == 1)
			{
				set_bool(&(table->table_mtx), &(table->is_finished), 1);
				write_status(philo, DIE, DEBUG);
			}
		}
	}
	return (NULL);
}
