/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:37:22 by nroth             #+#    #+#             */
/*   Updated: 2023/01/11 15:37:24 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int		res;
	int		sign;
	size_t	counter;

	res = 0;
	sign = 1;
	counter = 0;
	while ((nptr[counter] >= 9 && nptr[counter] <= 13)
		|| nptr[counter] == ' ')
		counter++;
	if (nptr[counter] == '-'
		|| nptr[counter] == '+')
		sign = 44 - nptr[counter++];
	while (counter < ft_strlen(nptr) && ft_isdigit(nptr[counter]))
	{
		res = (res * 10) + (nptr[counter] - '0');
		counter++;
	}
	return (res * sign);
}
