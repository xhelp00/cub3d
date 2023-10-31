/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_wall_values2(t_box *box)
{
	if (!box->info.side)
		box->info.wall_x = box->info.pos_y + box->info.prep_wall_dist
			* box->info.ray_dir_y;
	else
		box->info.wall_x = box->info.pos_x + box->info.prep_wall_dist
			* box->info.ray_dir_x;
	box->info.wall_x -= floor((box->info.wall_x));
	box->info.text_x = (int)(box->info.wall_x * (double)TEXTUREWIDTH);
	if (!box->info.side && box->info.ray_dir_x > 0)
		box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
	if (box->info.side && box->info.ray_dir_y < 0)
		box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
	box->info.step = 1.0 * TEXTUREHEIGHT / box->info.line_height;
	box->info.tex_pos = (box->info.draw_start - box->info.pitch - (box->info
				.pos_z / box->info.prep_wall_dist) - SCREENHEIGHT / 2
			+ box->info.line_height / 2) * box->info.step;
	box->info.draw = box->info.draw_start;
}

// Computing necessary values to draw walls.
void	compute_wall_values(t_box *box)
{
	if (!box->info.side)
		box->info.prep_wall_dist = (box->info.side_dist_x - box->info
				.delta_dist_x);
	else
		box->info.prep_wall_dist = (box->info.side_dist_y - box->info
				.delta_dist_y);
	box->info.line_height = (int)(SCREENHEIGHT / box->info.prep_wall_dist);
	box->info.draw_start = -box->info.line_height / 2 + SCREENHEIGHT / 2
		+ box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
	if (box->info.draw_start < 0)
		box->info.draw_start = 0;
	box->info.draw_end = box->info.line_height / 2 + SCREENHEIGHT / 2
		+ box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
	if (box->info.draw_end >= SCREENHEIGHT)
		box->info.draw_end = SCREENHEIGHT - 1;
	box->info.text_num = box->map[box->info.map_x][box->info.map_y] - 1 - '0';
	compute_wall_values2(box);
}

// Drawing each wall column.
void	draw_wall_column(t_box *box, int x)
{
	while (box->info.draw++ < box->info.draw_end)
	{
		box->info.text_y = (int)box->info.tex_pos & (TEXTUREHEIGHT - 1);
		box->info.tex_pos += box->info.step;
		box->info.color = extract_color(&box->textures[box->info.text_num]
				.addr[box->info.text_x * 4 + box->textures[box->info.text_num]
				.line_len * box->info.text_y]);
		if (box->info.side)
			box->info.color = (box->info.color >> 1) & 8355711;
		apply_fog(box, box->info.prep_wall_dist * 9);
		my_mlx_pyxel_put(&box->image, x, box->info.draw, box->info.color);
	}
	box->info.zbuffer[x] = box->info.prep_wall_dist;
	if (box->info.door)
		draw_door(box, x);
	box->info.ray[x].end_x = (box->info.map_y * 10) - (box->map_width * 10)
		+ SCREENWIDTH - MINIMAP_OFFSET;
	box->info.ray[x].end_y = (box->info.map_x * 10) + MINIMAP_OFFSET;
	if (box->info.ray[x].end_x < (box->info.pos_y * 10) + SCREENWIDTH
		- (box->map_width * 10) - MINIMAP_OFFSET -5)
		box->info.ray[x].end_x += 10;
	if (box->info.ray[x].end_y < (box->info.pos_x * 10) + MINIMAP_OFFSET -5)
		box->info.ray[x].end_y += 10;
}

void	cast_wall(t_box *box)
{
	int	x;

	x = -1;
	while (++x < SCREENWIDTH)
	{
		init_rays(box, x);
		perform_dda(box);
		compute_wall_values(box);
		draw_wall_column(box, x);
	}
}
