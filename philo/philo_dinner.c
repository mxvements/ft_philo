#include "philo.h"

static void single_philo(t_table *table)
{
	(void)table;
	return ;//TODO
}


/**
 * use example
 * ./philo 5 800 200 200 (5)
 * 
 * 		- If no meals -> return (0)
 * 		- If only 1 philo -> adhoc function
 * 
 * 		- Create all threads (all philos)
 * 		- Create a monitor thread -> search for dead philos
 * 		- Syncronize the beginning of the simulation
 * 		- Join everyone
*/
void	philo_dinner(t_table *table)
{
	int		i;
	t_philo	*philo;

	dprintf(STDOUT_FILENO, "\n[dinner_start]\n");
	if (table->meal_limit == 0)
		return ;
	if (table->philos_nbr == 1)
		return (single_philo(table));
	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = table->philos + (i * sizeof(t_philo));
		dprintf(STDOUT_FILENO, "starts routine [philo_id] %d [create thread] ", philo->id);
		safe_thread_handle(&(philo->id_thread), philo_routine, philo, CREATE);
	}
	//monitor philo's threadds
	safe_thread_handle(&(table->monitor), philo_monitor, table, CREATE);
	//gettime of dinner start
	table->time_start = get_time(MILLISECOND);
	//now all threads are aready, after all are created
	set_bool(&table->table_mtx, &table->is_ready, 1);
	//join
	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = table->philos + (i * sizeof(t_philo));
		safe_thread_handle(&(philo->id_thread), NULL, NULL, JOIN);
	}
	//if we manage to reach this point all philos are full

}
