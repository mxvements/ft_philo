#include "philo.h"

/**
 * using gettimeofday
 * t_time -> SECOND; MILLISECOND; MICROSECOND
 * 
 */
long	ft_gettime(t_time time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (error_print("Failure on gettimeofday"));
	if (time_code == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (time_code == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (time_code == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		return (error_print("Wrong time_code on get_time"));
	return (0);
}