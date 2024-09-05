#include "philo.h"
#include <stdint.h> 

// static void single_philo_routine(t_table *table)
// {
// 	t_philo	philo;

// 	philo = table->philos[0];
// 	philo_wait(table->philos);
// 	set_last_meal_time(&philo);
// 	add_long(&(table->table_mtx), &(table->philos_running_nbr), 1);
// 	while (is_finished(table) == 0)
// 	{
// 		if (philo.is_full)
// 			return (NULL);
// 		philo_eat(&philo);
// 		philo
// 	}
// 	return ;
// }

/**
 * If the philo_nbr is even
 */

/**
 * we need to
 * - wait all philos (sinchronization)
 * - endlees loop:
 * 	- check time to die
 * 	- time to eat
 * 	- time to sleep
*/
static void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	//dprintf(STDOUT_FILENO, "\n[philo_routine] [philo_id] %d\n", philo->id);
	philo_wait(philo->table); //synchronize all philos
	//we need to de-syncronize the
	set_last_meal_time(philo);
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
int	philo_dinner(t_table *table)
{
	int		i;
	t_philo	*philo;
	int		*monitor_status;

	//dprintf(STDOUT_FILENO, "\n[dinner_start]\n");
	if (table->meal_limit == 0)
		return (0);
	// if (table->philos_nbr == 1)
	// 	return (single_philo_routine(table));
	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = table->philos + (i * sizeof(t_philo));
		//dprintf(STDOUT_FILENO, "starts routine [philo_id] %d [create thread] ", philo->id);
		if (safe_thread_handle(&(philo->id_thread), philo_routine, philo, NULL, CREATE) < 0)
			return (-1); //error -> might need to clean threads
	}
	//monitor philo's threadds
	if (safe_thread_handle(&(table->monitor), philo_monitor, table, NULL, CREATE) < 0) //<-----
		return (-1);
 	//gettime of dinner start
	table->t_start = get_time(MILLISECOND);
	if (table->t_start < 0)
		return (-1);
	//now all threads are aready, after all are created
	set_bool(&table->table_mtx, &table->is_ready, 1);
	//join
	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = table->philos + (i * sizeof(t_philo));
		if (safe_thread_handle(&(philo->id_thread), NULL, NULL, NULL, JOIN) < 0)
			return (-1);
	}
	//if we manage to reach this point all philos are full
	set_bool(&table->table_mtx, &table->is_finished, 1); //DATARACE
	if (safe_thread_handle(&table->monitor, NULL, NULL, (void *)&monitor_status, JOIN) < 0)
		return (-1);
	//TODO: check monitor_status to check it, monitor checks if a philo has died
	if (monitor_status && (intptr_t)monitor_status < 0)
		return (-1);
	return (0);
}
