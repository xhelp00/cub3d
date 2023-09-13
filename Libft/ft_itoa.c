/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:31:31 by nroth             #+#    #+#             */
/*   Updated: 2023/01/13 13:31:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

static void	add_digit(char *dest, int n, int n_len)
{
	int	index;
	int	factor;
	int	digit;

	digit = 0;
	index = 0;
	factor = ft_pow(10, n_len - 1);
	if (n < 0)
	{
		n *= -1;
		dest[index++] = '-';
		n_len++;
	}
	while (index < n_len)
	{
		digit = 0;
		while (n >= factor)
		{
			digit += 1;
			n -= factor;
		}
		dest[index] = digit + '0';
		index++;
		factor /= 10;
	}
}

char	*ft_itoa(int n)
{
	int		n_len;
	char	*res;

	n_len = 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	while (ft_abs(n) / ft_pow(10, n_len - 1) >= 10)
		n_len++;
	if (n < 0)
		res = ft_calloc(sizeof(char), n_len + 2);
	else
		res = ft_calloc(sizeof(char), n_len + 1);
	if (!res)
		return (NULL);
	add_digit(res, n, n_len);
	return (res);
}
