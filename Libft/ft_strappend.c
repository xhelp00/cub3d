/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 12:10:46 by nroth             #+#    #+#             */
/*   Updated: 2023/02/14 12:10:47 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*str_append(char *s1, char *s2, char *spacer)
{
	char	*res;
	char	*temp;

	if (spacer)
		temp = ft_strjoin (s1, spacer);
	else
		temp = ft_strdup(s1);
	res = ft_strjoin (temp, s2);
	free (temp);
	free (s1);
	return (res);
}
