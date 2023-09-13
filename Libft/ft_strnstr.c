/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:53:35 by nroth             #+#    #+#             */
/*   Updated: 2023/01/11 14:53:36 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_counter;

	if (!*little)
		return ((char *) big);
	if (!big && !len)
		return (NULL);
	while ((*big || *(big - 1)) && len)
	{
		little_counter = 0;
		if (*big == little[little_counter]
			&& ft_strlen(little) <= len)
		{
			while (big[little_counter] == little[little_counter]
				&& little[little_counter])
				little_counter++;
			if (little_counter == ft_strlen(little))
				return ((char *)big);
		}
		big++;
		len--;
	}
	return (0);
}
