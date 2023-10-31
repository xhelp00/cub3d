/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	action_door(t_box *box)
{
	t_sprite	*s;

	s = box->sprites;
	while (s)
	{
		if (s->data->texture == DOOR && s->data->dist < 2 && !s->data->opening
			&& s->data->state == CLOSE && box->player.n_key > 0)
		{
			box->player.n_key--;
			s->data->opening = 1;
			box->p = music(box->env, "sounds/door.mp3");
			gettimeofday(&s->data->action_time, NULL);
		}
		s = s->next;
	}
}

void	rotate_right(t_box *box)
{
	box->info.old_dir_x = box->info.dir_x;
	box->info.dir_x = box->info.dir_x * cos(-box->info.rot_speed
			* box->mouse.xdistance) - box->info.dir_y
		* sin(-box->info.rot_speed * box->mouse.xdistance);
	box->info.dir_y = box->info.old_dir_x * sin(-box->info.rot_speed
			* box->mouse.xdistance) + box->info.dir_y
		* cos(-box->info.rot_speed * box->mouse.xdistance);
	box->info.old_plane_x = box->info.plane_x;
	box->info.plane_x = box->info.plane_x * cos(-box->info.rot_speed
			* box->mouse.xdistance) - box->info.plane_y
		* sin(-box->info.rot_speed * box->mouse.xdistance);
	box->info.plane_y = box->info.old_plane_x * sin(-box->info.rot_speed
			* box->mouse.xdistance) + box->info.plane_y
		* cos(-box->info.rot_speed * box->mouse.xdistance);
}

void	rotate_left(t_box *box)
{
	box->info.old_dir_x = box->info.dir_x;
	box->info.dir_x = box->info.dir_x * cos(box->info.rot_speed
			* box->mouse.xdistance) - box->info.dir_y
		* sin(box->info.rot_speed * box->mouse.xdistance);
	box->info.dir_y = box->info.old_dir_x * sin(box->info.rot_speed
			* box->mouse.xdistance) + box->info.dir_y
		* cos(box->info.rot_speed * box->mouse.xdistance);
	box->info.old_plane_x = box->info.plane_x;
	box->info.plane_x = box->info.plane_x * cos(box->info.rot_speed
			* box->mouse.xdistance) - box->info.plane_y
		* sin(box->info.rot_speed * box->mouse.xdistance);
	box->info.plane_y = box->info.old_plane_x * sin(box->info.rot_speed
			* box->mouse.xdistance) + box->info.plane_y
		* cos(box->info.rot_speed * box->mouse.xdistance);
}

void	cry(t_box *box)
{
	if (box->player.cry)
	{
		if (((box->time.tv_sec - box->player.last_tear.tv_sec
					+ ((box->time.tv_usec - box->player.last_tear.tv_usec)
						/ 1000000.0))) > box->player.fire_rate / 100.0)
		{
			gettimeofday(&box->player.last_tear, NULL);
			sprite_append(box, box->info.pos_x, box->info.pos_y, TEAR);
			box->p = music(box->env, "sounds/shot.mp3");
		}
	}
	box->old_time = box->time;
	gettimeofday(&box->time, NULL);
	box->info.frame_time = (box->time.tv_sec - box->old_time.tv_sec)
		+ ((box->time.tv_usec - box->old_time.tv_usec) / 1000000.0);
	box->info.move_speed = box->info.frame_time * 3.0;
	box->info.move_speed *= box->player.speed / 100;
	box->info.ene_move_speed = box->info.frame_time * 3.0;
	box->info.rot_speed = box->info.frame_time * 1.5;
	if (box->info.sprint)
		box->info.move_speed *= 2;
	if (box->info.pos_z == -200)
		box->info.move_speed *= 0.5;
}

void	cal_move(t_box *box)
{
	if (MOUSE_CONTROL)
		box->mouse.xdistance = (box->mouse.x - (SCREENWIDTH / 2));
	else
		box->mouse.x = SCREENWIDTH / 2;
	if (box->mouse.xdistance < 0)
		box->mouse.xdistance *= -1;
	else if (box->mouse.xdistance == 0)
		box->mouse.xdistance = 1;
	if (box->mouse.xdistance > 1)
		box->mouse.xdistance = box->mouse.xdistance / 15;
	if (box->info.rotate == 1 || box->mouse.x > SCREENWIDTH / 2)
		rotate_right(box);
	else if (box->info.rotate == -1 || box->mouse.x < SCREENWIDTH / 2)
		rotate_left(box);
	if (box->info.move_x == 1)
		move_right(box);
	else if (box->info.move_x == -1)
		move_left(box);
	if (box->info.move_y == 1)
		move_forward(box);
	else if (box->info.move_y == -1)
		move_back(box);
	mouse_y(box);
	cry(box);
}
