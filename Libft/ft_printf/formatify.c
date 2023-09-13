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

static void	flagifier_2(char *typestr, t_format **print__format, char *toprint)
{
	int			i;
	t_format	*print_format;
	char		type;

	type = typestr[ft_strlen(typestr) - 1];
	print_format = *print__format;
	if (ft_strchr("id", type) && ft_atoi(toprint) < 0)
		print_format->sign = -1;
	else if (ft_strchr("uXx", type) || ft_atoi(toprint) > 0)
		print_format->sign = 1;
	i = -1;
	while (ft_isdigit(typestr[++i]) || typestr[i] == '.')
	{
		if (typestr[i] == '.')
		{
			print_format->pnt = 1;
			print_format->prc = ft_atoi(&typestr[i + 1]);
			i += num_len(print_format->prc);
		}
		else if (!print_format->pnt)
		{
			print_format->wdt = ft_atoi(&typestr[i]);
			i += num_len(print_format->wdt) - 1;
		}
	}
}

t_format	*flagifier(char *typestr, char *toprint)
{
	t_format	*print_format;
	int			i;

	i = -1;
	print_format = ft_calloc(1, sizeof(t_format));
	if (!print_format)
		return (NULL);
	while (ft_strchr(F_FLGS, typestr[++i]) && typestr[i] != '.')
	{
		if (typestr[i] == '0')
			print_format->zero = 1;
		if (typestr[i] == '+' && !print_format->sign_pref)
			print_format->sign_pref = 1;
		if (typestr[i] == ' ' && !print_format->sign_pref)
			print_format->sign_pref = 2;
		if (typestr[i] == '#')
			print_format->hash = 1;
		if (typestr[i] == '-')
			print_format->dash = 1;
	}
	flagifier_2(&typestr[i], &print_format, toprint);
	return (print_format);
}

int	check_if_ok(t_format **print_format, char **toprint)
{
	char	*newstr;

	if ((*print_format)->sign < 0
		&& ((*print_format)->prc || (*print_format)->zero))
	{
		newstr = ft_substr(*toprint, 1, ft_strlen(*toprint) - 1);
		free(*toprint);
		*toprint = newstr;
	}
	return (0);
}

int	formatify(char *typestr, char **toprint, int *toprint_len)
{
	t_format	*print_format;
	int			stat;
	char		type;

	type = typestr[ft_strlen(typestr) - 1];
	*toprint_len = 0;
	print_format = flagifier(typestr, *toprint);
	if (!print_format || check_if_ok(&print_format, toprint) == -1)
		return (-1);
	if (!ft_strncmp(*toprint, "(null)", 7)
		&&print_format->pnt && print_format->prc < 6)
	{
		free(*toprint);
		*toprint = ft_strdup("");
	}
	stat = apply_formats(*print_format, type, toprint);
	if (stat == -1)
		return (-1);
	*toprint_len += stat;
	free(print_format);
	return (0);
}
