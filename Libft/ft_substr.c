/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:16:12 by nroth             #+#    #+#             */
/*   Updated: 2023/01/12 14:16:13 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (!s)
		return (NULL);
	if (start + 1 > ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	else if (ft_strlen(s) - (start) < len)
		substr = ft_calloc((ft_strlen(s) - (start) + 1), sizeof (char));
	else
		substr = ft_calloc((len + 1), sizeof(char));
	if (!substr)
		return (NULL);
	ft_strlcpy (substr, (char *) s + start, len + 1);
	return (substr);
}
