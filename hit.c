/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_player_frame_when_hit(t_box *box)
{
	box->player.frame = ((((box->time.tv_sec - box->player.hit_time.tv_sec)
					+ ((box->time.tv_usec - box->player.hit_time.tv_usec)
						/ 1000000.0)) * 10) * 16) / 10;
	if (box->player.frame > 20)
		box->player.hit = 0;
	return (1);
}

int	handle_player_getting_hit(t_box *box)
{
	box->player.hit = 1;
	if (box->god == 0 && !box->won && !box->lost)
	{
		box->player.hp -= 1;
		if (box->player.hp < 1)
		{
			box->lost = 1;
			printf("YOU ARE DEAD!!!\n");
			box->p = music(box->env, "sounds/fail.mp3");
			gettimeofday(&box->fin_time, NULL);
			return (0);
		}
		box->p = music(box->env, "sounds/ow.mp3");
	}
	gettimeofday(&box->player.hit_time, NULL);
	return (1);
}

int	handle_tear(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	if (data->hit)
	{
		return (check_frame_and_remove(box, data, sprites));
	}
	else if (check_collision_with_map(box, data)
		|| check_collision_with_door(box, data)
		|| data->travel > box->player.range / 5.0
		|| check_collision_sprites(box, data, sprites))
	{
		sprite_hit(box, sprites, NULL);
		return (0);
	}
	else
	{
		data->x += data->dir_x * box->info.move_speed * (box->player.shot_speed
				/ 8.0);
		data->y += data->dir_y * box->info.move_speed * (box->player.shot_speed
				/ 8.0);
	}
	return (1);
}

double	calculate_frame_time(t_box *box, t_sprite_data *data)
{
	return (((((box->time.tv_sec - data->hit_time.tv_sec)
					+ ((box->time.tv_usec - data->hit_time.tv_usec)
						/ 1000000.0)) * 10) * 16) / 10);
}

void	apply_item_effects(t_box *box, int item_id)
{
	if (item_id == 0)
		box->player.fire_rate -= box->player.fire_rate / 10;
	else if (item_id == 3)
	{
		box->player.dmg += 5;
		if (!find_item(box, 11) && !find_item(box, 3))
			box->player.dmg *= 1.5;
	}
	else if (item_id == 5)
	{
		box->player.fire_rate /= 2;
		box->player.range /= 1.5;
	}
	else if (item_id == 6)
		box->player.dmg += 10;
	else if (item_id == 11)
	{
		box->player.max_hp += 2;
		box->player.hp = box->player.max_hp;
		box->player.dmg += 3;
		if (!find_item(box, 3) && !find_item(box, 11))
			box->player.dmg *= 1.5;
		box->player.range += 15;
		box->player.speed += 30;
	}
}
