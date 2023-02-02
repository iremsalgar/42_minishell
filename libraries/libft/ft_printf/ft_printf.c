#include "../libft.h"

int	ft_form(char c, va_list varg)
{
	int	len;

	len = 0;
	if (c == 's')
		len += ft_putstr(va_arg(varg, char *));
	else if (c == 'c')
		len += ft_putchar(va_arg(varg, int));
	else if (c == 'd')
		len += ft_putnbr(va_arg(varg, int));
	else if (c == 'i')
		len += ft_putnbr(va_arg(varg, int));
	else if (c == 'x' || c == 'X')
		len += ft_putx(va_arg(varg, unsigned int), c);
	else if (c == 'p')
	{
		len += write(1, "0x", 2);
		len += ft_putx(va_arg(varg, unsigned long int), 'x');
	}
	else if (c == 'u')
		len += ft_put_unsint(va_arg(varg, unsigned int));
	else if (c == '%')
		len += write(1, "%", 1);
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	varg;
	int		i;

	i = 0;
	len = 0;
	va_start(varg, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_form(str[++i], varg);
			i++;
		}
		else
			len += ft_putchar(str[i++]);
	}
	va_end(varg);
	return (len);
}
