#include "philo.h"

int g_BIG = 10000;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void	*count_to_big(void *arg)
{
	int	i = 0;
	int *counter = (int *)malloc(sizeof(int));

	(void)arg;
	(*counter) = 0;
	while (i < g_BIG)
	{
		pthread_mutex_lock(&lock);
		(*counter)++;
		pthread_mutex_unlock(&lock);
		i++;
	}
	return (counter);
}
/*
	Using locks so threads wait for each other (mutex)
	
	This example wont work with parallelism because of the increment in the
	counter -> race condition
		both threads have access to the same resources (memory)

	Threads use the same memory, but they need to wait on each other to
	do the increment on the counter, otherwise we would have a random result
*/
int	main(void)
{
	int	*counter;
	pthread_t	t1;
	pthread_t	t2;

	pthread_create(&t1, NULL, count_to_big, NULL);
	pthread_create(&t2, NULL, count_to_big, NULL);

	pthread_join(t1, (void *)&counter);
	pthread_join(t2, (void *)&counter);

	printf("final counter: %d\n", *counter);
	return (0);
}