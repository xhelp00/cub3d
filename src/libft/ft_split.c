/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:39:39 by phelebra          #+#    #+#             */
/*   Updated: 2023/01/23 09:56:43 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static int	ft_wordcount(char const *s, char c)
{
	int	wordcount;
	int	i;

	wordcount = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			wordcount++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (wordcount);
}

static int	ft_size_word(char const *s, char c)
{
	int	size;

	size = 0;
	while (s[size] != c && s[size])
	{
		size++;
	}
	return (size);
}

static void	ft_free(char **strs, int j)
{
	while (j-- > 0)
		free(strs[j]);
	free(strs);
}

static char	**ft_fill(char **new, const char *str, char c, int count)
{
	int	words;
	int	len;
	int	i;

	i = 0;
	words = 0;
	while (words < count)
	{
		while (str[i] == c)
			i++;
		len = ft_size_word(&str[i], c);
		new[words] = ft_substr(str, i, len);
		if (!new[words])
		{
			ft_free(new, words);
			return (NULL);
		}
		while (str[i] && str[i] != c)
			i++;
		words++;
	}
	new[words] = NULL;
	return (new);
}

char	**ft_split(const char *str, char c)
{
	int		count;
	char	**new;

	if (!str)
		return (NULL);
	count = ft_wordcount(str, c);
	new = malloc ((count + 1) * sizeof(char **));
	if (!new)
		return (NULL);
	return (ft_fill(new, str, c, count));
}
