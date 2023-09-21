/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:36:11 by phelebra          #+#    #+#             */
/*   Updated: 2023/09/20 10:06:55 by phelebra         ###   ########.fr       */
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
			my_mlx_pyxel_put(&box->image, tmp_x, tmp_y, rect->fill_color);
		}
	}
}