/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_seg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*find_seg(t_box *box, int seg)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if (sprites->data->seg == seg && (sprites->data->texture
				== LARRY_JR_BODY || sprites->data->texture == LARRY_JR_HEAD))
			return (sprites);
		sprites = sprites->next;
	}
	return (sprites);
}

t_sprite	*find_door(t_box *box, int x, int y)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	if (!sprites)
		return (NULL);
	while (sprites)
	{
		if (sprites->data->x == x && sprites->data->y == y
			&& sprites->data->texture == DOOR)
			return (sprites);
		sprites = sprites->next;
	}
	return (NULL);
}

t_sprite	*find_next_seg(t_box *box, int target_seg)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if (sprites->data->seg == target_seg)
		{
			return (sprites);
		}
		sprites = sprites->next;
	}
	return (NULL);
}

void	decrement_segments(t_box *box, int seg_limit)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if ((sprites->data->texture == LARRY_JR_HEAD || sprites->data->texture
				== LARRY_JR_BODY)
			&& sprites->data->seg > seg_limit)
		{
			sprites->data->seg--;
		}
		sprites = sprites->next;
	}
}

void	update_total_segments(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if (sprites->data->texture == LARRY_JR_HEAD || sprites->data->texture
			== LARRY_JR_BODY)
		{
			sprites->data->n_seg--;
		}
		sprites = sprites->next;
	}
}
