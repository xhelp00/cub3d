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
