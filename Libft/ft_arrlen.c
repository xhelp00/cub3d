/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 08:56:59 by nroth             #+#    #+#             */
/*   Updated: 2022/10/14 08:57:05 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen(void **s)
{
	unsigned long	length;

	if (!s)
		return (0);
	length = 0;
	while ((char *) s[length] != NULL)
		length++;
	return (length);
}
