/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrlen .c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	CREDITS for nroth <3
*/
size_t	ft_arrlen(void **s)
{
	unsigned long	length;

	if (!s)
		return (0);
	length = 0;
	while ((char *) s[length] != NULL)
		length++;
	return (length);
}
