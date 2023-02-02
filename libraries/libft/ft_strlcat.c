#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t	dstsize)
{
	size_t	index;
	size_t	dstlen;
	size_t	srclen;

	index = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstsize <= dstlen)
		return (srclen + dstsize);
	while (src[index] != '\0' && dstsize > (dstlen + 1))
	{
		dst[dstlen] = src[index];
		index++;
		dstlen++;
	}
	dst[dstlen] = '\0';
	return (dstlen + ft_strlen((char *)(src + index)));
}
