/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:28:55 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 18:58:16 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * return errors on pthread functions'
 * like a recreation of perror (not allowed in the project)
 *
 * possible return error codes:
 * (https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html)
 *
 * 		pthread_create:
 * 			EAGAIN, EINVAL, EPERM
 *		pthread_join;
 * 			EDEADLK, EINVAL,ESRCH
 * 		pthread_detach;
 * 			EINVAL, ESRCH
 * 
 * 		pthread_init;
 * 			EAGAIN, EINVAL, ENOMEM, EPERM
 * 		pthread_destroy;
 * 			EAGAIN, EINVAL, ENOMEM, EPERM
 * 		pthread_lock;
 * 			EAGAIN, EINVAL, EPERM, ENOTRECOVERABLE, EOWNERDEAD, EDEADLK, EBUSY,
 * 		pthread_unlock;
 * 			EAGAIN, EINVAL, EPERM, ENOTRECOVERABLE, EOWNERDEAD, EDEADLK, EBUSY,
 * 
 * writes the error message and returns -1
 */
static int	pthr_error(int status)
{
	if (status == EAGAIN)
		return (error_print("Resource temporarily unavailable"));
	else if (status == EINVAL)
		return (error_print("Invalid argument"));
	else if (status == EPERM)
		return (error_print("Operation not permitted"));
	else if (status == ENOMEM)
		return (error_print("Cannot allocate memory"));
	else if (status == ENOTRECOVERABLE)
		return (error_print("State not recoverable"));
	else if (status == EOWNERDEAD)
		return (error_print("Owner died"));
	else if (status == EDEADLK)
		return (error_print("Resource deadlock avoided"));
	else if (status == EBUSY)
		return (error_print("Device or resource busy"));
	else if (status == ESRCH)
		return (error_print("No such process"));
	return (0);
}

/**
 * mutex functs:
 * 		pthread_mutex_init
 * 			(pthread_mutex_t *restrict mutex,
 * 			const pthread_mutexattr_t *restrict attr)
 * 		pthread_mutex_destroy
 * 			(pthread_mutex_t *mutex)
 * 		pthread_mutex_lock
 * 			(pthread_mutex_t *mutex)
 * 		pthread_mutex_unlock
 * 			(pthread_mutex_t *mutex)
 * 		return
 * 			0 in case of sucess, status code of error in case of error
 * 
 * writes the error message and returns -1
 *
 * to debug use:
 * 		dprintf(STDOUT_FILENO, "opthr: %d\n", opthr)
 */
int	safe_mutex(t_mtx *mutex, t_opthrd opthr)
{
	if (opthr == INIT)
		return (pthr_error(pthread_mutex_init(mutex, NULL)));
	else if (opthr == DESTROY)
		return (pthr_error(pthread_mutex_destroy(mutex)));
	else if (opthr == LOCK)
		return (pthr_error(pthread_mutex_lock(mutex)));
	else if (opthr == UNLOCK)
		return (pthr_error(pthread_mutex_unlock(mutex)));
	else
		return (error_print("Wrong opthread"));
}

/**
 * threads functs:
 * 		pthread_create
 * 			(pthread_t *thread, const pthread_attr_t *attr, 
 * 			void *(*start_routine)(void *), void *arg)
 * 		pthread_join
 * 			(pthread_t thread, void **retval)
 * 		pthread_detach
 * 			(pthread_t thread)
 * 		return
 * 			0 in case of succes, status code of error in case of error
 * 
 * writes the error message and returns -1
 * 
 * to debug use:
 * 		dprintf(STDOUT_FILENO, "opthr: %d\n", opthr)
 */
int	safe_thread(pthread_t *thr, void *(*f)(void *), void *data, t_opthrd opthr)
{
	if (opthr == CREATE)
		return (pthr_error(pthread_create(thr, NULL, f, data)));
	else if (opthr == JOIN)
		return (pthr_error(pthread_join(*thr, &data)));
	else if (opthr == DETACH)
		return (pthr_error(pthread_detach(*thr)));
	else
		return (error_print("Wrong opthread"));
}
