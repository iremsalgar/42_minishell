#include "libft.h"
#include <stdio.h>

int	ft_isalnum(int str)
{
	if (ft_isdigit (str) || ft_isalpha (str))
		return (1);
	return (0);
}
