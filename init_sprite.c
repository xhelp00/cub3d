/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_data(t_sprite *new)
{
	new->data->x = 0;
	new->data->y = 0;
	new->data->start_x = 0;
	new->data->start_y = 0;
	new->data->travel = 0;
	new->data->hp = 100;
	new->data->texture = 0;
	new->data->dir_x = 0;
	new->data->dir_y = 0;
	new->data->state = 0;
	new->data->frame = 0;
	new->data->n_seg = 0;
	new->data->start_n_seg = 0;
	new->data->seg = 0;
	new->data->hit = 0;
	new->data->id = 0;
	new->data->sound = 0;
	new->data->opening = 0;
	new->data->state = IDLE;
	new->next = NULL;
	new->prev = NULL;
}

t_sprite	*new_sprite(void)
{
	t_sprite	*new;

	new = ft_calloc(1, sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->data = ft_calloc(1, sizeof(t_sprite_data));
	if (!new->data)
		return (NULL);
	set_data(new);
	return (new);
}

t_sprite	*last_sprite(t_sprite *s)
{
	if (!s)
		return (NULL);
	while (s->next)
		s = s->next;
	return (s);
}

void	sprite_add_back(t_box *box, t_sprite *new)
{
	if (new->data->texture == LARRY_JR_HEAD)
	{
		new->data->n_seg = 5;
		new->data->start_n_seg = 5;
	}
	if (box->sprites == NULL)
		box->sprites = new;
	else
	{
		new->prev = last_sprite(box->sprites);
		last_sprite(box->sprites)->next = new;
	}
}

void	sprite_append(t_box *box, float x, float y, int texture)
{
	t_sprite	*new;

	new = new_sprite();
	new->data->x = x;
	new->data->y = y;
	new->data->start_x = x;
	new->data->start_y = y;
	if (texture > 50)
	{
		new->data->id = texture - 100;
		new->data->texture = ITEMS;
	}
	else
		new->data->texture = texture;
	new->data->dir_x = box->info.dir_x;
	new->data->dir_y = box->info.dir_y;
	sprite_add_back(box, new);
}
