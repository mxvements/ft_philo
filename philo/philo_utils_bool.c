#include "philo.h"

void	set_bool(t_mtx *mtx, int *dst, int value)
{
	safe_mtx_handle(mtx, LOCK);
	*dst = value;
	safe_mtx_handle(mtx, UNLOCK);
}

int		get_bool(t_mtx *mtx, int *dst)
{
	int	rslt;

	safe_mtx_handle(mtx, LOCK);
	rslt = *dst;
	safe_mtx_handle(mtx, UNLOCK);
	return (rslt);
}
