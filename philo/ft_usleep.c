/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciama2 <luciama2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:14:05 by luciama2          #+#    #+#             */
/*   Updated: 2024/09/26 20:49:23 by luciama2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * only using usleep when reaching a thereshold
 * usec (microseconds) < 1000
 */
void	ft_usleep(t_table *table, long micro_s)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = ft_gettime(MICROSECOND);
	while ((ft_gettime(MICROSECOND) - start) < micro_s)
	{
		if (is_table_finished(table) == 1)
			break ;
		elapsed = ft_gettime(MICROSECOND) - start;
		remaining = micro_s - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while ((ft_gettime(MICROSECOND) - start) < micro_s)
				;
		}
	}
}
