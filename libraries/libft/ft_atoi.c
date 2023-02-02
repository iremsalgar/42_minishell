#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int				i;
	long long int	res;

	i = 1;
	res = 0;
	while ((*str >= 9 && *str <= 13) || (*str == 32))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (*str != 0 && *str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0') * i;
		if (res > 2147483647)
			return (-1);
		if (res < -2147483648)
			return (0);
		str++;
	}
	return (res);
}
