
#include "philo.h"

/**
 * long philo_nbr
 * long time_to_die
 * long time_to_eat
 * long time_to_sleep
 * long	meal_limit
 */
void	print_table(t_table *table)
{
	printf("[table]\n");
	if (table->philo_nbr)
		printf("table->philo_nbr:\t%li\n", table->philo_nbr);
	if (table->time_to_die)
		printf("table->time_to_die:\t%li\n", table->time_to_die);
	if (table->time_to_eat)
		printf("table->time_to_eat:\t%li\n", table->time_to_eat);
	if (table->time_to_sleep)
		printf("table->time_to_sleep:\t%li\n", table->time_to_sleep);
	if (table->meal_limit)
		printf("table->meal_limit:\t%li\n", table->meal_limit);
	if (table->time_start)
		printf("table->time_start:v%li\n", table->time_start);
	if (table->end_flag)
		printf("table->end_flag:\t%i\n", table->end_flag);
}
/**
 * generic function to handle errors
 */
void	philo_exit(const char *error)
{
	printf(RED"%s\n"WHITE, error);
	exit(EXIT_FAILURE);
}
/**
 * safe_malloc
 * use philo_exit when there's a malloc error
 */
void	*safe_malloc(size_t bytes)
{
	void	*rslt;

	rslt = malloc(bytes);
	if (!rslt)
		philo_exit("Malloc error");
	return (rslt);
}

/**
 * return errors on pthread functions'
 * like a recreation of perror (not allowed in the project)
 * possible return error codes:
 * pthread_init
 * 	EAGAIN, EINVAL, ENOMEM, EPERM
 * pthread_destroy
 * 	EAGAIN, EINVAL, ENOMEM, EPERM
 * pthread_lock
 * 	EAGAIN, EINVAL, EPERM, ENOTRECOVERABLE, EOWNERDEAD, EDEADLK, EBUSY, 
 * pthread_unlock
 * 	EAGAIN, EINVAL, EPERM, ENOTRECOVERABLE, EOWNERDEAD, EDEADLK, EBUSY, 
 * 
 * EINVAL, EDEADLK, EPERM, ENOMEN, EBUSY
 */
static void	handle_mutex_error(int status, t_pthread opthread)
{

}

/**
 * pthread_create
 * pthread_detach
 * pthread_join
 * pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
 * pthread_mutex_destroy(pthread_mutex_t *mutex)
 * pthread_mutex_lock(pthread_mutex_t *mutex)
 * pthread_mutex_unlock(pthread_mutex_t *mutex)
 */
void	safe_mutex_handle(t_mtx *mutex, t_pthread opthread)
{
	if (opthread = INIT)
		pthread_mutex_init(mutex, NULL);
	else if (opthread = DESTROY)
		pthread_mutex_destroy(mutex);
	else if (opthread = LOCK)
		pthread_mutex_lock(mutex);
	else if (opthread = UNLOCK)
		pthread_mutex_unlock(mutex);
	else
		philo_exit("Wrong opthread");
}
