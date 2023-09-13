/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:57:13 by nroth             #+#    #+#             */
/*   Updated: 2023/01/12 14:57:15 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static size_t	spec_strlen(char *str, char *set)
{
	size_t	counter;
	size_t	i;

	i = 0;
	counter = ft_strlen(str);
	while (i < ft_strlen(str))
	{
		if (ft_strchr(set, str[i]))
			counter--;
		else
			break ;
		i++;
	}
	if (!counter)
		return (counter);
	i = ft_strlen(str);
	while (--i)
	{
		if (ft_strchr(set, str[i]))
			counter--;
		else
			break ;
	}
	return (counter);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*substr;
	size_t	substr_ctr;
	size_t	i;
	size_t	reduced_strlen;

	if (!s1)
		return (NULL);
	reduced_strlen = spec_strlen((char *)s1, (char *)set);
	substr = ft_calloc(reduced_strlen + 1, sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	substr_ctr = 0;
	while (ft_strchr(set, s1[i]))
		i++;
	while (substr_ctr < reduced_strlen)
		substr[substr_ctr++] = s1[i++];
	return (substr);
}
