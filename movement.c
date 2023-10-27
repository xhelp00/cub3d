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

void	move_right(t_box *box)
{
	if ((box->map[(int)(box->info.pos_x + box->info.dir_x
				* box->info.move_speed)][(int)box->info.pos_y] == '0')
		|| (box->map[(int)(box->info.pos_x + box->info.dir_x
		* box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x + box->info.dir_x
		* box->info.move_speed), (int)box->info.pos_y)->data->state
			== OPEN))
		box->info.pos_x += box->info.dir_x * box->info.move_speed;
	if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		+ box->info.dir_y * box->info.move_speed)] == '0')
		|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		+ box->info.dir_y * box->info.move_speed)] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y
		+ box->info.dir_y * box->info.move_speed))->data->state == OPEN))
		box->info.pos_y += box->info.dir_y * box->info.move_speed;
}

void	move_left(t_box *box)
{
	if ((box->map[(int)(box->info.pos_x - box->info.dir_x
				* box->info.move_speed)][(int)box->info.pos_y] == '0')
		|| (box->map[(int)(box->info.pos_x - box->info.dir_x
		* box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x - box->info.dir_x
		* box->info.move_speed), (int)box->info.pos_y)->data->state
			== OPEN))
		box->info.pos_x -= box->info.dir_x * box->info.move_speed;
	if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		- box->info.dir_y * box->info.move_speed)] == '0')
		|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		- box->info.dir_y * box->info.move_speed)] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y
		- box->info.dir_y * box->info.move_speed))->data->state == OPEN))
		box->info.pos_y -= box->info.dir_y * box->info.move_speed;
}

void	move_forward(t_box *box)
{
	if ((box->map[(int)(box->info.pos_x + box->info.dir_y
				* box->info.move_speed)][(int)box->info.pos_y] == '0')
		|| (box->map[(int)(box->info.pos_x + box->info.dir_y
		* box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x + box->info.dir_y
		* box->info.move_speed), (int)box->info.pos_y)->data->state
			== OPEN))
		box->info.pos_x += box->info.dir_y * box->info.move_speed;
	if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		- box->info.dir_x * box->info.move_speed)] == '0')
		|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		- box->info.dir_x * box->info.move_speed)] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y
		- box->info.dir_x * box->info.move_speed))->data->state == OPEN))
		box->info.pos_y -= box->info.dir_x * box->info.move_speed;
}

void	move_back(t_box *box)
{
	if ((box->map[(int)(box->info.pos_x - box->info.dir_y
				* box->info.move_speed)][(int)box->info.pos_y] == '0')
		|| (box->map[(int)(box->info.pos_x - box->info.dir_y
		* box->info.move_speed)][(int)box->info.pos_y] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x - box->info.dir_y
		* box->info.move_speed), (int)box->info.pos_y)->data->state
			== OPEN))
		box->info.pos_x -= box->info.dir_y * box->info.move_speed;
	if ((box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		+ box->info.dir_x * box->info.move_speed)] == '0')
		|| (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y
		+ box->info.dir_x * box->info.move_speed)] == '0' + DOOR + 1
			&& find_door(box, (int)(box->info.pos_x), (int)(box->info.pos_y
		+ box->info.dir_x * box->info.move_speed))->data->state == OPEN))
		box->info.pos_y += box->info.dir_x * box->info.move_speed;
}

void	mouse_y(t_box *box)
{
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

int	update_player_frame_when_hit(t_box *box)
{
	box->player.frame = ((((box->time.tv_sec - box->player.hit_time.tv_sec)
					+ ((box->time.tv_usec - box->player.hit_time.tv_usec)
						/ 1000000.0)) * 10) * 16) / 10;
	if (box->player.frame > 20)
	{
		box->player.hit = 0;
		return (1);
	}
	return (0);
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

int	check_player_hit(t_box *box, t_sprite_data *data)
{
	if (box->player.hit)
		return (update_player_frame_when_hit(box));
	else if (data->dist < 0.1)
		return (handle_player_getting_hit(box));
	return (1);
}

int	handle_tear(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	t_sprite	*obj;

	if (data->hit)
	{
		data->frame = ((((box->time.tv_sec - data->hit_time.tv_sec) + ((box->time.tv_usec - data->hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		if (data->frame > 14)
		{
			sprite_remove(box, sprites);
			return (0);
		}
	}
	else if ((box->map[(int)(data->x + data->dir_x * box->info.move_speed)][(int)data->y] > '0'
			&& box->map[(int)(data->x + data->dir_x * box->info.move_speed)][(int)data->y] != '0' + DOOR + 1)
			|| (box->map[(int)(data->x)][(int)(data->y + data->dir_y * box->info.move_speed)] > '0'
			&& box->map[(int)(data->x)][(int)(data->y + data->dir_y * box->info.move_speed)] != '0' + DOOR + 1))
	{
		sprite_hit(box, sprites, NULL);
		return (0);
	}
	else if ((find_door(box, (int)data->x, (int)data->y + data->dir_y * box->info.move_speed)
			&& find_door(box, (int)data->x, (int)data->y + data->dir_y * box->info.move_speed)->data->state != OPEN)
			|| (find_door(box, (int)(data->x + data->dir_x * box->info.move_speed), (int)data->y)
			&& find_door(box, (int)(data->x + data->dir_x * box->info.move_speed), (int)data->y)->data->state != OPEN))
	{
		sprite_hit(box, sprites, NULL);
		return (0);
	}
	else if (data->travel > box->player.range / 5.0)
	{
		sprite_hit(box, sprites, NULL);
		return (0);
	}
	else
	{
		obj = box->sprites;
		while (obj)
		{
			if (1 > ((obj->data->x - data->x)
					* (obj->data->x - data->x)
					+ (obj->data->y - data->y)
					* (obj->data->y - data->y)) * 100 && obj->data->texture < TEAR
					&& obj->data->hit == 0)
				{
					sprite_hit(box, sprites, obj);
					return (0);
				}
			obj = obj->next;
		}
		data->x += data->dir_x * box->info.move_speed * (box->player.shot_speed / 8.0);
		data->y += data->dir_y * box->info.move_speed * (box->player.shot_speed / 8.0);
	}
	return (1);
}

int	handle_item(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	data->frame = ((((box->time.tv_sec - data->hit_time.tv_sec) + ((box->time
		.tv_usec - data->hit_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
	if (data->dist < 0.1)
	{
		if (data->id == 0)
			box->player.fire_rate -= box->player.fire_rate / 10;
		else if (data->id == 3)
		{
			box->player.dmg += 5;
			if (!find_item(box, 11) && !find_item(box, 3))
				box->player.dmg *= 1.5;
		}
		else if (data->id == 5)
		{
			box->player.fire_rate /= 2;
			box->player.range /= 1.5;
		}
		else if (data->id == 6)
			box->player.dmg += 10;
		else if (data->id == 11)
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
		data->frame = ((((box->time.tv_sec - data->action_time.tv_sec) + ((box
			->time.tv_usec - data->action_time.tv_usec) / 1000000.0)) * 10)
				* 16) / 10;
		if (data->frame > 32)
		{
			data->opening = 0;
			if (data->state == CLOSE)
				data->state = OPEN;
		}
	}
	return (1);
}

void	cal_sprite_move(t_box *box)
{
	t_sprite	*sprites;
	int			continue_loop;

	continue_loop = 1;
	sprites = box->sprites;
	while (sprites && continue_loop)
	{
		if (sprites->data->texture == LARRY_JR_HEAD)
		{
			enemy_angle(box, sprites->data);
			enemy_move(box, sprites->data);
		}
		if (sprites->data->texture == LARRY_JR_BODY)
		{
			body_angle(box, sprites->data);
			enemy_move(box, sprites->data);
		}
		if (sprites->data->texture == LEECH || (sprites->data->texture == BABY
			&& sprites->data->state == AWAKE))
		{
			enemy_angle(box, sprites->data);
			enemy_move(box, sprites->data);
		}
		if (sprites->data->texture < TEAR && sprites->data->texture != DOOR)
			continue_loop = check_player_hit(box, sprites->data);
		else if (sprites->data->texture == TEAR)
			continue_loop = handle_tear(box, sprites->data, sprites);
		else if (sprites->data->texture == ITEMS)
			continue_loop = handle_item(box, sprites->data, sprites);
		else if (sprites->data->texture == KEY && sprites->data->dist < 0.1
			&& sprites->data->dist != 0)
			continue_loop = handle_key(box, sprites);
		else if (sprites->data->texture == TROPHY && sprites->data->dist < 0.1
			&& sprites->data->dist != 0)
			continue_loop = handle_trophy(box, sprites);
		else if (sprites->data->texture == DOOR)
			continue_loop = handle_door(box, sprites->data);
		if (continue_loop)
			sprites = sprites->next;
	}
}
