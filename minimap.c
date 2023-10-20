/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:46:15 by phelebra          #+#    #+#             */
/*   Updated: 2023/10/09 15:26:56 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawMinimap(t_box *box)
{
	draw_map(box);
	draw_player(box);
	draw_rays(box);
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
			rect.y = (i * 10) + MINIMAP_OFFSET;
			rect.width = 10;
			rect.height = 10;
			rect.border_color = 0x0014213d;
			rect.border_width = 0;
			rect.fill_color = get_fill_color(grid_item, box, i, j);
			draw_rect(&rect, box);
		}
	}
}

void	draw_player(t_box *box)
{
	t_rect	rect;
	
	rect.x = (box->info.pos_y * 10) + SCREENWIDTH - (box->map_width * 10) - MINIMAP_OFFSET -5;
	rect.y = (box->info.pos_x * 10) + MINIMAP_OFFSET -5;
	rect.fill_color = 0x00e63946;
	draw_rect(&rect, box);
}

int		get_fill_color(char grid_item, t_box *box, int i, int j)
{
	int	color;

	if (grid_item == '0')
		color = 0x00757575;
	else if (grid_item == '3')
		if (find_door(box, i, j)->data->state)
			color = 0x00939D;
		else
			color = 0x00666d;
	else
		color = 0x0014213d;
	return (color);
}

void	draw_rays(t_box *box)
{
	int		i;
	t_line	line;

	i = -1;
	while (++i < SCREENWIDTH)
	{
	line.begin_x = (box->info.pos_y * 10) + SCREENWIDTH - (box->map_width * 10) - MINIMAP_OFFSET ;
	line.begin_y = (box->info.pos_x * 10) + MINIMAP_OFFSET ;
	
	line.end_x = box->info.ray[i].end_x;
	line.end_y = box->info.ray[i].end_y;
	
	line.color = 0x00e63946;
	draw_line(&line, box);
	}
}