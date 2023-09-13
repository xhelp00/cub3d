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

#include "ft_printf.h"

char	*print_char(int i)
{
	char	*res;

	res = ft_strdup(" ");
	res[0] = i;
	return (res);
}

char	*print_str(char *s)
{
	if (!s)
		return (ft_strdup("(null)"));
	return (ft_strdup(s));
}

char	*print_int(int num)
{
	return (ft_itoa(num));
}

char	*print_unsigned_int(unsigned int num)
{
	return (unsigned_itoa(num));
}

void	ft_write(char *s, int s_len)
{
	while (s_len)
	{
		write(1, s, 1);
		s++;
		s_len--;
	}
}
