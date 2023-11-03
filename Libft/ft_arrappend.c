/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	appends item to char * array and re allocates the space.
	original arr is freed
	NOTE: ITEM has to be freeable
	CREDITS for nroth <3
*/
char	**ft_arrappend(char **arr, char *to_append)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc (sizeof (char *) * (ft_arrlen((void **) arr) + 2));
	while (arr && arr[i])
	{
		ret[i] = arr[i];
		i++;
	}
	ret [i] = to_append;
	ret [i + 1] = NULL;
	free (arr);
	arr = ret;
	return (ret);
}
