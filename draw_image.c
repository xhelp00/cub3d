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

void fill_screen_red(t_box *box)
{
	int x, y;
	unsigned char alpha = 0x80;
	unsigned char red_value = 0xFF;
	unsigned int *pixel_buffer = (unsigned int *)box->image.addr;
	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			int index = y * box->image.line_len / 4 + x;
			unsigned int current_color = pixel_buffer[index];
			unsigned char current_red = (current_color >> 16) & 0xFF;
			unsigned char blended_red = (red_value * alpha + current_red * (255 - alpha)) / 255;
			pixel_buffer[index] = (current_color & 0xFF00FFFF) | (blended_red << 16);
			x++;
		}
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

/*
	my_mlx_put_image_to_window

	Puts either full image, if sprite_id is -1,
	or sprite form spritesheet with the spirte_id id
*/
void	my_mlx_put_image_to_window(t_box *box, t_image *image, int x, int y, int sprite_id)
{
	if (sprite_id >= 0)
		mlx_put_image_to_window(box->mlx, box->win, image->img, x, y, 0 + (image->one_x * (sprite_id % image->n_col)), 0 + (image->one_y * (sprite_id / image->n_col)), image->one_x, image->one_y);
	else
		mlx_put_image_to_window(box->mlx, box->win, image->img, x, y, 0, 0, image->width, image->height);
}

/*
	new_image

	Creates a new mlx_image_alpha and sets its variables
*/
void	new_image(void *mlx, t_image *image, int width, int height)
{
	image->img = mlx_new_image_alpha(mlx, width, height);
	image->width = width;
	image->height = height;
	image->addr = (unsigned char *)mlx_get_data_addr(image->img,
			&image->bits_pp, &image->line_len, &image->endian);
}

/*
	clear_image

	Sets every pixel in image to 0
	which means it will be trasparent
*/
void	clear_image(t_image *image)
{
	ft_memset(image->addr, 0, image->height * image->width * 4);
}

/*
	png_file_to_image

	Tryes to convert png file to image
*/
void	png_file_to_image(void *mlx, t_image *image, char *file)
{
	cp_image_t	png_img;
	cp_pixel_t 	*mlx_img_data;
	int			i;

	png_img = cp_load_png(file);
	if (png_img.pix == NULL)
		return ;
	cp_premultiply(&png_img);
	image->img = mlx_new_image_alpha(mlx, png_img.w, png_img.h);
	if (image->img == NULL)
		return (free(png_img.pix), (void) 0);
	mlx_img_data = (cp_pixel_t *)mlx_get_data_addr(image->img, &image->bits_pp, &image->line_len, &image->endian);
	i = -1;
	while (i++ < png_img.w * png_img.h)
	{
		mlx_img_data[i].r = png_img.pix[i].b;
		mlx_img_data[i].g = png_img.pix[i].g;
		mlx_img_data[i].b = png_img.pix[i].r;
		mlx_img_data[i].a = png_img.pix[i].a;
	}
	image->width = png_img.w;
	image->height = png_img.h;
	free(png_img.pix);
}

/*
	split_spritesheet

	Used on spritesheet images to split it into sprites with ids
	Needs to know number of images in rows and collums beforehand
	- This step can be done automatically in the future
*/
void	split_spritesheet(t_image *image, int n_col, int n_row, int one_x, int one_y)
{
	image->n_col = n_col;
	image->n_row = n_row;
	if (one_x == 0)
		image->one_x = image->width / image->n_col;
	else
		image->one_x = one_x;
	if (one_y == 0)
		image->one_y = image->height / image->n_row;
	else
		image->one_y = one_y;
}

unsigned int	pixel_visibility(float fade)
{
	return ((int)((1.0 - fade) * 255) << 24 | 0 << 16 | 0 << 8 | 0);
}

void	apply_fog(t_box *box, double dist)
{
	double fade = (1 - dist / 100);
	if (dist / 100 < 1.0)
		box->info.color = ((int)((box->info.color & 0xFF0000) * fade) & 0xFF0000)
				| ((int)((box->info.color & 0xFF00) * fade) & 0xFF00)
				| (int)((box->info.color & 0xFF) * fade);
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
	t_item	*items;

	my_mlx_put_image_to_window(box, &box->textures[UI_PICKUPS], 20, 50, 1);
	if (box->hud)
	{
		my_mlx_put_image_to_window(box, &box->textures[UI_STATS], 20, 185, 1);
		my_mlx_put_image_to_window(box, &box->textures[UI_STATS], 20, 225, 4);
		my_mlx_put_image_to_window(box, &box->textures[UI_STATS], 20, 265, 2);
		my_mlx_put_image_to_window(box, &box->textures[UI_STATS], 20, 305, 5);
		my_mlx_put_image_to_window(box, &box->textures[UI_STATS], 20, 350, 0);
	}
	y = -1;
	while (++y < SCREENHEIGHT)
	{
		x = -1;
		while (++x < SCREENWIDTH)
		{
			// box->info.color = 0;
			// if (box->hud)
			// {
			// 	if (y > 185 && y < 215 && x > 20 && x < 50)
			// 		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 5 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 185 - ((y - 185) / 2))]);
			// 	else if (y > 225 && y < 255 && x > 20 && x < 50)
			// 		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 20 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 210 - ((y - 225) / 2))]);
			// 	else if (y > 268 && y < 298 && x > 20 && x < 55)
			// 		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x + 10 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 268 - ((y - 268) / 2))]);
			// 	else if (y > 305 && y < 335 && x > 20 && x < 50)
			// 		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 5 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 290 - ((y - 305) / 2))]);
			// 	else if (y > 350 && y < 380 && x > 20 && x < 50)
			// 		box->info.color = extract_color(&box->textures[UI_STATS].addr[(x - 20 - ((x - 20) / 2)) * 4 + box->textures[UI_STATS].line_len * (y - 350 - ((y - 350) / 2))]);
			// }
			// if (y > 50 && y < 80 && x > 20 && x < 50)
			// 	box->info.color = extract_color(&box->textures[UI_PICKUPS].addr[(x - 4 - ((x - 20) / 2)) * 4 + box->textures[UI_PICKUPS].line_len * (y - 50 - ((y - 50) / 2))]);
			// if ((box->info.color & 0x00FFFFFF) != 0)
			// {
			// 	my_mlx_pyxel_put(&box->image, x, y, 0xFF << 24 | box->info.color);
			// 	// my_mlx_pyxel_put(&box->shaders, x, y, pixel_visibility(1));
			// }
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
					{
							my_mlx_pyxel_put(&box->image, x, y, 0xFF << 24 | box->info.color);
							// my_mlx_pyxel_put(&box->shaders, x, y, pixel_visibility(1));
					}
				}
			}
			if (box->hud)
			{
				items = box->items;
				i = 0;
				while (items && i < 20)
				{
					if (y > 650 && y < 682 && x > 20 + (i * 32) && x < 52 + (i * 32))
					{
						box->info.color = extract_color(&box->textures[items->data->texture].addr[((x - 20 + ((items->data->id % 20) * 32)) - (i * 32)) * 4 + box->textures[items->data->texture].line_len * (y - 650)]);
						if ((box->info.color & 0x00FFFFFF) != 0)
						{
								my_mlx_pyxel_put(&box->image, x, y, 0xFF << 24 | box->info.color);
								// my_mlx_pyxel_put(&box->shaders, x, y, pixel_visibility(1));
						}
					}
					i++;
					items = items->next;
				}
			}
		}
	}
}

/*	Redraw

*/
void	redraw(t_box *box)
{
	char 	*nbr;
	int 	y;
	int 	x;

	mlx_destroy_image(box->mlx, box->image.img);
	new_image(box->mlx, &box->image, SCREENWIDTH, SCREENHEIGHT);

	mlx_destroy_image(box->mlx, box->shaders.img);
	new_image(box->mlx, &box->shaders, SCREENWIDTH, SCREENHEIGHT);

	y = -1;
	while (++y < SCREENHEIGHT)
	{
		x = -1;
		while (++x < SCREENWIDTH)
			my_mlx_pyxel_put(&box->shaders, x, y, pixel_visibility(0));
	}

	cast_floor(box);
	cast_wall(box);

	cast_obj(box);
	cal_move(box);
	cal_sprite_move(box);
	//print_map_contents(box);
    //fill_buffer_with_color(box->image.addr, SCREENWIDTH, SCREENHEIGHT, 0x00FF0000);

	drawMinimap(box);
	//single_square_test(box);

	if (!box->won && !box->lost)
	{
		if (box->player.hit)
			fill_screen_red(box);
		my_mlx_put_image_to_window(box, &box->image, 0, 0, -1);
		my_mlx_put_image_to_window(box, &box->shaders, 0, 0, -1);
		draw_hud(box);

	}
	else if (box->lost)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		my_mlx_put_image_to_window(box, &box->textures[GRIM], 0, 0, -1);
		if (box->player.frame > 100)
			exit_hook(box);
	}
	else if (box->win)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		my_mlx_put_image_to_window(box, &box->textures[WIN], 0, 0, -1);
		if (box->player.frame > 100)
			exit_hook(box);
	}

	nbr = ft_itoa(1.0 / box->info.frame_time);
	mlx_string_put(box->mlx, box->win, 20, 20, 0x00FFFFFF, nbr);
	if (box->hud)
	{
		nbr = (free(nbr), ft_itoa(box->player.speed));
		mlx_string_put(box->mlx, box->win, 65, 203, 0x00FFFFFF, nbr);
		nbr = (free(nbr), ft_itoa(box->player.range));
		mlx_string_put(box->mlx, box->win, 65, 245, 0x00FFFFFF, nbr);
		nbr = (free(nbr), ft_itoa(box->player.fire_rate));
		mlx_string_put(box->mlx, box->win, 65, 287, 0x00FFFFFF, nbr);
		nbr = (free(nbr), ft_itoa(box->player.shot_speed));
		mlx_string_put(box->mlx, box->win, 65, 329, 0x00FFFFFF, nbr);
		nbr = (free(nbr), ft_itoa(box->player.dmg));
		mlx_string_put(box->mlx, box->win, 65, 371, 0x00FFFFFF, nbr);
	}
	nbr = (free(nbr), ft_itoa(box->player.n_key));
	mlx_string_put(box->mlx, box->win, 50, 70, 0x00FFFFFF, nbr);
	free(nbr);
}
