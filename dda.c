/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Initializing the rays and prepping for raycasting.
void	init_rays(t_box *box, int x)
{
	reset_vals(box);
	box->info.camera_x = 2 * x / (double)SCREENWIDTH - 1;
	box->info.ray_dir_x = box->info.dir_x + box->info.plane_x
		* box->info.camera_x;
	box->info.ray_dir_y = box->info.dir_y + box->info.plane_y
		* box->info.camera_x;
	box->info.map_x = (int)box->info.pos_x;
	box->info.map_y = (int)box->info.pos_y;
	box->info.delta_dist_x = fabs(1 / box->info.ray_dir_x);
	box->info.delta_dist_y = fabs(1 / box->info.ray_dir_y);
}

void	init_side_distances(t_box *box)
{
	if (box->info.ray_dir_x < 0)
	{
		box->info.step_x = -1;
		box->info.side_dist_x = (box->info.pos_x - box->info.map_x)
			* box->info.delta_dist_x;
	}
	else
	{
		box->info.step_x = 1;
		box->info.side_dist_x = (box->info.map_x + 1.0 - box->info.pos_x)
			* box->info.delta_dist_x;
	}
	if (box->info.ray_dir_y < 0)
	{
		box->info.step_y = -1;
		box->info.side_dist_y = (box->info.pos_y - box->info.map_y)
			* box->info.delta_dist_y;
	}
	else
	{
		box->info.step_y = 1;
		box->info.side_dist_y = (box->info.map_y + 1.0 - box->info.pos_y)
			* box->info.delta_dist_y;
	}
}

void	handle_wall_and_door_collisions(t_box *box)
{
	if (box->map[box->info.map_x][box->info.map_y] > '0' && box->map[box->info
		.map_x][box->info.map_y] != DOOR + 1 + '0')
	{
		box->info.hit = 1;
	}
	else if (box->map[box->info.map_x][box->info.map_y] == DOOR + 1 + '0'
		&& !box->info.door && !(find_door(box, box->info.map_x,
			box->info.map_y)->data->state == OPEN && !find_door(box, box->info
			.map_x, box->info.map_y)->data->opening))
	{
		box->info.door_side = box->info.side;
		box->info.door = 1;
		box->info.door_x = box->info.map_x;
		box->info.door_y = box->info.map_y;
		box->info.door_dist_x = box->info.side_dist_x;
		box->info.door_dist_y = box->info.side_dist_y;
	}
}

void	do_dda(t_box *box)
{
	while (!box->info.hit)
	{
		if (box->info.side_dist_x < box->info.side_dist_y)
		{
			box->info.side_dist_x += box->info.delta_dist_x;
			box->info.map_x += box->info.step_x;
			box->info.side = 0;
		}
		else
		{
			box->info.side_dist_y += box->info.delta_dist_y;
			box->info.map_y += box->info.step_y;
			box->info.side = 1;
		}
		handle_wall_and_door_collisions(box);
	}
}

void	perform_dda(t_box *box)
{
	init_side_distances(box);
	do_dda(box);
}
