#include "philo.h"

static void philo_wait(t_table *table)
{
	while (get_bool(&table->table_mtx, &table->is_ready) == 0)
		;
}

/**
 * we need to
 * - wait all philos (sinchronization)
 * - endlees loop:
 * 	- check time to die
 * 	- time to eat
 * 	- time to sleep
*/
static void *routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	philo_wait(philo->table);

	//set last_meal_time
	
	while (is_finished(table) == 0)
	{
		if (philo->is_full) //THREAD SAFE?
			return (NULL);
		// philo_eat(philo);
		// philo_sleep(philo);
		// philo_think(philo);
	}

	return (NULL);
}

static void single_philosopher(t_table *table)
{
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
	t_philo	philo;

	if (table->meal_limit == 0)
		return ;
	if (table->philo_nbr == 1)
		return (single_philosopher(table));
	i = -1;
	while (++i < table->philo_nbr)
	{
		//create all the threads, when we crete the threads the routine starts
		//we need to sinchronize all threads
		philo = table->philos[i];
		safe_thread_handle(&(philo.id_thread), routine, NULL, CREATE);
	}
	//gettime of dinner start
	table->time_start = get_time(MILLISECOND);
	//now all threads are aready, after all are created
	set_bool(&table->table_mtx, &table->is_ready, 1);
	//join
	i = -1;
	while (++i < table->philo_nbr)
	{
		philo = table->philos[i];
		safe_thread_handle(&(philo.id_thread), NULL, NULL, JOIN);
	}
	//if we manage to reach this point all philos are full

}
