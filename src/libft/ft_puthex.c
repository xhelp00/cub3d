/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:13:33 by phelebra          #+#    #+#             */
/*   Updated: 2023/02/10 12:53:09 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_sizehex(unsigned int ui)
{
	int	i;

	i = 0;
	while (ui)
	{
		i++;
		ui /= 16;
	}
	return (i);
}

static char	*ft_itohex(unsigned int ui, char xchar)
{
	char	*ptr;
	int		size;
	int		i;

	size = ft_sizehex(ui);
	ptr = malloc(sizeof(char) * (size + 1));
	if (!ptr)
		return (NULL);
	ptr[size] = '\0';
	while (ui)
	{
		i = ui % 16;
		if (i < 10)
			ptr[size - 1] = i + '0';
		else
			ptr[size - 1] = i + xchar;
		ui /= 16;
		size--;
	}
	return (ptr);
}

int	ft_puthex(unsigned int ui, char xchar)
{
	char	*s;
	int		size;

	if (!ui)
	{
		write (1, "0", 1);
		return (1);
	}
	if (xchar == 'X')
		xchar = 55;
	else
		xchar = 87;
	s = ft_itohex(ui, xchar);
	size = ft_putstr(s);
	free(s);
	return (size);
}
