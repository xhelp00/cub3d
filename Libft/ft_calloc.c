/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 16:16:24 by nroth             #+#    #+#             */
/*   Updated: 2023/01/11 16:16:25 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res;

	if (nmemb && size)
	{
		if ((nmemb * size) / size != nmemb)
			return (NULL);
	}
	res = malloc(size * nmemb);
	if (!res)
		return (NULL);
	ft_bzero(res, size * nmemb);
	return (res);
}
