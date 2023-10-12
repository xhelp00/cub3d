/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:23:13 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/25 18:01:34 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_move(t_box *box)
{
	box->mouse.xdistance = (box->mouse.x - (SCREENWIDTH / 2));
	if (box->mouse.xdistance < 0)
		box->mouse.xdistance *= -1;
	else if (box->mouse.xdistance == 0)
		box->mouse.xdistance = 1;
	if (box->mouse.xdistance > 1)
		box->mouse.xdistance = box->mouse.xdistance / 15;
	if (box->info.rotate == 1 || box->mouse.x > SCREENWIDTH / 2)
	{
		box->info.old_dir_x = box->info.dir_x;
		box->info.dir_x = box->info.dir_x * cos(-box->info.rot_speed * box->mouse.xdistance) - box->info.dir_y * sin(-box->info.rot_speed * box->mouse.xdistance);
		box->info.dir_y = box->info.old_dir_x * sin(-box->info.rot_speed * box->mouse.xdistance) + box->info.dir_y * cos(-box->info.rot_speed * box->mouse.xdistance);
		box->info.old_plane_x = box->info.plane_x;
		box->info.plane_x = box->info.plane_x * cos(-box->info.rot_speed * box->mouse.xdistance) - box->info.plane_y * sin(-box->info.rot_speed * box->mouse.xdistance);
		box->info.plane_y = box->info.old_plane_x * sin(-box->info.rot_speed * box->mouse.xdistance) + box->info.plane_y * cos(-box->info.rot_speed * box->mouse.xdistance);
	}
	else if (box->info.rotate == -1 || box->mouse.x < SCREENWIDTH / 2)
	{
		box->info.old_dir_x = box->info.dir_x;
		box->info.dir_x = box->info.dir_x * cos(box->info.rot_speed * box->mouse.xdistance) - box->info.dir_y * sin(box->info.rot_speed * box->mouse.xdistance);
		box->info.dir_y = box->info.old_dir_x * sin(box->info.rot_speed * box->mouse.xdistance) + box->info.dir_y * cos(box->info.rot_speed * box->mouse.xdistance);
		box->info.old_plane_x = box->info.plane_x;
		box->info.plane_x = box->info.plane_x * cos(box->info.rot_speed * box->mouse.xdistance) - box->info.plane_y * sin(box->info.rot_speed * box->mouse.xdistance);
		box->info.plane_y = box->info.old_plane_x * sin(box->info.rot_speed * box->mouse.xdistance) + box->info.plane_y * cos(box->info.rot_speed * box->mouse.xdistance);
	}
	if (box->info.move_x == 1)
	{
		if (box->map[(int)(box->info.pos_x + box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			box->info.pos_x += box->info.dir_x * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_y * box->info.move_speed)] == '0')
			box->info.pos_y += box->info.dir_y * box->info.move_speed;
	}
	else if (box->info.move_x == -1)
	{
		if (box->map[(int)(box->info.pos_x - box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			box->info.pos_x -= box->info.dir_x * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_y * box->info.move_speed)] == '0')
			box->info.pos_y -= box->info.dir_y * box->info.move_speed;
	}
	if (box->info.move_y == 1)
	{
		if (box->map[(int)(box->info.pos_x + box->info.dir_y * box->info.move_speed)][(int)(box->info.pos_y)] == '0')
			box->info.pos_x += box->info.dir_y * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_x * box->info.move_speed)] == '0')
			box->info.pos_y -= box->info.dir_x * box->info.move_speed;
	}
	else if (box->info.move_y == -1)
	{
		if (box->map[(int)(box->info.pos_x - box->info.dir_y * box->info.move_speed)][(int)(box->info.pos_y)] == '0')
			box->info.pos_x -= box->info.dir_y * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_x * box->info.move_speed)] == '0')
			box->info.pos_y += box->info.dir_x * box->info.move_speed;
	}

	box->mouse.ydistance = (box->mouse.y - (SCREENHEIGHT / 2));
	if (box->mouse.ydistance < 0)
		box->mouse.ydistance *= -1;
	if (box->info.up_down == 1 || box->mouse.y < SCREENHEIGHT / 2)
	{
		box->info.pitch += 25 * box->info.rot_speed * box->mouse.ydistance;
		if (box->info.pitch > 400)
			box->info.pitch = 400;
	}
	else if (box->info.up_down == -1 || box->mouse.y > SCREENHEIGHT / 2)
	{
		box->info.pitch -= 25 * box->info.rot_speed * box->mouse.ydistance;
		if (box->info.pitch < -400)
			box->info.pitch = -400;
	}
	if (box->info.pos_z > 0)
		box->info.pos_z -= 100 * box->info.move_speed;
	if (box->player.cry)
	{
		// printf("TIME SINCE LAST SHOT %f > %f\n", (box->time.tv_sec - box->player.last_tear.tv_sec + ((box->time.tv_usec - box->player.last_tear.tv_usec) / 1000000.0)), box->player.fire_rate / 100.0);
		if (((box->time.tv_sec - box->player.last_tear.tv_sec + ((box->time.tv_usec - box->player.last_tear.tv_usec) / 1000000.0))) > box->player.fire_rate / 100.0)
		{
			gettimeofday(&box->player.last_tear, NULL);
			sprite_append(box, box->info.pos_x, box->info.pos_y, TEAR);
		}
	}

	box->old_time = box->time;
	gettimeofday(&box->time, NULL);
	box->info.frame_time = (box->time.tv_sec - box->old_time.tv_sec) +
						((box->time.tv_usec - box->old_time.tv_usec) / 1000000.0);
	box->info.move_speed = box->info.frame_time * 3.0;
	box->info.ene_move_speed = box->info.frame_time * 3.0;
	box->info.rot_speed = box->info.frame_time * 1.5;
	if (box->info.sprint)
		box->info.move_speed *= 2;
	if (box->info.pos_z == -200)
		box->info.move_speed *= 0.5;
}

void	sprite_hit(t_box *box, t_sprite *who, t_sprite *what)
{
	if (what == NULL)
	{
		who->data->hit = 1;
		gettimeofday(&who->data->hit_time, NULL);
	}
	else
	{
		// printf("HIT SPRITE\n");
		who->data->hit = 1;
		gettimeofday(&who->data->hit_time, NULL);
		what->data->hit = 1;
		gettimeofday(&what->data->hit_time, NULL);
		what->data->hp -= box->player.dmg;
		if (what->data->hp < 1)
			sprite_remove(box, what);
	}
	// printf("\e[0;31mDestroing tear of index %i\e[0m\n", index);
	// if (10 < (box->time.tv_sec - box->old_time.tv_sec) +
	// 		((box->time.tv_usec - box->old_time.tv_usec) / 1000000.0))
	// sprite_remove(box, index);
	// printf("\e[0;32mNumber of sprites after destroing %i\e[0m\n", box->n_sprites);
}

void	cal_sprite_move(t_box *box)
{
	t_sprite	*sprites;
	t_sprite	*obj;

	// printf("\nDUMP:\n");
	// sprites = box->sprites;
	// while (sprites)
	// {
	// 	printf("Texture: %i | x: %f | y: %f | dir_x: %f | dir_y: %f | state: %i | hit: %i\n", sprites->data->texture, sprites->data->x, sprites->data->y, sprites->data->dir_x, sprites->data->dir_y, sprites->data->state, sprites->data->hit);
	// 	sprites = sprites->next;
	// }
	sprites = box->sprites;
	// printf("Dir_x %f | Dir_y %f\n", box->info.dir_x, box->info.dir_y);
	while (sprites)
	{
		if (sprites->data->texture == BABY && sprites->data->state == AWAKE)
		{
			if (sprites->data->x < box->info.pos_x)
				sprites->data->x += 0.1 * box->info.ene_move_speed;
			if (sprites->data->x > box->info.pos_x)
				sprites->data->x -= 0.1 * box->info.ene_move_speed;
			if (sprites->data->y < box->info.pos_y)
				sprites->data->y += 0.1 * box->info.ene_move_speed;
			if (sprites->data->y > box->info.pos_y)
				sprites->data->y -= 0.1 * box->info.ene_move_speed;

			// if (box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0'
			// 		&& box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0')
			// {
			// 	sprites->data->x += sprites->data->dir_x * 0.1 * box->info.ene_move_speed;
			// 	sprites->data->y += sprites->data->dir_y * 0.1 * box->info.ene_move_speed;
			// }
			// else
			// {
			// 	box->info.old_dir_x = sprites->data->dir_x;
			// 	sprites->data->dir_x = sprites->data->dir_x * cos(box->info.rot_speed) - sprites->data->dir_y * sin(box->info.rot_speed);
			// 	sprites->data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed) + sprites->data->dir_y * cos(box->info.rot_speed);
			// }
		}
		if (sprites->data->texture < TEAR)
		{
			if (box->player.hit)
			{
				box->player.frame = ((((box->time.tv_sec - box->player.hit_time.tv_sec) + ((box->time.tv_usec - box->player.hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
				if (box->player.frame > 20)
					box->player.hit = 0;
			}
			else if (sprites->data->dist < 0.1)
			{
				box->player.hit = 1;
				box->player.hp -= 1;
				gettimeofday(&box->player.hit_time, NULL);
			}
		}

		if (sprites->data->texture == LEECH)
		{
			box->info.old_dir_x = sprites->data->dir_x;
			sprites->data->dir_x = sprites->data->dir_x * cos(box->info.rot_speed) - sprites->data->dir_y * sin(box->info.rot_speed);
			sprites->data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed) + sprites->data->dir_y * cos(box->info.rot_speed);

			sprites->data->x += sprites->data->dir_x * 0.1 * box->info.ene_move_speed;
			sprites->data->y += sprites->data->dir_y * 0.1 * box->info.ene_move_speed;
		}

		if (sprites->data->texture == TEAR)
		{
			if (sprites->data->hit)
			{
				sprites->data->frame = ((((box->time.tv_sec - sprites->data->hit_time.tv_sec) + ((box->time.tv_usec - sprites->data->hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
				// printf("FRAME: %i | HIT TIME: %li\n", sprites->data->frame, sprites->data->hit_time.tv_sec);
				if (sprites->data->frame > 14)
					sprite_remove(box, sprites);
			}
			else if (box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.move_speed)][(int)sprites->data->y] == '1'
					|| box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.move_speed)] == '1')
				sprite_hit(box, sprites, NULL);
			else if (sprites->data->travel > box->player.range / 5.0)
				sprite_hit(box, sprites, NULL);
			else
			{
				obj = box->sprites;
				while (obj)
				{
					// printf("DIST FROM %f\n", ((obj->data->x - sprites->data->x)
					// 		* (obj->data->x - sprites->data->x)
					// 		+ (obj->data->y - sprites->data->y)
					// 		* (obj->data->y - sprites->data->y)));
					if (1 > ((obj->data->x - sprites->data->x)
							* (obj->data->x - sprites->data->x)
							+ (obj->data->y - sprites->data->y)
							* (obj->data->y - sprites->data->y)) * 100 && obj->data->texture != TEAR
							&& obj->data->hit == 0)
						sprite_hit(box, sprites, obj);
					obj = obj->next;
				}
				sprites->data->x += sprites->data->dir_x * box->info.move_speed * (box->player.shot_speed / 8.0);
				sprites->data->y += sprites->data->dir_y * box->info.move_speed * (box->player.shot_speed / 8.0);
			}

		}
		sprites = sprites->next;
	}
}
