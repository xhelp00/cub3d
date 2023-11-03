/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_sprite_distances(t_box *box, t_sprite *sprites)
{
	while (sprites)
	{
		sprites->data->dist = ((box->info.pos_x - sprites->data->x)
				* (box->info.pos_x - sprites->data->x)
				+ (box->info.pos_y - sprites->data->y)
				* (box->info.pos_y - sprites->data->y));
		sprites->data->travel = ((sprites->data->start_x - sprites->data->x)
				* (sprites->data->start_x - sprites->data->x)
				+ (sprites->data->start_y - sprites->data->y)
				* (sprites->data->start_y - sprites->data->y));
		sprites = sprites->next;
	}
}

void	inner_bubble_sort(t_sprite *sprites)
{
	t_sprite	*tmp;

	tmp = sprites;
	while (tmp->next)
	{
		if (tmp->data->dist < tmp->next->data->dist)
			swap(tmp);
		tmp = tmp->next;
	}
}

void	outer_bubble_sort(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		inner_bubble_sort(sprites);
		sprites = sprites->next;
	}
}

void	bubble_sort_sprites(t_box *box)
{
	calc_sprite_distances(box, box->sprites);
	outer_bubble_sort(box);
}

void	swap(t_sprite *x)
{
	t_sprite_data	*tmp;

	if (!x || (x->data == NULL && x->next == NULL))
		return ;
	tmp = x->data;
	x->data = x->next->data;
	x->next->data = tmp;
}
