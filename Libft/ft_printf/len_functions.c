/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:52:54 by nroth             #+#    #+#             */
/*   Updated: 2023/02/07 16:52:55 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned int	unsigned_len(unsigned long long num)
{
	unsigned int	num_len;

	num_len = 1;
	while (num / ft_unsigned_pow(10, num_len - 1) >= 10)
		num_len++;
	return (num_len);
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

unsigned int	num_len(int num)
{
	unsigned int	n_len;

	n_len = 1;
	if (num == -2147483648)
		return (10);
	while (ft_abs(num) / ft_pow(10, n_len - 1) >= 10)
		n_len++;
	return (n_len);
}

size_t	ft_special_strlen(char *s, char type)
{
	int	i;

	i = 0;
	if (!*s && type == 'c')
		return (1);
	while (s[i])
		i++;
	return (i);
}
