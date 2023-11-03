/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:04:52 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned int	blend_red_with_current_color(unsigned int current_color,
	unsigned char alpha, unsigned char red_value)
{
	unsigned char	current_red;
	unsigned char	blended_red;

	current_red = (current_color >> 16) & 0xFF;
	blended_red = (red_value * alpha + current_red * (255 - alpha)) / 255;
	return ((current_color & 0xFF00FFFF) | (blended_red << 16));
}

void	process_row_for_red_blending(t_box *box, int y)
{
	unsigned int	*pixel_buffer;
	unsigned int	current_color;
	int				x;
	int				index;

	pixel_buffer = (unsigned int *)box->image.addr;
	x = 0;
	while (x < SCREENWIDTH)
	{
		index = y * box->image.line_len / 4 + x;
		current_color = pixel_buffer[index];
		pixel_buffer[index] = blend_red_with_current_color(current_color,
				0x80, 0xFF);
		x++;
	}
}

void	fill_screen_red(t_box *box)
{
	int	y;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		process_row_for_red_blending(box, y);
		y++;
	}
}

void	apply_fog(t_box *box, double dist)
{
	if (dist / 100 < 1.0)
		box->info.color = ((int)(((box->info.color >> 16) & 0xFF)
					* (1 - dist / 100)) << 16
				| (int)(((box->info.color >> 8) & 0xFF) * (1 - dist / 100)) << 8
				| (int)((box->info.color & 0xFF) * (1 - dist / 100)));
	else
		box->info.color = 0;
}

void	hit_mark(t_box *box, t_sprite *sprite)
{
	if (sprite->data->hit && sprite->data->texture != TEAR)
	{
		sprite->data->frame = (((box->time.tv_sec
						- sprite->data->hit_time.tv_sec) + ((box->time.tv_usec
							- sprite->data->hit_time.tv_usec)
						/ 1000000.0)) * 10);
		if (sprite->data->frame < 1)
			box->info.color = 0x00FF0000;
		else
			sprite->data->hit = 0;
	}
}
