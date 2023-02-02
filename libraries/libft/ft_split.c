#include "libft.h"
#include <stdio.h>

static size_t	if_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	return (len);
}

static size_t	len_word(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != '\0')
	{
		if (*s != c && (s[1] == '\0' || s[1] == c))
			len++;
		s++;
	}
	return (len);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	index;
	size_t	two_index;
	size_t	word_len;

	if (!s)
		return (NULL);
	word_len = len_word(s, c);
	res = (char **)malloc(sizeof(char *) * word_len + 1);
	if (res == NULL)
		return (NULL);
	index = 0;
	while (index < word_len)
	{
		while (*s == c && *s != '\0')
			s++;
		res[index] = (char *)malloc(sizeof(char) * if_word_len(s, c) + 1);
		two_index = 0;
		while (*s != c && *s != '\0')
			res[index][two_index++] = *s++;
		res[index][two_index] = '\0';
		index++;
	}
	res[index] = NULL;
	return (res);
}
