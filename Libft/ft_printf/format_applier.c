/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_applier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:06:19 by nroth             #+#    #+#             */
/*   Updated: 2023/02/04 12:06:21 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	add_actual_padding(char *toprint, t_format print_format,
		char type, char **padding)
{
	int	padding_len;

	padding_len = print_format.wdt - ft_special_strlen(toprint, type);
	while (padding_len--)
	{
		if (print_format.zero && print_format.pnt && print_format.prc != -1)
			ft_strappend(padding, " ");
		else if (print_format.zero && !ft_strchr("sc", type))
			ft_strappend(padding, "0");
		else
			ft_strappend(padding, " ");
	}
}

int	add_padding(t_format print_format, char type, char **toprint)
{
	char	*padding;
	char	*padded_toprint;

	padding = NULL;
	if (print_format.zero
		&& print_format.pnt && print_format.prc != -1
		&& !ft_strchr("sc", type))
		add_neg_back(&print_format, toprint);
	if (print_format.sign < 0 && print_format.wdt && print_format.prc > 0)
		print_format.wdt--;
	else if (print_format.sign < 0 && print_format.zero
		&& print_format.prc != -1)
		print_format.wdt--;
	if (print_format.wdt > ft_special_strlen(*toprint, type))
	{
		add_actual_padding(*toprint, print_format, type, &padding);
		if (print_format.dash && !print_format.zero)
			padded_toprint = ft_strjoin(*toprint, padding);
		else
			padded_toprint = ft_strjoin(padding, *toprint);
		evacuate(*toprint, padding);
		*toprint = padded_toprint;
	}
	return (0);
}

void	add_precision(t_format print_format, char type, char **toprint)
{
	char	*new_str;

	if (type == 's')
	{
		if ((int) ft_strlen(*toprint) <= print_format.prc)
			return ;
		new_str = ft_calloc(print_format.prc, sizeof(char));
		ft_strlcpy(new_str, *toprint, print_format.prc + 1);
		free(*toprint);
		*toprint = new_str;
		return ;
	}
	if (print_format.prc == 0 && !ft_strncmp(*toprint, "0", 2))
	{
		new_str = ft_strdup("");
		free(*toprint);
		*toprint = new_str;
	}
	else if (print_format.prc >= (int) ft_strlen(*toprint))
	{
		print_format.zero = 1;
		print_format.wdt = print_format.prc;
		print_format.prc = -1;
		add_padding(print_format, type, toprint);
	}
}

int	add_padding_null(t_format print_format, char **toprint)
{
	int		padding_len;
	char	*padding;

	padding = NULL;
	padding_len = print_format.wdt;
	while (padding_len--)
		ft_strappend(&padding, " ");
	if (print_format.dash)
		padding[0] = '\0';
	else
		padding[print_format.wdt - 1] = '\0';
	free(*toprint);
	*toprint = padding;
	return (0);
}

int	apply_formats(t_format print_format, char type, char **toprint)
{
	int	is_null_char;
	int	top_strlen;

	reset_to_0(&is_null_char, &top_strlen);
	if (type == 'c' && !**toprint)
		is_null_char = 1;
	if (print_format.pnt)
		add_precision(print_format, type, toprint);
	if (print_format.sign_pref && print_format.sign >= 0)
		add_sign(type, print_format.sign_pref, toprint);
	if (print_format.hash && print_format.sign)
		add_hex_pre(type, toprint);
	if (print_format.wdt && is_null_char == 1)
		add_padding_null(print_format, toprint);
	if (print_format.wdt && !is_null_char)
		add_padding(print_format, type, toprint);
	if (print_format.sign < 0 && !ft_strchr(*toprint, '-'))
		add_neg_back(&print_format, toprint);
	if (!ft_strlen(*toprint))
		top_strlen += ft_strlen((*toprint + 1));
	else
		top_strlen += ft_strlen((*toprint));
	return (top_strlen + is_null_char);
}
