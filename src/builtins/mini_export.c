#include "builtins.h"

/*
* It checks if a variable exists in the environment,
* and if it does, it updates it
*/
int	variable_exist(t_tools *tools, char *str)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = ft_strdup(str);
	s1 = delete_quotes(s1);
	while (tools->envp[i])
	{
		if (ft_strncmp(tools->envp[i], \
			str, equal_sign(tools->envp[i])) == 0)
		{
			free(tools->envp[i]);
			tools->envp[i] = ft_strdup(s1);
			free(s1);
			return (1);
		}
		i++;
	}
	free(s1);
	return (0);
}

int	check_parameter(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]))
		return (export_error(str));
	if (equal_sign(str) == 0)
		return (EXIT_FAILURE);
	if (str[0] == '=')
		return (export_error(str));
	while (str[i] != '=')
	{
		if (check_valid_identifier(str[i]))
			return (export_error(str));
		i++;
	}
	return (EXIT_SUCCESS);
}

/*
* It takes an array of strings,
* a string, and a string,
* and returns an array of strings
*/
char	**whileloop_add_var(char **arr, char **rtn, char *str)
{
	int		i;
	char	*s1;

	i = 0;
	s1 = ft_strdup(str);
	while (arr[i] != NULL)
	{
		if (arr[i + 1] == NULL)
		{
			rtn[i] = ft_strdup(s1);
			rtn[i + 1] = ft_strdup(arr[i]);
		}
		else
			rtn[i] = ft_strdup(arr[i]);
		if (rtn[i] == NULL)
		{
			free_arr(rtn);
			return (rtn);
		}
		i++;
	}
	free(str);
	return (rtn);
}

/*It adds a string to an array of strings*/
char	**add_var(char **arr, char *str)
{
	char	**rtn;
	size_t	i;

	i = 0;
	str = delete_quotes(str);
	while (arr[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 2);
	if (!rtn)
		return (NULL);
	i = 0;
	whileloop_add_var(arr, rtn, str);
	return (rtn);
}

/*It takes a simple command and exports it to the environment*/
int	mini_export(t_tools *tools, t_simple_cmds *simple_cmd)
{
	char	**tmp;
	int		i;

	i = 1;
	if (!simple_cmd->str[1] || simple_cmd->str[1][0] == '\0')
		mini_env(tools, simple_cmd);
	else
	{
		while (simple_cmd->str[i])
		{
			if (check_parameter(simple_cmd->str[i]) == 0 \
			&& variable_exist(tools, simple_cmd->str[i]) == 0)
			{
				if (simple_cmd->str[i])
				{
					tmp = add_var(tools->envp, simple_cmd->str[i]);
					free_arr(tools->envp);
					tools->envp = tmp;
				}
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
