#include "philo.h"

void	philo_exit(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	exit(EXIT_FAILURE);
}
