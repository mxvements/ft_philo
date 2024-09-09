#include "philo.h"

/**
 * only using usleep when reaching a thereshold
 * usec (microseconds) < 1000
 */
void	ft_usleep(t_table *table, long micro_s)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = ft_gettime(MICROSECOND);
	while ((ft_gettime(MICROSECOND) - start) < micro_s )
	{
		if (is_finished(table) == 1)
			break ;
		elapsed = ft_gettime(MICROSECOND) - start;
		remaining = micro_s - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while ((ft_gettime(MICROSECOND) - start) < micro_s)
				;
		}
	}
}
