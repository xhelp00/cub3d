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

static void	ptr_add_digits(unsigned long long num, char *res_ptr)
{
	char	*last;

	if (num >= 16)
	{
		ptr_add_digits(num / 16, res_ptr);
		ptr_add_digits(num % 16, res_ptr);
	}
	else
	{
		last = ft_strchr(res_ptr, '\0');
		*last = HEX_SMOL[num];
	}
}

int	ptr_len(unsigned long long num)
{
	int	len;

	len = 0;
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

char	*print_ptr(unsigned long long ptr)
{
	int		num_len;
	char	*res;

	if (!ptr)
		return (ft_strdup("(nil)"));
	num_len = ptr_len(ptr);
	res = ft_calloc(num_len + 3, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, "0x", 3);
	ptr_add_digits(ptr, res);
	return (res);
}
