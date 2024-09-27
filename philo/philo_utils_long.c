/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_long.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:05:17 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 18:21:38 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_long(t_mtx *mtx, long *dst, long value)
{
	safe_mutex(mtx, LOCK);
	*dst = value;
	safe_mutex(mtx, UNLOCK);
}

void	add_long(t_mtx *mtx, long *dst, long value_to_add)
{
	int	value;

	safe_mutex(mtx, LOCK);
	value = *dst;
	*dst = value + value_to_add;
	safe_mutex(mtx, UNLOCK);
}

long	get_long(t_mtx *mtx, long *dst)
{
	long	rslt;

	safe_mutex(mtx, LOCK);
	rslt = *dst;
	safe_mutex(mtx, UNLOCK);
	return (rslt);
}
