/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/06 14:38:21 by jbartosi         ###   ########.fr       */
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

int	extract_color(unsigned char *pixel)
{
	return (pixel[3] << 24 | pixel[2] << 16 | pixel[1] << 8 | pixel[0]);
}

void	cal_move(t_box *box)
{
	if (box->info.rotate == 1)
	{
		box->info.old_dir_x = box->info.dir_x;
		box->info.dir_x = box->info.dir_x * cos(-box->info.rot_speed) - box->info.dir_y * sin(-box->info.rot_speed);
		box->info.dir_y = box->info.old_dir_x * sin(-box->info.rot_speed) + box->info.dir_y * cos(-box->info.rot_speed);
		box->info.old_plane_x = box->info.plane_x;
		box->info.plane_x = box->info.plane_x * cos(-box->info.rot_speed) - box->info.plane_y * sin(-box->info.rot_speed);
		box->info.plane_y = box->info.old_plane_x * sin(-box->info.rot_speed) + box->info.plane_y * cos(-box->info.rot_speed);
	}
	else if (box->info.rotate == -1)
	{
		box->info.old_dir_x = box->info.dir_x;
		box->info.dir_x = box->info.dir_x * cos(box->info.rot_speed) - box->info.dir_y * sin(box->info.rot_speed);
		box->info.dir_y = box->info.old_dir_x * sin(box->info.rot_speed) + box->info.dir_y * cos(box->info.rot_speed);
		box->info.old_plane_x = box->info.plane_x;
		box->info.plane_x = box->info.plane_x * cos(box->info.rot_speed) - box->info.plane_y * sin(box->info.rot_speed);
		box->info.plane_y = box->info.old_plane_x * sin(box->info.rot_speed) + box->info.plane_y * cos(box->info.rot_speed);
	}
	if (box->info.move_x == 1)
	{
		if (box->map[(int)(box->info.pos_x + box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			box->info.pos_x += box->info.dir_x * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_y * box->info.move_speed)] == '0')
			box->info.pos_y += box->info.dir_y * box->info.move_speed;
	}
	else if (box->info.move_x == -1)
	{
		if (box->map[(int)(box->info.pos_x - box->info.dir_x * box->info.move_speed)][(int)box->info.pos_y] == '0')
			box->info.pos_x -= box->info.dir_x * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_y * box->info.move_speed)] == '0')
			box->info.pos_y -= box->info.dir_y * box->info.move_speed;
	}
	if (box->info.move_y == 1)
	{
		if (box->map[(int)(box->info.pos_x + box->info.dir_y * box->info.move_speed)][(int)(box->info.pos_y)] == '0')
			box->info.pos_x += box->info.dir_y * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y - box->info.dir_x * box->info.move_speed)] == '0')
			box->info.pos_y -= box->info.dir_x * box->info.move_speed;
	}
	else if (box->info.move_y == -1)
	{
		if (box->map[(int)(box->info.pos_x - box->info.dir_y * box->info.move_speed)][(int)(box->info.pos_y)] == '0')
			box->info.pos_x -= box->info.dir_y * box->info.move_speed;
		if (box->map[(int)(box->info.pos_x)][(int)(box->info.pos_y + box->info.dir_x * box->info.move_speed)] == '0')
			box->info.pos_y += box->info.dir_x * box->info.move_speed;
	}

	box->old_time = box->time;
	gettimeofday(&box->time, NULL);
	box->info.frame_time = (box->time.tv_sec - box->old_time.tv_sec) +
						((box->time.tv_usec - box->old_time.tv_usec)/1000000.0);
	box->info.move_speed = box->info.frame_time * 3.0;
	box->info.rot_speed = box->info.frame_time * 1.5;
	if (box->info.sprint)
	{
		box->info.move_speed *= 2;
		box->info.rot_speed *= 1.5;
	}
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
	box->image.img = mlx_new_image(box->mlx, SCREENWIDTH, SCREENHEIGHT);
	box->image.addr = (unsigned char *)mlx_get_data_addr(box->image.img,
			&box->image.bits_pp, &box->image.line_len, &box->image.endian);
	cast_floor(box);
	cast_wall(box);
	cast_obj(box);
	cal_move(box);
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
	fps = ft_itoa(1.0 / box->info.frame_time);
	mlx_string_put(box->mlx, box->win, 20, 20, 0x00FFFFFF, fps);
	free(fps);
}
