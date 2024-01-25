/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:36:11 by phelebra          #+#    #+#             */
/*   Updated: 2023/10/06 15:40:57 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_rect *rect, t_box *box)
{
	int	i;
	int	j;
	int	tmp_x = 0;
	int	tmp_y = 0;

	//rect->border_width--;
	i = -1;
	while (++i < rect->height)
	{
		j = -1;
		while (++j < rect->width)
		{
			//printf("Drawing pixel at %d, %d\n", tmp_x, tmp_y);

			tmp_x = rect->x + j;
			tmp_y = rect->y + i;
			/* if (i <= rect->border_width || j <= rect->border_width
				|| i >= rect->height - 1 - rect->border_width
				|| j >= rect->width - 1 - rect->border_width)
				img[tmp_y * res_width + tmp_x] = rect->border_color;
			else */
				//img[(tmp_y * box->image.line_len) + (tmp_x * (box->image.bits_pp / 8))] = rect->fill_color;
			my_mlx_pyxel_put(&box->image, tmp_x, tmp_y, 0xFF << 24 | rect->fill_color);
			my_mlx_pyxel_put(&box->shaders, tmp_x, tmp_y, pixel_visibility(1));
		}
	}
}

 void	draw_line(t_line *line, t_box *box)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = line->end_x - line->begin_x;
	delta_y = line->end_y - line->begin_y;
	pixels = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = line->begin_x;
	pixel_y = line->begin_y;
	while (pixels)
	{
		//img[(int)pixel_y * res_width + (int)pixel_x] = line->color;
		my_mlx_pyxel_put(&box->image, (int)pixel_x, (int)pixel_y, 0xFF << 24 | line->color);
		my_mlx_pyxel_put(&box->shaders, (int)pixel_x, (int)pixel_y, pixel_visibility(1));
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}
