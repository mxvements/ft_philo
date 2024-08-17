
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
