
#include "philo.h"

static void *myturn(void *arg)
{
	int	i = 8;
	int	*v = (int *)arg;

	while (i--)
	{
		sleep(1);
		printf("my turn %d - %d\n", i, *v);
		(*v)++;
	}
	return (NULL);
}

static void *yourturn(void *arg)
{
	int	i = 3;
	int	*iptr = (int *)malloc(sizeof(int));

	(void)arg;
	*iptr =  2;
	while (i--)
	{
		sleep(2);
		printf("your turn %d - %d\n", i, *iptr);
		(*iptr)++;
	}
	return (iptr);
}
/**
 * Passing data to threads
 */
int	main(void)
{
	pthread_t	t1;
	pthread_t	t2;
	int v = 5; //value modified in thread
	int *rslt; //value allocated in thread

	pthread_create(&t1, NULL, myturn, &v);
	pthread_create(&t2, NULL, yourturn, NULL);

	//wait until thread is done before we exit
	pthread_join(t1, NULL);
	pthread_join(t2, (void *)&rslt);

	printf("threads end, value passed to 1st thread: %d\n", v); //8 + 5
	printf("threads end, result allocated in 2nd thread: %d\n", (*rslt)); //3 + 2

	return (0);
}