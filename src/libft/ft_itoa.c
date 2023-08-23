/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:39:58 by phelebra          #+#    #+#             */
/*   Updated: 2023/01/19 17:13:24 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	int			len;
	long int	m;

	len = ft_intlen(n);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	m = n;
	if (m < 0)
	{
		ptr[0] = '-';
		m *= -1;
	}
	ptr[len] = '\0';
	len--;
	if (m == 0)
		ptr[0] = '0';
	while (m)
	{
		ptr[len] = m % 10 + '0';
		m /= 10;
		len--;
	}
	return (ptr);
}
