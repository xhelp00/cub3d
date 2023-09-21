/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antess <antess@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/21 17:17:50 by antess           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pyxel_put(t_image *image, int x, int y, int color)
{
	unsigned char	*pixel;

	pixel = image->addr + (y * image->line_len + x
			* (image->bits_pp / 8));
	*(unsigned int *)pixel = color;
}

void	apply_fog(t_box *box, double dist)
{
	if (dist / 100 < 1.0)
	{
		int	r = (box->info.color >> 16) & 0xFF;
		int	g = (box->info.color >> 8) & 0xFF;
		int	b = box->info.color & 0xFF;
		int	nr = r * (1 - dist / 100);
		int	ng = g * (1 - dist / 100);
		int	nb = b * (1 - dist / 100);
		box->info.color = (nr << 16 | ng << 8 | nb);
	}
	else
		box->info.color = 0;
}

int	extract_color(unsigned char *pixel)
{
	return (pixel[3] << 24 | pixel[2] << 16 | pixel[1] << 8 | pixel[0]);
}

/*
void	draw_hud(t_box *box)
{
	int	x;
	int	y;

	//HEALTH BAR
	if (box->player.h_state == 0)
		box->player.h_offset = 0;
	else if (box->player.h_state == 1)
		box->player.h_offset = 80;
	else if (box->player.h_state == 2)
		box->player.h_offset = 160;
	else if (box->player.h_state == 3)
		box->player.h_offset = 240;
	x = -1;
	while (++x < 80)
	{
		y = SCREENHEIGHT - 40;
		while (++y < SCREENHEIGHT)
		{
			if (x < (int)box->timer % 120 && x > (int)box->timer % 120 - 40)
				my_mlx_pyxel_put(&box->image, x, y, extract_color(&box->player.h_bar.addr[(x + box->player.h_offset) * 4 + box->player.h_bar.line_len * (y - (SCREENHEIGHT - 40))]));
			else
				my_mlx_pyxel_put(&box->image, x, y, extract_color(&box->player.h_bar.addr[1 * 4 + box->player.h_bar.line_len * (y - (SCREENHEIGHT - 40) + 48)]));
		}
	}

	//GUN
	if ((box->info.pos_x > 3.9 && box->info.pos_x < 4.1) && (box->info.pos_y > 3.9 && box->info.pos_y < 4.1))
		box->player.has_gun = 1;
	if (box->player.has_gun > 0)
	{
		x = -1;
		while (++x < SCREENWIDTH)
		{
			y = -1;
			while (++y < SCREENHEIGHT)
			{
				if (box->player.has_gun == 1)
				{
					box->info.color = extract_color(&box->player.gun_overlay.addr[x * 4 + box->player.gun_overlay.line_len * y]);
					if ((box->info.color & 0x00FFFFFF) != 0)
						my_mlx_pyxel_put(&box->image, x, y, box->info.color);
				}
				if (x >= 80 && x < 160 && y >= 640)
				{
					box->info.color = extract_color(&box->player.gun_hotbar.addr[(x - 80) * 4 + box->player.gun_hotbar.line_len * (y - 640)]);
					if ((box->info.color & 0x00FFFFFF) != 0)
						my_mlx_pyxel_put(&box->image, x, y, box->info.color);
				}
			}
		}
	}
}
*/
/*	Redraw

*/
void	redraw(t_box *box)
{
	char	*fps;

	mlx_destroy_image(box->mlx, box->image.img);
	box->image.bits_pp = 0;
	box->image.line_len = 0;
	box->image.endian = 0;
	box->image.img = mlx_new_image(box->mlx, SCREENWIDTH, SCREENHEIGHT);
	//box->image.addr = malloc(SCREENWIDTH * SCREENHEIGHT * sizeof(unsigned char *));
	box->image.addr = (unsigned char *)mlx_get_data_addr(box->image.img,
			&box->image.bits_pp, &box->image.line_len, &box->image.endian);
	//printf("%i %i %i", box->image.bits_pp, box->image.line_len, box->image.endian);
	cast_floor(box);
	cast_wall(box);
	cast_obj(box);
	cal_move(box);
	cal_ene_move(box);
	//print_map_contents(box);
    //fill_buffer_with_color(box->image.addr, SCREENWIDTH, SCREENHEIGHT, 0x00FF0000);

	drawMinimap(box);
	//single_square_test(box);
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
	fps = ft_itoa(1.0 / box->info.frame_time);
	mlx_string_put(box->mlx, box->win, 20, 20, 0x00FFFFFF, fps);

	free(fps);
}
