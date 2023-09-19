/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:46:15 by phelebra          #+#    #+#             */
/*   Updated: 2023/09/19 15:15:30 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawMinimap(t_box *box)
{
	draw_map(box);

}

void	draw_map(t_box *box)
{
	t_rect	rect;
	int		i = 0;
	int		j = 0;
	char	grid_item;

	i = -1;
	while (++i < box->map_height)
	{
		j = -1;
		while (++j < box->map_width)
		{
			grid_item = box->map[i][j];
			rect.x = (j * 10) + SCREENWIDTH - (box->map_width * 10) - MINIMAP_OFFSET;
			rect.y = i * 10 + MINIMAP_OFFSET;
			rect.width = 10;
			rect.height = 10;
			rect.border_color = 0x0014213d;
			rect.border_width = 0;
			rect.fill_color = get_fill_color(grid_item);
			draw_rect(&rect, box->image.addr, SCREENWIDTH, box);
		}
	}
}

int		get_fill_color(char grid_item)
{
	int	color;

	if (grid_item == '0')
		color = 0x00757575;
	else
		color = 0x0014213d;
	return (color);
}
