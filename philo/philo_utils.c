
#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*rslt;

	rslt = malloc(bytes);
	if (!rslt)
		error_exit("Malloc error");
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

long	get_long(t_mtx *mtx, int *dst)
{
	long	rslt;

	safe_mutex_handle(mtx, LOCK);
	rslt = *dst;
	safe_mutex_handle(mtx, UNLOCK);
	return (rslt);
}

void	write_status_debug(t_philo *philo, t_status status)
{
	t_table	*table;
	long	elapsed;

	table = philo->table;
	elapsed = get_time(MILLISECOND);
	if (philo->is_full == 1) //THREAD_SAFE?
		return ;
	safe_mutex_handle(&table->write_mtx, LOCK);

	if ((status == FRST_FORK || status == SCND_FORK) && is_finished(table) == 0)
		printf(YELLOW"%-6ld %d has taken a fork\n"RESET, elapsed, philo->id);
	else if (status == EAT && is_finished(table) == 0)
		printf(ORANGE"%-6ld %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEP && is_finished(table) == 0)
		printf(CYAN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINK && is_finished(table) == 0)
		printf(GREEN"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIE)
		printf(RED"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	
	safe_mutex_handle(&table->write_mtx, UNLOCK);

}

void	write_status(t_philo *philo, t_status status)
{
	t_table	*table;
	long	elapsed;

	table = philo->table;
	elapsed = get_time(MILLISECOND);
	if (philo->is_full == 1) //THREAD_SAFE?
		return ;
	safe_mutex_handle(&table->write_mtx, LOCK);

	if ((status == FRST_FORK || status == SCND_FORK) && is_finished(table) == 0)
		printf(YELLOW"%-6ld %d has taken a fork\n"RESET, elapsed, philo->id);
	else if (status == EAT && is_finished(table) == 0)
		printf(ORANGE"%-6ld %d is eating\n"RESET, elapsed, philo->id);
	else if (status == SLEEP && is_finished(table) == 0)
		printf(CYAN"%-6ld %d is sleeping\n"RESET, elapsed, philo->id);
	else if (status == THINK && is_finished(table) == 0)
		printf(GREEN"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	else if (status == DIE)
		printf(RED"%-6ld %d is thinking\n"RESET, elapsed, philo->id);
	
	safe_mutex_handle(&table->write_mtx, UNLOCK);
}
