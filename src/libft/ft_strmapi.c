/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:49:18 by phelebra          #+#    #+#             */
/*   Updated: 2023/01/23 09:11:44 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * len + 1);
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = f((unsigned int)i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
