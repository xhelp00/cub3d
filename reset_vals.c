/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_vals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mouse_vals(t_box *box)
{
	box->mouse.xdistance = 0;
	box->mouse.ydistance = 0;
	box->mouse.x = 0;
	box->mouse.y = 0;
}

void	init_player_vals(t_box *box)
{
	box->player.speed = 100;
	box->player.range = 65;
	box->player.fire_rate = 50;
	box->player.shot_speed = 10;
	box->player.dmg = 35;
	box->player.cry = 0;
	box->player.state = 0;
	box->player.hp = 6;
	box->player.max_hp = 6;
	box->player.hit = 0;
	box->player.n_key = 0;
	gettimeofday(&box->player.last_tear, NULL);
}

void	init_vals(t_box *box)
{
	init_general_vals(box);
	init_pos_dir_vals(box);
	init_time_move_vals(box);
	init_attr_vals(box);
	init_misc_vals(box);
	init_mouse_vals(box);
	init_player_vals(box);
}

void	reset_vals(t_box *box)
{
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.map_x = 0;
	box->info.map_y = 0;
	box->info.hit = 0;
	box->info.text_num = 0;
	box->info.color = 0;
	box->info.door = 0;
	box->info.door_x = 0;
	box->info.door_y = 0;
	box->info.door_dist_x = 0;
	box->info.door_dist_y = 0;
	box->info.door_side = 0;
}
