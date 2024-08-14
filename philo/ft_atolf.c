
#include "philo.h"
#include <limits.h>

static int ft_isspace(int c)
{
	int	flag;

	flag = 0;
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == 32)
	{
		flag = 1;
	}
	return (flag);
}

static int ft_isdigit(int c)
{
	int	flag;

	flag = 0;
	if (c >= 48 && c <= 57)
		flag = 1;
	return (flag);
}

/**
 * ft_atolh
 * PROTOTYPE	long ft_atolh(char *s, int *flag)
 * PARAMS		s: str to convert to number
 * 				flag: 0 in case no int.overflow, 1 in case there's int.overflow
 * RETURNS		long
 * DESCRIPTION	convert intial portion of str to long representation considering
 * 				possible long overflow
 * NOTEs		stops whenever there's an invalid char
 * 				valid chars: digits & +- & spaces
 * 				first discards all whitespaces
 * 				then sets the sign(+-), only 1 char is considered
 * 				all base-10 digits until EOL or any other char is found
 * 				if at any point there's an long-overflow, flag is updated
 */
long	ft_atolf(char *s, int *flag)
{
	long long 	nbr;
	int			sign;

	sign = 1;
	*flag = 0;
	nbr = 0;
	while (ft_isspace(*s) == 1)
		s++;
	if (*s == '+')
		s++;
	else if (*s == '-')
	{
		sign = -1;
		s++;
	}
	if (ft_isdigit(*s) == 0)
		*flag = 1;
	while (ft_isdigit(*s) == 1)
	{
		nbr = (nbr * 10) + (*s - '0');
		if ((nbr * sign) < INT_MIN || (sign == 1 && nbr > INT_MAX))
			*flag = 1;
		s++;
	}
	return (nbr * sign);
}
