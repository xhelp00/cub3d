/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilities2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:52:31 by nroth             #+#    #+#             */
/*   Updated: 2023/02/07 16:52:33 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	evacuate(void *ptr, void *ptr2)
{
	free(ptr);
	free(ptr2);
	return (-1);
}

void	reset_to_0(int *n1, int *n2)
{
	*n1 = 0;
	*n2 = 0;
}

void	add_neg_back(t_format *print_format, char **toprint)
{
	char	*newstr;

	if (print_format->sign < 0)
	{
		newstr = ft_strjoin("-", *toprint);
		free(*toprint);
		*toprint = newstr;
		print_format->sign = 1;
	}
}
