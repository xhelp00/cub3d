/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:41:54 by nroth             #+#    #+#             */
/*   Updated: 2023/01/14 14:41:55 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	if (power == 0)
		return (1);
	return (nb * ft_pow(nb, power - 1));
}

static int	ft_abs(int nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

static void	add_digit_fd(int fd, int n, int n_len)
{
	int	factor;
	int	digit;

	digit = '-';
	factor = ft_pow(10, n_len - 1);
	if (n < 0)
	{
		n *= -1;
		write(fd, &digit, sizeof(char));
	}
	while (n_len)
	{
		digit = 0;
		while (n >= factor)
		{
			digit += 1;
			n -= factor;
		}
		digit += '0';
		write(fd, &digit, sizeof(char));
		n_len--;
		factor /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	int	n_len;

	n_len = 1;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	while (ft_abs(n) / ft_pow(10, n_len - 1) >= 10)
		n_len++;
	add_digit_fd(fd, n, n_len);
}
