/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:52:17 by nroth             #+#    #+#             */
/*   Updated: 2023/02/07 16:52:21 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	ft_unsigned_pow(size_t nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	if (power == 0)
		return (1);
	return (nb * ft_unsigned_pow(nb, power - 1));
}

int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}

static void	add_digit(char *dest, size_t n, int n_len)
{
	int		index;
	size_t	factor;
	int		digit;

	digit = 0;
	index = 0;
	factor = ft_unsigned_pow(10, n_len - 1);
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

char	*unsigned_itoa(size_t num)
{
	int		num_len;
	char	*res;

	num_len = 1;
	while (num / ft_unsigned_pow(10, num_len - 1) >= 10)
		num_len++;
	res = ft_calloc(num_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	add_digit(res, num, num_len);
	return (res);
}

void	ft_strappend(char **s1, char const *s2)
{
	char	*ret_str;
	size_t	tot_len;
	size_t	i;

	tot_len = ft_strlen(*s1) + ft_strlen(s2);
	ret_str = (char *)ft_calloc(tot_len + 1, sizeof(char));
	if (!ret_str)
		return ;
	i = 0;
	while (i < tot_len)
	{
		if (i < ft_strlen(*s1))
			ret_str[i] = *(*(s1) + i);
		else
			ret_str[i] = s2[i - ft_strlen(*s1)];
		i++;
	}
	if (*s1)
		free(*s1);
	*s1 = ret_str;
}
