/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:46:15 by phelebra          #+#    #+#             */
/*   Updated: 2023/09/18 15:45:17 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

# define MINIMAP_RATIO 200
# define MINIMAP_OFFSET 10

void drawMinimap(t_box *box)
{
	//my_mlx_pyxel_put(&box->image, SCREENWIDTH - 10, SCREENHEIGHT -10, 987130);
	draw_map(box);

}

void	draw_map(t_box *box)
{
	t_rect	rect;
	int		i;
	int		j;
	char	grid_item;

	i = -1;
	while (++i < box->map_height)
	{
		j = -1;
		while (++j < box->map_width)
		{
			grid_item = box->map[i][j];
			rect.x = j * 20 + MINIMAP_OFFSET;
			rect.y = i * 20 + MINIMAP_OFFSET;
			rect.width = 20;
			rect.height = 20;
			rect.border_color = 0x0014213d;
			rect.border_width = 0;
			rect.fill_color = get_fill_color(grid_item);
			draw_rect(&rect, box->image.addr, SCREENWIDTH);
		}
	}
}

int		get_fill_color(char grid_item)
{
	int	color;

	if (grid_item == '0')
		color = 0x757575;
	else
		color = 0x0014213d;
	return (color);
}
