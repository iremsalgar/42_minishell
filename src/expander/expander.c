#include "minishell.h"
#include "builtins.h"

/*It loops through the environment variables and if
it finds one that matches the string after the
dollar sign, it replaces the string after the
dollar sign with the value of the environment variable*/
int	loop_if_dollar_sign(t_tools *tools, char *str, char **tmp, int j)
{
	int		k;
	int		ret;
	char	*tmp2;
	char	*tmp3;

	k = 0;
	ret = 0;
	while (tools->envp[k])
	{
		if (ft_strncmp(str + j + 1, tools->envp[k],
				equal_sign(tools->envp[k]) - 1) == 0
			&& after_dol_lenght(str, j) - j == (int)equal_sign(tools->envp[k]))
		{
			tmp2 = ft_strdup(tools->envp[k] + equal_sign(tools->envp[k]));
			tmp3 = ft_strjoin(*tmp, tmp2);
			free(*tmp);
			*tmp = tmp3;
			free(tmp2);
			ret = equal_sign(tools->envp[k]);
		}
		k++;
	}
	if (ret == 0)
		ret = after_dol_lenght(str, j) - j;
	return (ret);
}

/*It checks if the character after the dollar sign is a digit.*/
int	handle_digit_after_dollar(int j, char *str)
{
	int	i;

	i = j;
	if (str[j] == '$')
	{
		if (ft_isdigit(str[j + 1]) == 1)
		{
			j += 2;
		}
	}
	return (j - i);
}

/*It detects the dollar signand replaces it with the value of the variable*/
char	*detect_dollar_sign(t_tools *tools, char *str)
{
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	j = 0;
	tmp = ft_strdup("\0");
	while (str[j])
	{
		j += handle_digit_after_dollar(j, str);
		if (str[j] == '$' && str[j + 1] == '?')
			j += question_mark(&tmp);
		else if (str[j] == '$' && (str[j + 1] != ' ' && (str[j + 1] != '"'
					|| str[j + 2] != '\0')) && str[j + 1] != '\0')
			j += loop_if_dollar_sign(tools, str, &tmp, j);
		else
		{
			tmp2 = char_to_str(str[j++]);
			tmp3 = ft_strjoin(tmp, tmp2);
			free(tmp);
			tmp = tmp3;
			free(tmp2);
		}
	}
	return (tmp);
}

/*
* It takes a string and replaces all the dollar signs
* with the corresponding environment variable
*/
char	**expander(t_tools *tools, char **str)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (str[i] != NULL)
	{
		if (dollar_sign(str[i]) != 0 && str[i][dollar_sign(str[i]) - 2] != '\'' \
			&& str[i][dollar_sign(str[i])] != '\0')
		{
			tmp = detect_dollar_sign(tools, str[i]);
			free(str[i]);
			str[i] = tmp;
		}
		if (ft_strncmp(str[0], "export", ft_strlen(str[0]) - 1) != 0)
		{
			str[i] = delete_quotes(str[i]);
		}
		i++;
	}
	return (str);
}

/*It takes a string and expands it*/
char	*expander_str(t_tools *tools, char *str)
{
	char	*tmp;

	tmp = NULL;
	if (dollar_sign(str) != 0 && str [dollar_sign(str) - 2] != '\'' \
		&& str[dollar_sign(str)] != '\0')
	{
		tmp = detect_dollar_sign(tools, str);
		free(str);
		str = tmp;
	}
	if (there_is_quotes(str))
		str = delete_quotes(str);
	return (str);
}
