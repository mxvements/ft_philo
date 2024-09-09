#include "philo.h"

static void ft_freenull(void **data)
{
	free(*data);
	*data= NULL;
}

static void	table_mtx_destroy(t_table *table)
{
	int		i;
	t_philo	*philo;
	t_fork 	*fork;

	i = -1;
	while (++i < table->philos_nbr)
	{
		philo = table->philos + (i * sizeof(t_philo));
		if (philo->id > 0 && safe_mtx_handle(&philo->philo_mtx, DESTROY) < 0)
			error_print("Error destroying philo_mtx");
		fork = table->forks + (i * sizeof(t_fork));
		if (fork->id >= 0 && safe_mtx_handle(&fork->fork_mtx, DESTROY) < 0)
			error_print("Error destroying fork_mtx");
	}
	if (safe_mtx_handle(&table->table_mtx, DESTROY) < 0)
		error_print("Error destroying table_mtx");
	if (safe_mtx_handle(&table->write_mtx, DESTROY) < 0)
		error_print("Error destroying write_mtx");
}

/**
 * free ptr on struct
 * no malloc on ptr to table, so no need to free that ptr
 */
void	table_free(t_table *table)
{
	table_mtx_destroy(table);
	if (table->forks)
		ft_freenull((void **)&table->forks);
	if (table->philos)
		ft_freenull((void **)&table->philos);
	return ;
}
