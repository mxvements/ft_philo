#include "philo.h"

static void forks_free(t_table *table)
{
	t_fork	*fork;
	int		i;

	i = -1;
	while (++i < table->philos_nbr)
	{
		fork = table->forks + (i * sizeof(t_fork));
		safe_mtx_handle(&(fork->fork_mtx), DESTROY); //do not protect
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
		memset(table->philos, 0, sizeof(t_philo) * table->philos_nbr); //clean mem space of the array
		table->philos = NULL;
	}
	if (table->forks)
	{
		forks_free(table); //DUDAS
		memset(table->forks, 0, sizeof(t_table) * table->philos_nbr); //clean mem space of the array
		table->forks = NULL;
	}
	//free(table);
}
