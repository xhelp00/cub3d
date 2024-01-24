/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   items.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/25 18:01:31 by jbartosi         ###   ########.fr       */
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

t_item	*last_item(t_item *i)
{
	if (!i)
		return (NULL);
	while (i->next)
		i = i->next;
	return (i);
}

void	item_add_back(t_box *box, t_item *new)
{
	if (box->items == NULL)
		box->items = new;
	else
	{
		new->prev = last_item(box->items);
		last_item(box->items)->next = new;
	}
}

t_item	*find_item(t_box *box, int id)
{
	t_item	*items;

	items = box->items;
	if (!items)
		return (NULL);
	while (items)
	{
		if (items->data->id == id)
			return (items);
		items = items->next;
	}
	return (NULL);
}

void	item_append(t_box *box, t_sprite *sprite)
{
	t_item	*new;

	new = new_item();
	new->data->id = sprite->data->id;
	new->data->texture = ITEMS;
	item_add_back(box, new);
	sprite_remove(box, sprite);
}

void	item_remove(t_box *box, t_item *to_rem)
{
	if (to_rem == box->items)
		box->items = box->items->next;
	else
		to_rem->prev->next = to_rem->next;
	if (to_rem->next)
		to_rem->next->prev = to_rem->prev;
	free(to_rem->data);
	free(to_rem);
}
