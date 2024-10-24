/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucia <lucia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 20:39:47 by luciama2          #+#    #+#             */
/*   Updated: 2024/10/21 23:18:45 by lucia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 	use example
 *  ./philo 5 800 200 200 [5]
 * 
 * 	arguments:
 * 	number_of_philosophers
 * 	time_to_die (ms)
 * 	time_to_eat (ms)
 * 	time_to_sleep (ms)
 * 	number_of_imes_each_philosopher_must_eat (optional)
 * 
 * 	cases to check:
 *		1 800 200 200 muere -> CHECK EXIT
 *		5 800 200 200 viven
 *		5 800 200 200 7 viven y cada uno come 7 veces
 *		4 410 200 200 viven
 *		4 310 200 100 mueren
 * 
 *		3 310 103 103 (tienen que vivir) 
 *		3 310 104 104 (tienen que morir)
 * 
 * 		210 310 103 104 (no deberian morir)

 * ncdu  en el directorio root para ver el cache

 */
int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		error_print("Invalid number of arguments\
			\nExample: ./philo 5 800 200 200 (5)");
		return (1);
	}
	memset((void *)&table, 0, sizeof(t_table));
	if (table_init(&table, argv) < 0)
	{
		table_free(&table);
		return (1);
	}
	if (philo_dinner(&table) < 0)
	{
		table_free(&table);
		return (1);
	}
	table_free(&table);
	return (0);
}
