
#include "philo.h"

static void *myturn(void *arg)
{
	int	i = 8;

	(void)arg;
	while (i--)
	{
		sleep(1);
		printf("my turn %d\n", i);
	}
	return (NULL);
}

static void *yourturn(void *arg)
{
	int	i = 3;

	(void)arg;
	while (i--)
	{
		sleep(2);
		printf("your turn %d\n", i);
	}
	return (NULL);
}

/*
	Using pthread_create and pthread_join
*/
int	main(void)
{
	pthread_t	t1;
	//pthread_t	t2;

	/* pthread_create(
		pthread_t *thread,
		const thread_attr_t *attr,
		void *(*start routine)(void *),
		void *arg
		)
	*/
	pthread_create(&t1, NULL, myturn, NULL);
	yourturn(NULL);
	pthread_join(t1, NULL);
	return (0);
}