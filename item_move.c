/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_item(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	data->frame = calculate_frame_time(box, data);
	if (data->dist < 0.1)
	{
		apply_item_effects(box, data->id);
		item_append(box, sprites);
		return (0);
	}
	return (1);
}

int	handle_key(t_box *box, t_sprite *sprites)
{
	box->player.n_key++;
	box->p = music(box->env, "sounds/key.mp3");
	sprite_remove(box, sprites);
	return (0);
}

int	handle_trophy(t_box *box, t_sprite *sprites)
{
	printf("YOU WIN!!!\n");
	box->p = music(box->env, "sounds/fanfare.mp3");
	sprite_remove(box, sprites);
	box->won = 1;
	gettimeofday(&box->fin_time, NULL);
	return (0);
}

int	handle_door(t_box *box, t_sprite_data *data)
{
	if (data->opening)
	{
		data->frame = ((((box->time.tv_sec - data->action_time.tv_sec)
						+ ((box->time.tv_usec - data->action_time.tv_usec)
							/ 1000000.0)) * 10) * 16) / 10;
		if (data->frame > 32)
		{
			data->opening = 0;
			if (data->state == CLOSE)
				data->state = OPEN;
		}
	}
	return (1);
}
