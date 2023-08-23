/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:41:11 by phelebra          #+#    #+#             */
/*   Updated: 2023/01/19 09:57:54 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	m;

	if (n < 0)
	{
		m = -n;
		write (fd, "-", 1);
	}
	else
		m = n;
	if (m >= 10)
	{
		ft_putnbr_fd(m / 10, fd);
		ft_putnbr_fd(m % 10, fd);
	}	
	if (m < 10)
	{
		m += '0';
		write (fd, &m, 1);
	}
}
