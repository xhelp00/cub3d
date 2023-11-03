/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_hit(t_box *box, t_sprite *who, t_sprite *what)
{
	if (what == NULL)
	{
		who->data->hit = 1;
		box->p = music(box->env, "sounds/splash.mp3");
		gettimeofday(&who->data->hit_time, NULL);
	}
	else
	{
		who->data->hit = 1;
		gettimeofday(&who->data->hit_time, NULL);
		box->p = music(box->env, "sounds/splash.mp3");
		what->data->hit = 1;
		box->p = music(box->env, "sounds/splash.mp3");
		gettimeofday(&what->data->hit_time, NULL);
		what->data->hp -= box->player.dmg;
		box->p = music(box->env, "sounds/pain.mp3");
		if (what->data->hp < 1)
		{
			box->p = music(box->env, "sounds/die.mp3");
			if (what->data->texture > DOOR && what->data->texture <= ISAAC)
				sprite_append(box, what->data->x, what->data->y, KEY);
			sprite_remove(box, what);
		}
	}
}

void	enemy_angle(t_box *box, t_sprite_data *data)
{
	box->info.t_angle = atan2(data->y - box->info.pos_y,
			data->x - box->info.pos_x);
	box->info.now_angle = atan2(data->dir_y, data->dir_x)
		- atan2(box->info.start_dir_y, box->info.start_dir_x);
	if (box->info.t_angle < 0)
		box->info.t_angle += 2 * PI;
	if (box->info.now_angle < 0)
		box->info.now_angle += 2 * PI;
	if (box->info.now_angle < box->info.t_angle || fabs(box->info.now_angle
			* (180 / PI) - box->info.t_angle * (180 / PI)) > 180)
	{
		box->info.old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(box->info.rot_speed
				* 0.5) - data->dir_y * sin(box->info.rot_speed * 0.5);
		data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed
				* 0.5) + data->dir_y * cos(box->info.rot_speed * 0.5);
	}
	else
	{
		box->info.old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-box->info.rot_speed
				* 0.5) - data->dir_y * sin(-box->info.rot_speed * 0.5);
		data->dir_y = box->info.old_dir_x * sin(-box->info.rot_speed
				* 0.5) + data->dir_y * cos(-box->info.rot_speed * 0.5);
	}
}

void	body_angle(t_box *box, t_sprite_data *data)
{
	box->info.t_angle = atan2(data->y - find_seg(box, data->seg - 1)->data->y,
			data->x - find_seg(box, data->seg - 1)->data->x);
	box->info.now_angle = atan2(data->dir_y, data->dir_x)
		- atan2(box->info.start_dir_y, box->info.start_dir_x);
	if (box->info.t_angle < 0)
		box->info.t_angle += 2 * PI;
	if (box->info.now_angle < 0)
		box->info.now_angle += 2 * PI;
	if (box->info.now_angle < box->info.t_angle || fabs(box->info.now_angle
			* (180 / PI) - box->info.t_angle * (180 / PI)) > 180)
	{
		box->info.old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(box->info.rot_speed * 0.5) - data->dir_y
			* sin(box->info.rot_speed * 0.5);
		data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed * 0.5)
			+ data->dir_y * cos(box->info.rot_speed * 0.5);
	}
	else
	{
		box->info.old_dir_x = data->dir_x;
		data->dir_x = data->dir_x * cos(-box->info.rot_speed * 0.5)
			- data->dir_y * sin(-box->info.rot_speed * 0.5);
		data->dir_y = box->info.old_dir_x * sin(-box->info.rot_speed * 0.5)
			+ data->dir_y * cos(-box->info.rot_speed * 0.5);
	}
}

void	enemy_move(t_box *box, t_sprite_data *data)
{
	if (((box->map[(int)(data->x + data->dir_x
					* box->info.ene_move_speed)][(int)data->y] == '0')
		|| (box->map[(int)(data->x + data->dir_x
		* box->info.move_speed)][(int)data->y] == '0' + DOOR + 1
		&& find_door(box, (int)(data->x + data->dir_x * box->info.move_speed),
			(int)data->y)->data->state == OPEN))
		&& ((box->map[(int)(data->x)][(int)(data->y + data->dir_y
			* box->info.ene_move_speed)] == '0')
		|| (box->map[(int)(data->x)][(int)(data->y + data->dir_y
			* box->info.ene_move_speed)] == '0' + DOOR + 1
		&& find_door(box, (int)(data->x), (int)(data->y + data->dir_y
			* box->info.ene_move_speed))->data->state == OPEN)))
	{
		data->x += data->dir_x * 0.1 * box->info.ene_move_speed;
		data->y += data->dir_y * 0.1 * box->info.ene_move_speed;
	}
}
