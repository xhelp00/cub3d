/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_floor_and_ceiling(t_box *box, int y)
{
	reset_vals(box);
	if (y > SCREENHEIGHT / 2 + box->info.pitch)
		box->info.is_floor = 1;
	else
		box->info.is_floor = 0;
}

void	calculate_ray_directions(t_box *box)
{
	box->info.ray_dir_x0 = box->info.dir_x - box->info.plane_x;
	box->info.ray_dir_y0 = box->info.dir_y - box->info.plane_y;
	box->info.ray_dir_x1 = box->info.dir_x + box->info.plane_x;
	box->info.ray_dir_y1 = box->info.dir_y + box->info.plane_y;
}

void	compute_perspective_values(t_box *box, int y)
{
	if (box->info.is_floor)
		box->info.p = y - SCREENHEIGHT / 2 - box->info.pitch;
	else
		box->info.p = SCREENHEIGHT / 2 - y + box->info.pitch;
	if (box->info.is_floor)
		box->info.cam_z = 0.5 * SCREENHEIGHT + box->info.pos_z;
	else
		box->info.cam_z = 0.5 * SCREENHEIGHT - box->info.pos_z;
}

void	compute_row_and_step_values(t_box *box)
{
	box->info.row_distance = box->info.cam_z / box->info.p;
	box->info.floor_step_x = box->info.row_distance * (box->info.ray_dir_x1
			- box->info.ray_dir_x0) / SCREENWIDTH;
	box->info.floor_step_y = box->info.row_distance * (box->info.ray_dir_y1
			- box->info.ray_dir_y0) / SCREENWIDTH;
}

void	compute_floor_values(t_box *box)
{
	box->info.cell_x = (int)(box->info.floor_x);
	box->info.cell_y = (int)(box->info.floor_y);
	box->info.tx = (int)(TEXTUREWIDTH * (box->info.floor_x - box->info.cell_x))
		& (TEXTUREWIDTH - 1);
	box->info.ty = (int)(TEXTUREHEIGHT * (box->info.floor_y - box->info.cell_y))
		& (TEXTUREHEIGHT - 1);
	box->info.floor_x += box->info.floor_step_x;
	box->info.floor_y += box->info.floor_step_y;
	box->info.floor_texture = 1;
	box->info.ceiling_texture = 1;
	box->info.distance = (int)((box->info.pos_x - box->info.floor_x)
			* (box->info.pos_x - box->info.floor_x) + (box->info.pos_y
				- box->info.floor_y) * (box->info.pos_y - box->info.floor_y));
}
