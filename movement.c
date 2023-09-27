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

	box->old_time = box->time;
	gettimeofday(&box->time, NULL);
	box->info.frame_time = (box->time.tv_sec - box->old_time.tv_sec) +
						((box->time.tv_usec - box->old_time.tv_usec) / 1000000.0);
	box->info.move_speed = box->info.frame_time * 3.0;
	box->info.rot_speed = box->info.frame_time * 1.5;
	if (box->info.sprint)
		box->info.move_speed *= 2;
	if (box->info.pos_z == -200)
		box->info.move_speed *= 0.5;
}

void	sprite_hit(t_sprite *sprite)
{
	sprite->state = HIT;
	gettimeofday(&sprite->hit_time, NULL);
	// printf("\e[0;31mDestroing tear of index %i\e[0m\n", index);
	// if (10 < (box->time.tv_sec - box->old_time.tv_sec) +
	// 		((box->time.tv_usec - box->old_time.tv_usec) / 1000000.0))
	// sprite_remove(box, index);
	// printf("\e[0;32mNumber of sprites after destroing %i\e[0m\n", box->n_sprites);
}

void	cal_sprite_move(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	// if (sprites)
	// {
	// 	return ;
	// }
	printf("\nDUMP:\n");
	while (sprites)
	{
		printf("Texture: %i | x: %f | y: %f | dir_x: %f | dir_y: %f\n", sprites->texture, sprites->x, sprites->y, sprites->dir_x, sprites->dir_y);
		sprites = sprites->next;
	}
	sprites = box->sprites;
	while (sprites)
	{
		/*
		if (box->sprites[i].texture == 10)
		{
			if (box->sprites[i].x < box->info.pos_x)
				box->sprites[i].x += speed;
			if (box->sprites[i].x > box->info.pos_x)
				box->sprites[i].x -= speed;
			if (box->sprites[i].y < box->info.pos_y)
				box->sprites[i].y += speed;
			if (box->sprites[i].y > box->info.pos_y)
				box->sprites[i].y -= speed;
		}
*/
	/*
		if (box->sprites[i].texture == 12)
		{
			if (box-box->sprites[i].index>map[(int)(box->sprites[i].x + speed)][(int)(box->sprites[i].y)] == '0')
				box->sprites[i].x += speed;
			else if (box->map[(int)(box->sprites[i].x)][(int)(box->sprites[i].y + speed)] == '0')
				box->sprites[i].y += speed;
			else if (box->map[(int)(box->sprites[i].x - speed)][(int)(box->sprites[i].y)] == '0')
				box->sprites[i].x -= speed;
			else if (box->map[(int)(box->sprites[i].x)][(int)(box->sprites[i].y - speed)] == '0')
				box->sprites[i].y -= speed;
		}
	*/
		if (sprites->texture == 30)
		{
			if (sprites->state == HIT)
			{
				sprites->frame = ((((box->time.tv_sec - sprites->hit_time.tv_sec) + ((box->time.tv_usec - sprites->hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
				printf("FRAME: %i\n", sprites->frame);
				if (sprites->frame > 14)
				{
					sprite_remove(sprites);
					printf("\e[0;32mNumber of sprites after destroing %i\e[0m\n", box->n_sprites);
				}
			}
			else if (box->map[(int)(sprites->x + sprites->dir_x * box->info.move_speed)][(int)sprites->y] == '1'
					|| box->map[(int)(sprites->x)][(int)(sprites->y + sprites->dir_y * box->info.move_speed)] == '1')
				sprite_hit(sprites);
			else
			{
				sprites->x += sprites->dir_x * box->info.move_speed;
				sprites->y += sprites->dir_y * box->info.move_speed;
			}
		}
		sprites = sprites->next;
	}
}
