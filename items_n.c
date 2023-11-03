/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_item	*new_item(void)
{
	t_item	*new;

	new = ft_calloc(1, sizeof(t_item));
	if (!new)
		return (NULL);
	new->data = ft_calloc(1, sizeof(t_item_data));
	if (!new->data)
		return (NULL);
	new->data->id = 0;
	new->data->texture = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
