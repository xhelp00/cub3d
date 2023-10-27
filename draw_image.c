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

int	extract_color(unsigned char *pixel)
{
	return (pixel[3] << 24 | pixel[2] << 16 | pixel[1] << 8 | pixel[0]);
}

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

unsigned int	extract_heart_color(t_box *box, int x, int y, int i)
{
	int	xoffset;
	int	index;

	xoffset = 0;
	if (i < (box->player.hp / 2))
		xoffset = x - 50;
	else if (box->player.hp % 2 == 1 && i == (box->player.hp / 2))
		xoffset = x - 34;
	else
		xoffset = x - 18;
	index = (xoffset - ((x + (i * 32) - 50) / 2)) * 4
		+ box->textures[UI_HEARTS].line_len * (y - 15 - ((y - 15) / 2));
	return (extract_color(&box->textures[UI_HEARTS].addr[index]));
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

void	init_redraw(t_box *box)
{
	mlx_destroy_image(box->mlx, box->image.img);
	box->image.bits_pp = 0;
	box->image.line_len = 0;
	box->image.endian = 0;
	box->image.img = mlx_new_image(box->mlx, SCREENWIDTH, SCREENHEIGHT);
	box->image.addr = (unsigned char *)mlx_get_data_addr(box->image.img,
			&box->image.bits_pp, &box->image.line_len, &box->image.endian);
}

void	handle_game_state(t_box *box)
{
	double	frame;

	if (!box->won)
	{
		if (box->player.hit)
			fill_screen_red(box);
		mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
	}
	if (box->won || box->lost)
	{
		frame = ((((box->time.tv_sec - box->fin_time.tv_sec)
						+ ((box->time.tv_usec - box->fin_time.tv_usec)
							/ 1000000.0)) * 10) * 16) / 10;
		box->player.frame = frame;
		if (box->lost)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img,
				360, 95);
		else if (box->win)
			mlx_put_image_to_window(box->mlx, box->win, box->textures[WIN].img,
				320, 40);
		if (box->player.frame > 100)
			exit_hook(box);
	}
}

void	display_and_free_stat(t_box *box, int value, int x, int y)
{
	char	*nbr;

	nbr = ft_itoa(value);
	mlx_string_put(box->mlx, box->win, x, y, 0x00FFFFFF, nbr);
	free(nbr);
}

void	update_hud(t_box *box)
{
	char	*nbr;

	nbr = ft_itoa(1.0 / box->info.frame_time);
	mlx_string_put(box->mlx, box->win, 20, 20, 0x00FFFFFF, nbr);
	free(nbr);
	if (box->hud)
	{
		display_and_free_stat(box, box->player.speed, 65, 203);
		display_and_free_stat(box, box->player.range, 65, 245);
		display_and_free_stat(box, box->player.fire_rate, 65, 287);
		display_and_free_stat(box, box->player.shot_speed, 65, 329);
		display_and_free_stat(box, box->player.dmg, 65, 371);
	}
	nbr = ft_itoa(box->player.n_key);
	mlx_string_put(box->mlx, box->win, 50, 70, 0x00FFFFFF, nbr);
	free(nbr);
}

void	redraw(t_box *box)
{
	init_redraw(box);
	cast_floor(box);
	cast_wall(box);
	cast_obj(box);
	cal_move(box);
	cal_sprite_move(box);
	draw_minimap(box);
	draw_hud(box);
	handle_game_state(box);
	update_hud(box);
}
