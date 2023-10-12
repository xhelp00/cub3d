/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 14:56:45 by phelebra         ###   ########.fr       */
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
		box->info.color = ((int)(((box->info.color >> 16) & 0xFF) * (1 - dist / 100)) << 16
				| (int)(((box->info.color >> 8) & 0xFF) * (1 - dist / 100)) << 8
				| (int)((box->info.color & 0xFF) * (1 - dist / 100)));
	else
		box->info.color = 0;
}

void	hit_mark(t_box *box, t_sprite *sprite)
{
	if (sprite->data->hit && sprite->data->texture != TEAR)
	{
		sprite->data->frame = (((box->time.tv_sec - sprite->data->hit_time.tv_sec) + ((box->time.tv_usec - sprite->data->hit_time.tv_usec) / 1000000.0)) * 10);
		//printf("FRAME: %i\n", sprite->data->frame);
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

void	draw_hud(t_box *box)
{
	//char	*nbr;
	int		x;
	int		y;
	int		i;

	
	y = -1;
	while (++y < SCREENHEIGHT)
	{
		x = -1;
		while (++x < SCREENWIDTH)
		{
			box->info.color = 0;
			if (y > 185 && y < 215 && x > 20 && x < 50)
				box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 5 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 185 - ((y - 185) / 2))]);
			else if (y > 225 && y < 255 && x > 20 && x < 50)
				box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 20 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 210 - ((y - 225) / 2))]);
			else if (y > 268 && y < 298 && x > 20 && x < 60)
				box->info.color = extract_color(&box->textures[UI_STATS].addr[(x + 10 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 268 - ((y - 268) / 2))]);
			else if (y > 305 && y < 335 && x > 20 && x < 50)
				box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 5 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 290 - ((y - 305) / 2))]);
			else if (y > 350 && y < 380 && x > 20 && x < 50)
				box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 20 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 350 - ((y - 350) / 2))]);
			if ((box->info.color & 0x00FFFFFF) != 0)
				my_mlx_pyxel_put(&box->image, x, y, box->info.color);
			box->info.color = 0;
			i = -1;
			while (++i < ((box->player.max_hp + 1) / 2))
			{
				if (y > 15 && y < 45 && x > 50 + (i * 32) && x < 82 + (i * 32))
				{
					if (i < (box->player.hp / 2))
						box->info.color = extract_color(&box->textures[UI_HEARTS].addr[((x - 50) - ((x + (i * 32) - 50) / 2)) * 4 + box->textures[UI_HEARTS].line_len * (y - 15 - ((y - 15) / 2))]);
					else if (box->player.hp % 2 == 1 && i == (box->player.hp / 2))
						box->info.color = extract_color(&box->textures[UI_HEARTS].addr[((x - 34) - ((x + (i * 32) - 50) / 2)) * 4 + box->textures[UI_HEARTS].line_len * (y - 15 - ((y - 15) / 2))]);
					else
						box->info.color = extract_color(&box->textures[UI_HEARTS].addr[((x - 18) - ((x + (i * 32) - 50) / 2)) * 4 + box->textures[UI_HEARTS].line_len * (y - 15 - ((y - 15) / 2))]);
					if ((box->info.color & 0x00FFFFFF) != 0)
							my_mlx_pyxel_put(&box->image, x, y, box->info.color);
				}
			}
		}
	}
}

/*	Redraw

*/
void	redraw(t_box *box)
{
	char	*fps;
	char 	*nbr;

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
	cal_sprite_move(box);
	//print_map_contents(box);
    //fill_buffer_with_color(box->image.addr, SCREENWIDTH, SCREENHEIGHT, 0x00FF0000);

	drawMinimap(box);
	draw_hud(box);
	//single_square_test(box);
	
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);

	fps = ft_itoa(1.0 / box->info.frame_time);
	mlx_string_put(box->mlx, box->win, 20, 20, 0x00FFFFFF, fps);

	if (box->player.hit && box->player.frame % 2 == 0)
		box->info.color = 0x00FF0000;
	else
		box->info.color = 0x00FFFFFF;
	nbr = ft_itoa(box->player.speed);
	mlx_string_put(box->mlx, box->win, 65, 203, box->info.color, nbr);
	nbr = (free(nbr), ft_itoa(box->player.range));
	mlx_string_put(box->mlx, box->win, 65, 245, box->info.color, nbr);
	nbr = (free(nbr), ft_itoa(box->player.fire_rate));
	mlx_string_put(box->mlx, box->win, 65, 287, box->info.color, nbr);
	nbr = (free(nbr), ft_itoa(box->player.shot_speed));
	mlx_string_put(box->mlx, box->win, 65, 329, box->info.color, nbr);
	nbr = (free(nbr), ft_itoa(box->player.dmg));
	mlx_string_put(box->mlx, box->win, 65, 371, box->info.color, nbr);
	free(nbr);

	free(fps);
}
