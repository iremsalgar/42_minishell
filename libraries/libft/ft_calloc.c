#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	char	*ptr;

	ptr = (char *)malloc(size * num);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, num * size);
	return (ptr);
}
