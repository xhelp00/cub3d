/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_floor_positions(t_box *box)
{
	box->info.floor_x = box->info.pos_x + box->info.row_distance
		* box->info.ray_dir_x0;
	box->info.floor_y = box->info.pos_y + box->info.row_distance
		* box->info.ray_dir_y0;
}

void	initialize_floor_casting(t_box *box, int y)
{
	setup_floor_and_ceiling(box, y);
	calculate_ray_directions(box);
	compute_perspective_values(box, y);
	compute_row_and_step_values(box);
	initialize_floor_positions(box);
}

void	calculate_drawing_bounds(t_box *box)
{
	box->info.line_height = (int)(SCREENHEIGHT / box->info.prep_wall_dist);
	box->info.draw_start = -box->info.line_height / 2 + SCREENHEIGHT / 2
		+ box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
	if (box->info.draw_start < 0)
		box->info.draw_start = 0;
	box->info.draw_end = box->info.line_height / 2 + SCREENHEIGHT / 2
		+ box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
	if (box->info.draw_end >= SCREENHEIGHT)
		box->info.draw_end = SCREENHEIGHT - 1;
}

void	handle_floor_casting(t_box *box, int x, int y)
{
	compute_floor_values(box);
	if (box->info.is_floor)
		box->info.color = extract_color(&box->textures[box->info.floor_texture]
				.addr[box->info.tx * 4 + box->textures[box->info.floor_texture]
				.line_len * box->info.ty]);
	else
		box->info.color = extract_color(&box->textures[box->info
				.ceiling_texture].addr[box->info.tx * 4 + box->textures[box
				->info.floor_texture].line_len * box->info.ty]);
	box->info.color = (box->info.color >> 1) & 8355711;
	apply_fog(box, box->info.distance);
	my_mlx_pyxel_put(&box->image, x, y, box->info.color);
}

void	cast_floor(t_box *box)
{
	int	y;
	int	x;

	y = -1;
	while (++y < SCREENHEIGHT)
	{
		initialize_floor_casting(box, y);
		x = -1;
		while (++x < SCREENWIDTH)
			handle_floor_casting(box, x, y);
	}
}
