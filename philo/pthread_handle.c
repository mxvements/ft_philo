#include "philo.h"

/**
 * return errors on pthread functions'
 * like a recreation of perror (not allowed in the project)
 *
 * possible return error codes:
 * (https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html)
 *
 * pthread_create:
 * 	EAGAIN, EINVAL, EPERM
 * pthread_join;
 * 	EDEADLK, EINVAL,ESRCH
 * pthread_detach;
 * 	EINVAL, ESRCH
 * 
 * pthread_init;
 * 	EAGAIN, EINVAL, ENOMEM, EPERM
 * pthread_destroy;
 * 	EAGAIN, EINVAL, ENOMEM, EPERM
 * pthread_lock;
 * 	EAGAIN, EINVAL, EPERM, ENOTRECOVERABLE, EOWNERDEAD, EDEADLK, EBUSY,
 * pthread_unlock;
 * 	EAGAIN, EINVAL, EPERM, ENOTRECOVERABLE, EOWNERDEAD, EDEADLK, EBUSY,
 */
static void	handle_pthread_error(int status)
{
	if (status == EAGAIN)
		error_exit("Resource temporarily unavailable");
	else if (status == EINVAL)
		error_exit("Invalid argument");
	else if (status == EPERM)
		error_exit("Operation not permitted");
	else if (status == ENOMEM)
		error_exit("Cannot allocate memory");
	else if (status == ENOTRECOVERABLE)
		error_exit("State not recoverable");
	else if (status == EOWNERDEAD)
		error_exit("Owner died");
	else if (status == EDEADLK)
		error_exit("Resource deadlock avoided");
	else if (status == EBUSY)
		error_exit("Device or resource busy");
	// else if (status == ESRCH)
	// 	error_exit("No such process");
}

/**
 * mutex functs:
 * 
 * pthread_mutex_init
 * 	(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr)
 * pthread_mutex_destroy
 * 	(pthread_mutex_t *mutex)
 * pthread_mutex_lock
 * 	(pthread_mutex_t *mutex)
 * pthread_mutex_unlock
 * 	(pthread_mutex_t *mutex)
 */
void	safe_mutex_handle(t_mtx *mutex, t_opthread opthr)
{
	//dprintf(STDOUT_FILENO, "opthr: %d\n", opthr);
	if (opthr == INIT)
		handle_pthread_error(pthread_mutex_init(mutex, NULL));
	else if (opthr == DESTROY)
		handle_pthread_error(pthread_mutex_destroy(mutex));
	else if (opthr == LOCK)
		handle_pthread_error(pthread_mutex_lock(mutex));
	else if (opthr == UNLOCK)
		handle_pthread_error(pthread_mutex_unlock(mutex));
	else
		error_exit("Wrong opthread");
}

/**
 * threads functs:
 * 
 * pthread_create
 * 	(pthread_t *thread, const pthread_attr_t *attr, 
 * 	void *(*start_routine)(void *), void *arg)
 * pthread_join
 * 	(pthread_t thread, void **retval)
 * pthread_detach
 * 	(pthread_t thread)
 */
void	safe_thread_handle(pthread_t *thr, void *(*f)(void *), void *data,
	t_opthread opthr)
{
	//dprintf(STDOUT_FILENO, "opthr: %d\n", opthr);
	if (opthr == CREATE)
		handle_pthread_error(pthread_create(thr, NULL, f, data));
	else if (opthr == JOIN)
		handle_pthread_error(pthread_join(*thr, NULL));
	else if (opthr == DETACH)
		handle_pthread_error(pthread_detach(*thr));
	else
		error_exit("Wrong opthread");
}
