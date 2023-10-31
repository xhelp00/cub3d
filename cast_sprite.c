/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_sprite_position(t_box *box, t_sprite *sprites)
{
	box->info.sprite_x = sprites->data->x - box->info.pos_x;
	box->info.sprite_y = sprites->data->y - box->info.pos_y;
}

void	calculate_transformations(t_box *box)
{
	box->info.inv_det = 1.0 / (box->info.plane_x * box->info.dir_y - box->info
			.dir_x * box->info.plane_y);
	box->info.transform_x = box->info.inv_det * (box->info.dir_y * box->info
			.sprite_x - box->info.dir_x * box->info.sprite_y);
	box->info.transform_y = box->info.inv_det * (-box->info.plane_y * box->info
			.sprite_x + box->info.plane_x * box->info.sprite_y);
}

void	calculate_screen_coordinates(t_box *box)
{
	box->info.sprite_screen_x = (int)((SCREENWIDTH / 2) * (1 + box->info
				.transform_x / box->info.transform_y));
	box->info.v_move_screen = (int)(VMOVE / box->info.transform_y) + box->info
		.pitch + box->info.pos_z / box->info.transform_y;
}

void	set_draw_limits(t_box *box)
{
	box->info.sprite_height = abs((int)(SCREENHEIGHT / (box->info.transform_y)))
		/ VDIV;
	box->info.draw_start_y = (-box->info.sprite_height / 2 + SCREENHEIGHT / 2)
		+ box->info.v_move_screen;
	box->info.draw_end_y = (box->info.sprite_height / 2 + SCREENHEIGHT / 2)
		+ box->info.v_move_screen;
	box->info.sprite_width = abs((int)(SCREENHEIGHT / (box->info.transform_y)))
		/ UDIV;
	box->info.draw_start_x = -box->info.sprite_width / 2 + box->info
		.sprite_screen_x;
	box->info.draw_end_x = box->info.sprite_width / 2 + box->info
		.sprite_screen_x;
	if (box->info.draw_start_y < 0)
		box->info.draw_start_y = 0;
	if (box->info.draw_end_y >= SCREENHEIGHT)
		box->info.draw_end_y = SCREENHEIGHT - 1;
	if (box->info.draw_start_x < 0)
		box->info.draw_start_x = 0;
	if (box->info.draw_end_x >= SCREENWIDTH)
		box->info.draw_end_x = SCREENWIDTH - 1;
}
