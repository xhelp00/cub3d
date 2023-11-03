/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_stats_on_hud(t_box *box, int x, int y)
{
	box->info.color = 0;
	if (y > 185 && y < 215 && x > 20 && x < 50)
		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 5
					- ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len
				* (y - 185 - ((y - 185) / 2))]);
	else if (y > 225 && y < 255 && x > 20 && x < 50)
		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 20
					- ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len
				* (y - 210 - ((y - 225) / 2))]);
	else if (y > 268 && y < 298 && x > 20 && x < 55)
		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x + 10
					- ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len
				* (y - 268 - ((y - 268) / 2))]);
	else if (y > 305 && y < 335 && x > 20 && x < 50)
		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 5
					- ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len
				* (y - 290 - ((y - 305) / 2))]);
	else if (y > 350 && y < 380 && x > 20 && x < 50)
	{
		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 20
					- ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len
				* (y - 350 - ((y - 350) / 2))]);
	}
	if ((box->info.color & 0x00FFFFFF) != 0)
		my_mlx_pyxel_put(&box->image, x, y, box->info.color);
}

void	draw_pickups_on_hud(t_box *box, int x, int y)
{
	if (y > 50 && y < 80 && x > 20 && x < 50)
		box->info.color = extract_color(&box->textures[UI_PICKUPS].addr[(x - 4
					- ((x - 20) / 2)) * 4 + box->textures[UI_PICKUPS].line_len
				* (y - 50 - ((y - 50) / 2))]);
	if ((box->info.color & 0x00FFFFFF) != 0)
		my_mlx_pyxel_put(&box->image, x, y, box->info.color);
}

void	draw_hearts_on_hud(t_box *box, int x, int y)
{
	int	i;

	i = 0;
	while (i < (box->player.max_hp + 1) / 2)
	{
		if (y > 15 && y < 45 && x > 50 + (i * 32) && x < 82 + (i * 32))
		{
			box->info.color = extract_heart_color(box, x, y, i);
			if ((box->info.color & 0x00FFFFFF) != 0)
				my_mlx_pyxel_put(&box->image, x, y, box->info.color);
		}
		i++;
	}
}

void	draw_items_on_hud(t_box *box, int x, int y)
{
	t_item	*items;
	int		i;

	items = box->items;
	i = 0;
	while (items && i < 20)
	{
		if (y > 650 && y < 682 && x > 20 + (i * 32) && x < 52 + (i * 32))
		{
			box->info.color = extract_color(&box->textures[items->data->texture]
					.addr[((x - 20 + ((items->data->id % 20) * 32)) - (i * 32))
					* 4 + box->textures[items->data->texture].line_len
					* (y - 650)]);
			if ((box->info.color & 0x00FFFFFF) != 0)
				my_mlx_pyxel_put(&box->image, x, y, box->info.color);
		}
		i++;
		items = items->next;
	}
}

void	draw_hud(t_box *box)
{
	int	x;
	int	y;

	y = -1;
	while (++y < SCREENHEIGHT)
	{
		x = -1;
		while (++x < SCREENWIDTH)
		{
			if (box->hud)
			{
				draw_stats_on_hud(box, x, y);
				draw_items_on_hud(box, x, y);
			}
			draw_pickups_on_hud(box, x, y);
			draw_hearts_on_hud(box, x, y);
		}
	}
}
