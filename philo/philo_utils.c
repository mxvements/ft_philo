
#include "philo.h"


void	philo_exit(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t bytes)
{
	void	*rslt;

	rslt = malloc(bytes);
	if (!rslt)
		philo_exit("Malloc error");
	return (rslt);
}

void	set_bool(t_mtx *mtx, int *dst, int value)
{
	safe_mutex_handle(mtx, LOCK);
	*dst = value;
	safe_mutex_handle(mtx, UNLOCK);
}

void	set_long(t_mtx *mtx, long *dst, long value)
{
	safe_mutex_handle(mtx, LOCK);
	*dst = value;
	safe_mutex_handle(mtx, UNLOCK);
}
