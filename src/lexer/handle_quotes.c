#include "lexer.h"

int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		if (str[i + j + 1] != del && j % 2 == 0 && j != 1)
			j++;
	}
	return (j);
}
