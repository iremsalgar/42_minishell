#include "minishell.h"

int	find_matching_quote(char *line, int i, int *num_del, int del)
{
	int	j;

	j = i + 1;
	*num_del += 1;
	while (line[j] && line[j] != del)
		j++;
	if (line[j] == del)
		*num_del += 1;
	return (j - i);
}

int	count_quotes(char *line)
{
	int	i;
	int	s;
	int	d;

	s = 0;
	d = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == 34)
			i += find_matching_quote(line, i, &d, 34);
		if (line[i] == 39)
			i += find_matching_quote(line, i, &s, 39);
		if ((int)ft_strlen(line) == i)
			break ;
	}
	if ((d > 0 && d % 2 != 0) || (s > 0 && s % 2 != 0))
		return (0);
	return (1);
}

char	**ft_arrdup(char **arr)
{
	char	**rtn;
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (arr[i] != NULL)
	{
		rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}

static int	ft_control_pipe2(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			break ;
		i++;
	}
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}

/*control_pipe functions does some sort of controls
controls of the funcitons are if there is any arguments after pipe*/

void	control_pipe(t_tools *tools)
{
	char	*line;
	int		i;

	line = tools->args;
	i = ft_strlen(line);
	if (!ft_control_pipe2(line))
		return ;
	while (i >= 0)
	{
		if (ft_isprint(line[i]) && line[i] != '|')
			return ;
		else if (line[i] == '|')
			ft_error(0, tools);
		i--;
	}
}
