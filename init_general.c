/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_general.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_general_vals(t_box *box)
{
	box->info.ray = malloc(sizeof(t_ray) * SCREENWIDTH + 1);
	box->sprites = NULL;
	box->items = NULL;
	box->n_sprites = 0;
	box->god = 0;
	box->hud = 1;
	box->won = 0;
	box->lost = 0;
	box->music = 0;
	box->pid = 0;
	box->input_index = 0;
	ft_memset(box->input_buffer, 0, sizeof(box->input_buffer));
}

void	init_pos_dir_vals(t_box *box)
{
	box->info.pos_x = 4;
	box->info.pos_y = 5;
	box->info.pos_z = 0;
	box->info.dir_x = -1.0;
	box->info.dir_y = 0;
	box->info.start_dir_x = -1.0;
	box->info.start_dir_y = 0;
	box->info.plane_x = 0;
	box->info.plane_y = 0.66;
}

void	init_time_move_vals(t_box *box)
{
	gettimeofday(&box->time, NULL);
	gettimeofday(&box->old_time, NULL);
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.rotate = 0;
	box->info.move_x = 0;
	box->info.move_y = 0;
}

void	init_attr_vals(t_box *box)
{
	box->info.hit = 0;
	box->info.sprint = 0;
	box->info.pitch = 0;
	box->info.up_down = 0;
	box->info.old_dir_x = 0;
	box->info.old_plane_x = 0;
	box->info.door = 0;
}

void	init_misc_vals(t_box *box)
{
	box->info.distance = 0;
	box->info.color = 0;
	box->info.rot_speed = 0;
	box->info.move_speed = 0;
	box->info.zbuffer = malloc(SCREENWIDTH * sizeof(double));
}
