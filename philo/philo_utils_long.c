#include "philo.h"

void	set_long(t_mtx *mtx, long *dst, long value)
{
	safe_mtx_handle(mtx, LOCK);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK);
}

void	add_long(t_mtx *mtx, long *dst, long value_to_add)
{
	int	value;

	safe_mtx_handle(mtx, LOCK);
	value = *dst;
	*dst = value + value_to_add;
	safe_mtx_handle(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *dst)
{
	long	rslt;

	safe_mtx_handle(mtx, LOCK);
	rslt = *dst;
	safe_mtx_handle(mtx, UNLOCK);
	return (rslt);
}
