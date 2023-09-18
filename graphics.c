/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 13:36:11 by phelebra          #+#    #+#             */
/*   Updated: 2023/09/18 14:28:29 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_rect(t_rect *rect, unsigned char *img, int res_width)
{
	int	i;
	int	j;
	int	tmp_x;
	int	tmp_y;

	rect->border_width--;
	i = -1;
	while (++i < rect->height)
	{
		j = -1;
		while (++j < rect->width)
		{
			tmp_x = rect->x + j;
			tmp_y = rect->y + i;
			if (i <= rect->border_width || j <= rect->border_width
				|| i >= rect->height - 1 - rect->border_width
				|| j >= rect->width - 1 - rect->border_width)
				img[tmp_y * res_width + tmp_x] = rect->border_color;
			else
				img[tmp_y * res_width + tmp_x] = rect->fill_color;
		}
	}
}