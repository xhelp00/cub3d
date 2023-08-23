/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 18:09:27 by phelebra          #+#    #+#             */
/*   Updated: 2023/02/10 12:50:53 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_paramtype(va_list args, char c)
{
	int	size;

	size = 0;
	if (c == 'c')
		size = ft_putchar(va_arg(args, int));
	else if (c == 's')
		size = ft_putstr(va_arg(args, char *));
	else if (c == 'p')
		size = ft_putptr(va_arg(args, uintptr_t));
	else if (c == 'i' || c == 'd')
		size = ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		size = ft_putunsign(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		size = ft_puthex(va_arg(args, unsigned int), c);
	else if (c == '%')
		size = ft_putchar('%');
	return (size);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		size;
	int		i;

	i = 0;
	size = 0;
	va_start (args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			size += ft_paramtype(args, s[i + 1]);
			i++;
		}
		else
			size += ft_putchar(s[i]);
		i++;
	}
	va_end(args);
	return (size);
}
