/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_door_and_wall_dist(t_box *box)
{
	if (!box->info.door_side)
		box->info.prep_wall_dist = (box->info.door_dist_x
				- box->info.delta_dist_x);
	else
		box->info.prep_wall_dist = (box->info.door_dist_y
				- box->info.delta_dist_y);
}

void	determine_texture_properties(t_box *box)
{
	box->info.text_num = box->map[box->info.door_x][box->info.door_y] - 1 - '0';
	if (!box->info.door_side)
		box->info.wall_x = box->info.pos_y + box->info.prep_wall_dist
			* box->info.ray_dir_y;
	else
		box->info.wall_x = box->info.pos_x + box->info.prep_wall_dist
			* box->info.ray_dir_x;
	box->info.wall_x -= floor((box->info.wall_x));
	box->info.text_x = (int)(box->info.wall_x * (double)TEXTUREWIDTH);
	if (!box->info.door_side && box->info.ray_dir_x > 0)
		box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
	if (box->info.door_side && box->info.ray_dir_y < 0)
		box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
}

void	loop_draw_door(t_box *box, t_sprite *door, int x)
{
	while (box->info.draw++ < box->info.draw_end)
	{
		box->info.text_y = (int)box->info.tex_pos & (TEXTUREHEIGHT - 1);
		box->info.tex_pos += box->info.step;
		if (!door->data->opening)
			box->info.color = extract_color(&box->textures[box->info.text_num]
					.addr[box->info.text_x * 4 + box->textures[box->info
					.text_num].line_len * box->info.text_y]);
		else if (door->data->opening)
		{
			if (box->info.text_x - door->data->frame * 2 < 64 && box->info
				.text_x - door->data->frame * 2 > 0)
				box->info.color = extract_color(&box->textures[box->info
						.text_num].addr[(box->info.text_x - door->data->frame
							* 2) * 4 + box->textures[box->info.text_num]
						.line_len * box->info.text_y]);
			else
				box->info.color = 0;
		}
		if ((box->info.color & 0x00FFFFFF) != 0)
		{
			apply_fog(box, box->info.prep_wall_dist * 9);
			my_mlx_pyxel_put(&box->image, x, box->info.draw, box->info.color);
		}
	}
}

void	draw_the_door(t_box *box, int x)
{
	t_sprite	*door;

	door = find_door(box, box->info.door_x, box->info.door_y);
	box->info.step = 1.0 * TEXTUREHEIGHT / box->info.line_height;
	box->info.tex_pos = (box->info.draw_start - box->info.pitch
			- (box->info.pos_z / box->info.prep_wall_dist) - SCREENHEIGHT / 2
			+ box->info.line_height / 2) * box->info.step;
	box->info.draw = box->info.draw_start;
	loop_draw_door(box, door, x);
}

void	draw_door(t_box *box, int x)
{
	find_door_and_wall_dist(box);
	calculate_drawing_bounds(box);
	determine_texture_properties(box);
	draw_the_door(box, x);
	box->info.zbuffer[x] = box->info.prep_wall_dist;
}
