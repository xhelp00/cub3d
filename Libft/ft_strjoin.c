/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:40:22 by nroth             #+#    #+#             */
/*   Updated: 2023/01/12 14:40:28 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret_str;
	int		tot_len;

	tot_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret_str = ft_calloc(tot_len, sizeof(char));
	if (!ret_str)
		return (NULL);
	ft_strlcat(ret_str, (char *)s1, tot_len);
	ft_strlcat(ret_str, (char *)s2, tot_len);
	return (ret_str);
}
