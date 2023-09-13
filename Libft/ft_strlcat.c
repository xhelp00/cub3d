/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 12:02:10 by nroth             #+#    #+#             */
/*   Updated: 2023/01/11 12:02:14 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	src_cnt;
	unsigned int	dest_cnt;
	size_t			ret_val;

	if (!dest && !size)
		return (0);
	dest_cnt = ft_strlen(dest);
	src_cnt = 0;
	if (size > ft_strlen(dest))
		ret_val = ft_strlen(src) + ft_strlen(dest);
	else
		return (ft_strlen(src) + size);
	if (!size)
		return (ret_val);
	while (src[src_cnt]
		&& dest_cnt + 1 < size)
	{
		dest[dest_cnt] = src[src_cnt];
		src_cnt++;
		dest_cnt++;
	}
	dest[dest_cnt] = '\0';
	return (ret_val);
}
