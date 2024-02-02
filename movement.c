/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:23:13 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:12 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	action_door(t_box *box)
{
	t_sprite	*s;

	s = box->sprites;
	while (s)
	{
		if (s->data->texture == DOOR && s->data->dist < 2 && !s->data->opening && s->data->state == CLOSE && box->player.n_key > 0)
		{
			box->player.n_key--;
			s->data->opening = 1;
			sound_play(box, &box->sound.sfx[DOOR]);
			gettimeofday(&s->data->action_time, NULL);
		}
		s = s->next;
	}
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
		if ((box->map[(int)(box->info.pos_x + box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			|| (box->map[(int)(box->info.pos_x + box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x + box->info.dir_x * box->info.move_speed), (int)box->info.pos_y)->data->state == OPEN))
			box->info.pos_x += box->info.dir_x * box->info.move_speed;
		if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_y * box->info.move_speed)] == '0')
			|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_y * box->info.move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y + box->info.dir_y * box->info.move_speed))->data->state == OPEN))
			box->info.pos_y += box->info.dir_y * box->info.move_speed;
	}
	else if (box->info.move_x == -1)
	{
		if ((box->map[(int)(box->info.pos_x - box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			|| (box->map[(int)(box->info.pos_x - box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x - box->info.dir_x * box->info.move_speed), (int)box->info.pos_y)->data->state == OPEN))
			box->info.pos_x -= box->info.dir_x * box->info.move_speed;
		if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_y * box->info.move_speed)] == '0')
			|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_y * box->info.move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y - box->info.dir_y * box->info.move_speed))->data->state == OPEN))
			box->info.pos_y -= box->info.dir_y * box->info.move_speed;
	}
	if (box->info.move_y == 1)
	{
		if ((box->map[(int)(box->info.pos_x + box->info.dir_y * box->info.move_speed)][(int)box->info.pos_y] == '0')
			|| (box->map[(int)(box->info.pos_x + box->info.dir_y * box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x + box->info.dir_y * box->info.move_speed), (int)box->info.pos_y)->data->state == OPEN))
			box->info.pos_x += box->info.dir_y * box->info.move_speed;
		if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_x * box->info.move_speed)] == '0')
			|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_x * box->info.move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y - box->info.dir_x * box->info.move_speed))->data->state == OPEN))
			box->info.pos_y -= box->info.dir_x * box->info.move_speed;
	}
	else if (box->info.move_y == -1)
	{
		if ((box->map[(int)(box->info.pos_x - box->info.dir_y * box->info.move_speed)][(int)box->info.pos_y] == '0')
			|| (box->map[(int)(box->info.pos_x - box->info.dir_y * box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x - box->info.dir_y * box->info.move_speed), (int)box->info.pos_y)->data->state == OPEN))
			box->info.pos_x -= box->info.dir_y * box->info.move_speed;
		if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_x * box->info.move_speed)] == '0')
			|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_x * box->info.move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y + box->info.dir_x * box->info.move_speed))->data->state == OPEN))
			box->info.pos_y += box->info.dir_x * box->info.move_speed;
	}

	if (MOUSE_CONTROL)
		box->mouse.ydistance = (box->mouse.y - (SCREENHEIGHT / 2));
	else
		box->mouse.y = SCREENHEIGHT / 2;
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
			sound_play(box, &box->sound.sfx[SHOT]);
		}
	}

	box->old_time = box->time;
	gettimeofday(&box->time, NULL);
	box->info.frame_time = (box->time.tv_sec - box->old_time.tv_sec) +
						((box->time.tv_usec - box->old_time.tv_usec) / 1000000.0);
	box->info.move_speed = box->info.frame_time * 3.0;
	box->info.move_speed *= box->player.speed / 100;
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
		sound_play(box, &box->sound.sfx[SPLASH]);
		gettimeofday(&who->data->hit_time, NULL);
	}
	else
	{
		// printf("HIT SPRITE\n");
		who->data->hit = 1;
		gettimeofday(&who->data->hit_time, NULL);
		sound_play(box, &box->sound.sfx[SPLASH]);
		what->data->hit = 1;
		sound_play(box, &box->sound.sfx[SPLASH]);
		gettimeofday(&what->data->hit_time, NULL);
		what->data->hp -= box->player.dmg;
		sound_play(box, &box->sound.sfx[PAIN]);
		if (what->data->hp < 1)
		{
			sound_play(box, &box->sound.sfx[DIE]);
			if (what->data->texture > DOOR && what->data->texture <= ISAAC)
				sprite_append(box, what->data->x, what->data->y, KEY);
			sprite_remove(box, what);
		}
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
	// t_item		*items;

	// printf("\nDUMP:\n");
	// sprites = box->sprites;
	// while (sprites)
	// {
	// 	printf("Texture: %i | x: %f | y: %f | dir_x: %f | dir_y: %f | state: %i | frame: %i | hit: %i | seg: %i | n_seg %i\n", sprites->data->texture, sprites->data->x, sprites->data->y, sprites->data->dir_x, sprites->data->dir_y, sprites->data->state, sprites->data->frame, sprites->data->hit, sprites->data->seg, sprites->data->n_seg);
	// 	sprites = sprites->next;
	// }

	// printf("\nDUMP:\n");
	// items = box->items;
	// while (items)
	// {
	// 	printf("Texture: %i | id: %d\n", items->data->texture, items->data->id);
	// 	items = items->next;
	// }

	sprites = box->sprites;
	// printf("Dir_x %f | Dir_y %f\n", box->info.dir_x, box->info.dir_y);
	while (sprites)
	{
		if (sprites->data->texture == LARRY_JR_HEAD)
		{
			box->info.t_angle = atan2(sprites->data->y - box->info.pos_y, sprites->data->x - box->info.pos_x);
			box->info.now_angle = atan2(sprites->data->dir_y, sprites->data->dir_x) - atan2(box->info.start_dir_y, box->info.start_dir_x);
			if (box->info.t_angle < 0)
				box->info.t_angle += 2 * PI;
			if (box->info.now_angle < 0)
				box->info.now_angle += 2 * PI;
			// printf("NOW_ANGLE: %f NOW_DIR_X %f NOW_DIR_Y %f | T_ANGLE: %f T_DIR_X %f T_DIR_Y %f\n", box->info.now_angle * (180 / PI), sprites->data->dir_x, sprites->data->dir_y, box->info.t_angle * (180 / PI), box->info.dir_x, box->info.dir_y);
			if (box->info.now_angle < box->info.t_angle || fabs(box->info.now_angle * (180 / PI) - box->info.t_angle * (180 / PI)) > 180)
			{
				box->info.old_dir_x = sprites->data->dir_x;
				sprites->data->dir_x = sprites->data->dir_x * cos(box->info.rot_speed * 0.5) - sprites->data->dir_y * sin(box->info.rot_speed * 0.5);
				sprites->data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed * 0.5) + sprites->data->dir_y * cos(box->info.rot_speed * 0.5);
			}
			else
			{
				box->info.old_dir_x = sprites->data->dir_x;
				sprites->data->dir_x = sprites->data->dir_x * cos(-box->info.rot_speed * 0.5) - sprites->data->dir_y * sin(-box->info.rot_speed * 0.5);
				sprites->data->dir_y = box->info.old_dir_x * sin(-box->info.rot_speed * 0.5) + sprites->data->dir_y * cos(-box->info.rot_speed * 0.5);
			}
			if (((box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0')
				|| (box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0' + DOOR + 1
				&& find_door(box, (int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed), (int)sprites->data->y)->data->state == OPEN))
				&& ((box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0')
				|| (box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(sprites->data->x), (int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed))->data->state == OPEN)))
			{
				sprites->data->x += sprites->data->dir_x * 0.1 * box->info.ene_move_speed;
				sprites->data->y += sprites->data->dir_y * 0.1 * box->info.ene_move_speed;
			}
		}
		if (sprites->data->texture == LARRY_JR_BODY)
		{
			// printf("YOU %i,%i | FOLLOW %i,%i\n", sprites->data->seg, sprites->data->texture, find_seg(box, sprites->data->seg - 1)->data->seg, find_seg(box, sprites->data->seg - 1)->data->texture);
			box->info.t_angle = atan2(sprites->data->y - find_seg(box, sprites->data->seg - 1)->data->y, sprites->data->x - find_seg(box, sprites->data->seg - 1)->data->x);
			box->info.now_angle = atan2(sprites->data->dir_y, sprites->data->dir_x) - atan2(box->info.start_dir_y, box->info.start_dir_x);
			if (box->info.t_angle < 0)
				box->info.t_angle += 2 * PI;
			if (box->info.now_angle < 0)
				box->info.now_angle += 2 * PI;
			// printf("\nSEG %i NOW_ANGLE: %f NOW_DIR_X %f NOW_DIR_Y %f | T_ANGLE: %f\n", sprites->data->seg, box->info.now_angle * (180 / PI), sprites->data->dir_x, sprites->data->dir_y, box->info.t_angle * (180 / PI));
			if (box->info.now_angle < box->info.t_angle || fabs(box->info.now_angle * (180 / PI) - box->info.t_angle * (180 / PI)) > 180)
			{
				box->info.old_dir_x = sprites->data->dir_x;
				sprites->data->dir_x = sprites->data->dir_x * cos(box->info.rot_speed * 0.5) - sprites->data->dir_y * sin(box->info.rot_speed * 0.5);
				sprites->data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed * 0.5) + sprites->data->dir_y * cos(box->info.rot_speed * 0.5);
			}
			else
			{
				box->info.old_dir_x = sprites->data->dir_x;
				sprites->data->dir_x = sprites->data->dir_x * cos(-box->info.rot_speed * 0.5) - sprites->data->dir_y * sin(-box->info.rot_speed * 0.5);
				sprites->data->dir_y = box->info.old_dir_x * sin(-box->info.rot_speed * 0.5) + sprites->data->dir_y * cos(-box->info.rot_speed * 0.5);
			}
			if (((box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0')
				|| (box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0' + DOOR + 1
				&& find_door(box, (int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed), (int)sprites->data->y)->data->state == OPEN))
				&& ((box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0')
				|| (box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(sprites->data->x), (int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed))->data->state == OPEN)))
			{
				sprites->data->x += sprites->data->dir_x * 0.1 * box->info.ene_move_speed;
				sprites->data->y += sprites->data->dir_y * 0.1 * box->info.ene_move_speed;
			}
		}
		if (sprites->data->texture < TEAR && sprites->data->texture != DOOR)
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
				if (box->god == 0 && !box->won && !box->lost)
				{
					box->player.hp -= 1;
					if (box->player.hp < 1)
					{
						box->lost = 1;
						printf("YOU ARE DEAD!!!\n");
						sound_play(box, &box->sound.sfx[FAIL]);
						gettimeofday(&box->fin_time, NULL);
						break;
					}
					sound_play(box, &box->sound.sfx[OW]);
				}
				gettimeofday(&box->player.hit_time, NULL);
			}
		}

		if (sprites->data->texture == LEECH || (sprites->data->texture == BABY && sprites->data->state == AWAKE))
		{
			box->info.t_angle = atan2(sprites->data->y - box->info.pos_y, sprites->data->x - box->info.pos_x);
			box->info.now_angle = atan2(sprites->data->dir_y, sprites->data->dir_x) - atan2(box->info.start_dir_y, box->info.start_dir_x);
			if (box->info.t_angle < 0)
				box->info.t_angle += 2 * PI;
			if (box->info.now_angle < 0)
				box->info.now_angle += 2 * PI;
			// printf("NOW_ANGLE: %f NOW_DIR_X %f NOW_DIR_Y %f | T_ANGLE: %f T_DIR_X %f T_DIR_Y %f\n", box->info.now_angle * (180 / PI), sprites->data->dir_x, sprites->data->dir_y, box->info.t_angle * (180 / PI), box->info.dir_x, box->info.dir_y);
			if (box->info.now_angle < box->info.t_angle || fabs(box->info.now_angle * (180 / PI) - box->info.t_angle * (180 / PI)) > 180)
			{
				box->info.old_dir_x = sprites->data->dir_x;
				sprites->data->dir_x = sprites->data->dir_x * cos(box->info.rot_speed * 0.5) - sprites->data->dir_y * sin(box->info.rot_speed * 0.5);
				sprites->data->dir_y = box->info.old_dir_x * sin(box->info.rot_speed * 0.5) + sprites->data->dir_y * cos(box->info.rot_speed * 0.5);
			}
			else
			{
				box->info.old_dir_x = sprites->data->dir_x;
				sprites->data->dir_x = sprites->data->dir_x * cos(-box->info.rot_speed * 0.5) - sprites->data->dir_y * sin(-box->info.rot_speed * 0.5);
				sprites->data->dir_y = box->info.old_dir_x * sin(-box->info.rot_speed * 0.5) + sprites->data->dir_y * cos(-box->info.rot_speed * 0.5);
			}
			if (((box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0')
				|| (box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed)][(int)sprites->data->y] == '0' + DOOR + 1
				&& find_door(box, (int)(sprites->data->x + sprites->data->dir_x * box->info.ene_move_speed), (int)sprites->data->y)->data->state == OPEN))
				&& ((box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0')
				|| (box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed)] == '0' + DOOR + 1
				&& find_door(box, (int)(sprites->data->x), (int)(sprites->data->y + sprites->data->dir_y * box->info.ene_move_speed))->data->state == OPEN)))
			{
				sprites->data->x += sprites->data->dir_x * 0.1 * box->info.ene_move_speed;
				sprites->data->y += sprites->data->dir_y * 0.1 * box->info.ene_move_speed;
			}
		}

		if (sprites->data->texture == TEAR)
		{
			// printf("%c | %i | %i\n", box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.move_speed)], (int)sprites->data->x, (int)(sprites->data->y + sprites->data->dir_y * box->info.move_speed));
			if (sprites->data->hit)
			{
				sprites->data->frame = ((((box->time.tv_sec - sprites->data->hit_time.tv_sec) + ((box->time.tv_usec - sprites->data->hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
				//printf("FRAME: %i | HIT TIME: %li\n", sprites->data->frame, sprites->data->hit_time.tv_sec);
				if (sprites->data->frame > 14)
				{
					sprite_remove(box, sprites);
					break;
				}
			}
			else if ((box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.move_speed)][(int)sprites->data->y] > '0'
					&& box->map[(int)(sprites->data->x + sprites->data->dir_x * box->info.move_speed)][(int)sprites->data->y] != '0' + DOOR + 1)
					|| (box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.move_speed)] > '0'
					&& box->map[(int)(sprites->data->x)][(int)(sprites->data->y + sprites->data->dir_y * box->info.move_speed)] != '0' + DOOR + 1))
			{
				sprite_hit(box, sprites, NULL);
				break;
			}
			else if ((find_door(box, (int)sprites->data->x, (int)sprites->data->y + sprites->data->dir_y * box->info.move_speed)
					&& find_door(box, (int)sprites->data->x, (int)sprites->data->y + sprites->data->dir_y * box->info.move_speed)->data->state != OPEN)
					|| (find_door(box, (int)(sprites->data->x + sprites->data->dir_x * box->info.move_speed), (int)sprites->data->y)
					&& find_door(box, (int)(sprites->data->x + sprites->data->dir_x * box->info.move_speed), (int)sprites->data->y)->data->state != OPEN))
			{
				sprite_hit(box, sprites, NULL);
				break;
			}
			else if (sprites->data->travel > box->player.range / 5.0)
			{
				sprite_hit(box, sprites, NULL);
				break;
			}
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
							* (obj->data->y - sprites->data->y)) * 100 && obj->data->texture < TEAR
							&& obj->data->hit == 0)
						{
							sprite_hit(box, sprites, obj);
							break;
						}
					obj = obj->next;
				}
				sprites->data->x += sprites->data->dir_x * box->info.move_speed * (box->player.shot_speed / 8.0);
				sprites->data->y += sprites->data->dir_y * box->info.move_speed * (box->player.shot_speed / 8.0);
			}

		}
		if (sprites->data->texture == ITEMS)
		{
			sprites->data->frame = ((((box->time.tv_sec - sprites->data->hit_time.tv_sec) + ((box->time.tv_usec - sprites->data->hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
			if (sprites->data->dist < 0.1)
			{
				if (sprites->data->id == 0)
					box->player.fire_rate -= box->player.fire_rate / 10;
				else if (sprites->data->id == 3)
				{
					box->player.dmg += 5;
					if (!find_item(box, 11) && !find_item(box, 3))
						box->player.dmg *= 1.5;
				}
				else if (sprites->data->id == 5)
				{
					box->player.fire_rate /= 2;
					box->player.range /= 1.5;
				}
				else if (sprites->data->id == 6)
					box->player.dmg += 10;
				else if (sprites->data->id == 11)
				{
					box->player.max_hp += 2;
					box->player.hp = box->player.max_hp;
					box->player.dmg += 3;
					if (!find_item(box, 3) && !find_item(box, 11))
						box->player.dmg *= 1.5;
					box->player.range += 15;
					box->player.speed += 30;
				}
				item_append(box, sprites);
				break;
			}
		}
		if (sprites->data->texture == KEY && sprites->data->dist < 0.1 && sprites->data->dist != 0)
		{
			box->player.n_key++;
			sound_play(box, &box->sound.sfx[KEY_PICKUP]);
			sprite_remove(box, sprites);
			break;
		}
		if (sprites->data->texture == TROPHY && sprites->data->dist < 0.1 && sprites->data->dist != 0)
		{
			printf("YOU WIN!!!\n");
			sound_play(box, &box->sound.sfx[FANFARE]);
			sprite_remove(box, sprites);
			box->won = 1;
			gettimeofday(&box->fin_time, NULL);
			break;
		}
		if (sprites->data->texture == DOOR)
		{
			if (sprites->data->opening)
			{
				sprites->data->frame = ((((box->time.tv_sec - sprites->data->action_time.tv_sec) + ((box->time.tv_usec - sprites->data->action_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
				if (sprites->data->frame > 32)
				{
					sprites->data->opening = 0;
					if (sprites->data->state == CLOSE)
						sprites->data->state = OPEN;
				}
			}
		}
		sprites = sprites->next;
	}
}
