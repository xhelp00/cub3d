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
	int	tmp_x;
	int	tmp_y;

	tmp_x = 0;
	tmp_y = 0;
	i = -1;
	while (++i < rect->height)
	{
		j = -1;
		while (++j < rect->width)
		{
			tmp_x = rect->x + j;
			tmp_y = rect->y + i;
			my_mlx_pyxel_put(&box->image, tmp_x, tmp_y, rect->fill_color);
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
		my_mlx_pyxel_put(&box->image, (int)pixel_x, (int)pixel_y, line->color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels--;
	}
}
