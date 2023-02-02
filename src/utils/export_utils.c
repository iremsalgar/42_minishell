#include "builtins.h"

int	is_equal_varbl(char *str)
{
	if (ft_strncmp(str, "=$", ft_strlen(str)))
		return (1);
	return (0);
}
