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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			counter;
	unsigned char	chars[2];

	counter = 0;
	while (counter < n && (s1[counter] || s2[counter]))
	{
		chars[0] = s1[counter];
		chars[1] = s2[counter];
		if (chars[0] - chars[1])
			return ((chars[0] - chars[1]));
		counter++;
	}
	return (0);
}
