/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:05:14 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/27 18:21:38 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(t_mtx *mtx, int *dst, int value)
{
	safe_mutex(mtx, LOCK);
	*dst = value;
	safe_mutex(mtx, UNLOCK);
}

int	get_bool(t_mtx *mtx, int *dst)
{
	int	rslt;

	safe_mutex(mtx, LOCK);
	rslt = *dst;
	safe_mutex(mtx, UNLOCK);
	return (rslt);
}
