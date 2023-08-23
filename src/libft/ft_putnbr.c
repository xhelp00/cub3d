/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:32:27 by phelebra          #+#    #+#             */
/*   Updated: 2023/02/10 12:51:44 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_putnbr(int i)
{
	char	*s;
	int		size;

	s = ft_itoa(i);
	size = ft_putstr(s);
	free(s);
	return (size);
}
