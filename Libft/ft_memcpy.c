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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_p;

	dest_p = dest;
	if (!dest && !src)
		return (dest);
	while (n)
	{
		n--;
		*(dest_p + n) = *(char *)(src + n);
	}
	return (dest);
}
