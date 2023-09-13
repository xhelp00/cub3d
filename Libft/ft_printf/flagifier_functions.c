/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:31:31 by nroth             #+#    #+#             */
/*   Updated: 2023/01/13 13:31:32 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	add_sign(char type, int sign_pref, char **toprint)
{
	char	*newstr;

	if (type != 'd'
		&& type != 'i')
		return (-1);
	if (ft_isdigit(**toprint))
	{
		if (sign_pref == 1)
			newstr = ft_strjoin("+", *toprint);
		else
			newstr = ft_strjoin(" ", *toprint);
		free(*toprint);
		*toprint = newstr;
	}
	return (0);
}

int	add_hex_pre(char type, char **toprint)
{
	char	*newstr;

	if (type != 'x' && type != 'X')
		return (-1);
	if (!ft_memcmp(*toprint, "0", 2))
		return (0);
	if (type == 'X')
		newstr = ft_strjoin("0X", *toprint);
	else
		newstr = ft_strjoin("0x", *toprint);
	free(*toprint);
	*toprint = newstr;
	return (0);
}
