/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 17:04:28 by phelebra          #+#    #+#             */
/*   Updated: 2023/01/16 17:16:28 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstbuffsize)
{
	size_t	i;
	size_t	j;
	size_t	res;

	i = 0;
	j = 0;
	if (!dst && dstbuffsize == 0)
		return (0);
	while (dst[i] && i < dstbuffsize)
		i++;
	j = ft_strlen(src);
	if (dstbuffsize > i)
		res = i + j;
	else
		res = dstbuffsize + j;
	j = 0;
	while (dstbuffsize != 0 && src[j] && i < dstbuffsize - 1)
		dst[i++] = src[j++];
	if (dstbuffsize > i)
		dst[i] = '\0';
	return (res);
}
