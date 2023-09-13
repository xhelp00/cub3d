/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:53:16 by nroth             #+#    #+#             */
/*   Updated: 2023/01/11 12:53:18 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			counter;
	unsigned char	s1_c;
	unsigned char	s2_c;

	counter = 0;
	while (counter < n)
	{
		s1_c = *(unsigned char *)(s1 + counter);
		s2_c = *(unsigned char *)(s2 + counter);
		if (s1_c - s2_c)
			return (s1_c - s2_c);
		counter++;
	}
	return (0);
}
