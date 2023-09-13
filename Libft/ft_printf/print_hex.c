/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:16:52 by nroth             #+#    #+#             */
/*   Updated: 2023/01/31 16:16:57 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	hex_add_digit(unsigned int num, char cap,
	char *res_ptr, int num_len)
{
	unsigned int	div;
	unsigned int	mod;
	char			*last;

	div = num / 16;
	mod = num % 16;
	if (!res_ptr)
		return ;
	last = ft_strchr(res_ptr, '\0');
	if (div >= 16)
	{
		hex_add_digit(div, cap, res_ptr, num_len);
		last = ft_strchr(res_ptr, '\0');
	}
	else if (div)
	{
		*last = HEX_SMOL[div];
		if (cap == 'X')
			*last = HEX_CAP[div];
		last = ft_strchr(res_ptr, '\0');
	}
	*last = HEX_SMOL[mod];
	if (cap == 'X')
		*last = HEX_CAP[mod];
}
/*
	type is X if capital, x if small
*/

char	*print_hex(unsigned int num, char type)
{
	int		num_len;
	char	*res;

	num_len = 1;
	if (num == (unsigned int)-1)
		num_len = 8;
	else
	{
		while (num / ft_unsigned_pow(16, num_len - 1) >= 16)
			num_len++;
	}
	res = ft_calloc(num_len + 1, sizeof(char));
	if (!res)
		return (NULL);
	hex_add_digit(num, type, res, num_len);
	return (res);
}
