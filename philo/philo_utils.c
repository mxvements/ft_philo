
#include "philo.h"


void	*safe_malloc(size_t bytes)
{
	void	*rslt;

	rslt = malloc(bytes);
	if (!rslt)
	{
		error_print("Malloc error");
		return (NULL);
	}
	return (rslt);
}

void	set_bool(t_mtx *mtx, int *dst, int value)
{
	safe_mutex_handle(mtx, LOCK);
	*dst = value;
	safe_mutex_handle(mtx, UNLOCK);
}

int		get_bool(t_mtx *mtx, int *dst)
{
	int	rslt;

	safe_mutex_handle(mtx, LOCK);
	rslt = *dst;
	safe_mutex_handle(mtx, UNLOCK);
	return (rslt);
}

void	set_long(t_mtx *mtx, long *dst, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dst = value;
	safe_mutex_handle(mtx, UNLOCK);
}

void	add_long(t_mtx *mtx, long *dst, long value_to_add)
{
	int	value;

	safe_mutex_handle(mtx, LOCK);
	value = *dst;
	*dst = value + value_to_add;
	safe_mutex_handle(mtx, UNLOCK);
}

/**
 * Make the system Fair
 */
void	de_synchronize_philos(t_philo *philo)
{
	if (((t_table *)philo->table)->philos_nbr % 2 == 0 && philo->id % 2 == 0)
	{
		precision_usleep(philo->table, 3e4);
	}
	else
	{
		if (philo->id % 2 == 0)
			philo_think(philo);
	}
}

long	get_long(t_mtx *mtx, long *dst)
{
	long	rslt;

	safe_mutex_handle(mtx, LOCK);
	rslt = *dst;
	safe_mutex_handle(mtx, UNLOCK);
	return (rslt);
}

static void	write_status_debug(t_philo *philo, t_status status, long elapsed)
{
	t_table	*table;
	
	table = philo->table;
	if (status == FRST_FORK && is_finished(table) == 0)
		printf(YELLOW"%-6ld %d has taken the 1st fork [%d]\n"RESET, elapsed,
		philo->id, philo->first_fork->fork_id);
	else if (status == SCND_FORK && is_finished(table) == 0)
		printf(YELLOW"%-6ld %d has taken the 2nd fork [%d]\n"RESET, elapsed,
		philo->id, philo->secnd_fork->fork_id);
	else if (status == EAT && is_finished(table) == 0)
		printf(GREEN"%-6ld %d is eating [count: %ld]\n"RESET, elapsed,
		philo->id, philo->meals_count);
	else if (status == SLEEP && is_finished(table) == 0)
		printf(CYAN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINK && is_finished(table) == 0)
		printf(GRAY"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIE)
		printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
}
/**
 * [time_millisec] [philo_id] [action]
 */
void	write_status(t_philo *philo, t_status status, int debug)
{
	t_table	*table;
	long	elapsed;

	table = philo->table;
	elapsed = get_time(MILLISECOND) - ((t_table*)philo->table)->t_start;
	if (philo->is_full == 1) //THREAD_SAFE?
		return ;
	safe_mutex_handle(&table->write_mtx, LOCK);
	if (debug)
		write_status_debug(philo, status, elapsed);
	else
	{
		if ((status == FRST_FORK || status == SCND_FORK)
			&& is_finished(table) == 0)
			printf(YELLOW"%-6ld %d has taken a fork\n"RESET, elapsed, philo->id);
		else if (status == EAT && is_finished(table) == 0)
			printf(ORANGE"%-6ld %d is eating\n"RESET, elapsed, philo->id);
		else if (status == SLEEP && is_finished(table) == 0)
			printf(CYAN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
		else if (status == THINK && is_finished(table) == 0)
			printf(GREEN"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
		else if (status == DIE)
			printf(RED"%-6ld %d died\n"RESET, elapsed, philo->id);
	}
	safe_mutex_handle(&table->write_mtx, UNLOCK);
}
