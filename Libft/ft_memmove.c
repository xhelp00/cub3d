/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:50:22 by nroth             #+#    #+#             */
/*   Updated: 2022/10/15 10:50:30 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_p;
	size_t	i;

	dest_p = dest;
	i = 0;
	if (!dest && !src)
		return (dest);
	if (dest > src)
		ft_memcpy(dest, src, n);
	else
	{
		while (i < n)
		{
			*(dest_p + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dest);
}
