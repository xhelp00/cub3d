/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:39:00 by phelebra          #+#    #+#             */
/*   Updated: 2023/01/23 09:26:15 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub;
	unsigned int		i;

	if ((size_t)start + len > ft_strlen(s))
		len = ft_strlen(s) - (size_t)start;
	if ((size_t)start >= ft_strlen(s))
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		sub[0] = 0;
		return (sub);
	}
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start] != '\0' && i < (unsigned int) len)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
