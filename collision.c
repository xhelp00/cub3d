/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player_hit(t_box *box, t_sprite_data *data)
{
	if (box->player.hit)
		return (update_player_frame_when_hit(box));
	else if (data->dist < 0.1)
		return (handle_player_getting_hit(box));
	return (1);
}

int	check_frame_and_remove(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	data->frame = ((((box->time.tv_sec - data->hit_time.tv_sec)
					+((box->time.tv_usec - data->hit_time.tv_usec) / 1000000.0))
				* 10) * 16) / 10;
	if (data->frame > 14)
	{
		sprite_remove(box, sprites);
		return (0);
	}
	return (1);
}

int	check_collision_with_map(t_box *box, t_sprite_data *data)
{
	if ((box->map[(int)(data->x + data->dir_x * box->info.move_speed)][(int)data
		->y] > '0'
		&& box->map[(int)(data->x + data->dir_x * box->info.move_speed)]
			[(int)data->y] != '0' + DOOR + 1)
		|| (box->map[(int)(data->x)][(int)(data->y + data->dir_y * box->info
			.move_speed)] > '0'
		&& box->map[(int)(data->x)][(int)(data->y + data->dir_y * box->info
			.move_speed)] != '0' + DOOR + 1))
		return (1);
	return (0);
}

int	check_collision_with_door(t_box *box, t_sprite_data *data)
{
	if ((find_door(box, (int)data->x, (int)data->y + data->dir_y * box->info
				.move_speed) && find_door(box, (int)data->x, (int)data->y
				+ data->dir_y * box->info.move_speed)->data->state != OPEN)
		|| (find_door(box, (int)(data->x + data->dir_x * box->info.move_speed),
			(int)data->y)
		&& find_door(box, (int)(data->x + data->dir_x * box->info.move_speed),
		(int)data->y)->data->state != OPEN))
		return (1);
	return (0);
}

int	check_collision_sprites(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	t_sprite	*obj;

	obj = box->sprites;
	while (obj)
	{
		if (1 > ((obj->data->x - data->x) * (obj->data->x - data->x)
				+ (obj->data->y - data->y)
				* (obj->data->y - data->y)) * 100 && obj->data->texture < TEAR
			&& obj->data->hit == 0)
		{
			sprite_hit(box, sprites, obj);
			return (1);
		}
		obj = obj->next;
	}
	return (0);
}
