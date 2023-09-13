/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:48:09 by nroth             #+#    #+#             */
/*   Updated: 2023/01/12 15:48:10 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_wc(char *s, char c)
{
	int	wc;

	wc = 0;
	if (!c || !s || !*s)
		return (0);
	while (s && *s)
	{
		if (*s != c)
		{
			wc++;
			s = ft_strchr(s, c);
		}
		else
			while (*s == c)
				s++;
	}
	return (wc);
}

static int	evacuate(char **res_arr)
{
	int	i;

	i = 0;
	while (res_arr[i])
		free(res_arr[i++]);
	free(res_arr);
	return (1);
}

static int	write_split(char **res_arr, char *s, char c)
{
	int		i;
	int		res_ctr;
	int		w_len;

	i = 0;
	res_ctr = 0;
	while (s && s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		if (ft_strchr(&s[i], c))
			w_len = ft_strchr(&s[i], c) - &s[i];
		else
			w_len = ft_strlen(&s[i]);
		res_arr[res_ctr] = ft_calloc(sizeof(char), w_len + 1);
		if (!res_arr[res_ctr])
			return (evacuate(res_arr));
		ft_strlcpy (res_arr[res_ctr++], (char *)s + i, (size_t)w_len + 1);
		i += w_len;
	}
	res_arr[res_ctr] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**res_arr;

	res_arr = ft_calloc(sizeof(char *), get_wc((char *)s, c) + 1);
	if (!res_arr)
		return (NULL);
	if (write_split(res_arr, (char *)s, c) == 1)
		return (NULL);
	return (res_arr);
}
