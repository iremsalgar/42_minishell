#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_p;
	const char	*src_p;

	if ((dst == src) || n == 0)
		return (dst);
	if (!dst && !src)
		return (0);
	dst_p = (char *)dst;
	src_p = (const char *)src;
	while (n--)
		dst_p[n] = src_p[n];
	return (dst);
}
