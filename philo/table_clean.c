#include "philo.h"

static void forks_free(t_table *table)
{
	t_fork	*fork;
	int		i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		fork = table->forks + (i * sizeof(t_fork));
		safe_mutex_handle(fork, DESTROY); //????
	}
	free(table->forks);
}
/**
 * only the forks struct need to be freed
 * philos have ptrs to forks and table, which are freed outside
 */
void	table_clean(t_table *table)
{
	if (table->philos)
	{
		memset(table->philos, 0, sizeof(t_philo) * table->philo_nbr); //clean mem space of the array
		table->philos = NULL;
	}
	if (table->forks)
	{
		forks_free(table);
		memset(table->forks, 0, sizeof(t_table) * table->philo_nbr); //clean mem space of the array
		table->forks = NULL;
	}
	//free(table);
}
