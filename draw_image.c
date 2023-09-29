/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:00:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/23 14:37:42 by jbartosi         ###   ########.fr       */
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
	if (sprite->data->state == HIT && sprite->data->texture != 30)
	{
		sprite->data->frame = (((box->time.tv_sec - sprite->data->hit_time.tv_sec) + ((box->time.tv_usec - sprite->data->hit_time.tv_usec) / 1000000.0)) * 10);
		//printf("FRAME: %i\n", sprite->data->frame);
		if (sprite->data->frame < 1)
				box->info.color = 0x00FF0000;
		else
			sprite->data->state = IDLE;
	}
}

int	extract_color(unsigned char *pixel)
{
	return (pixel[3] << 24 | pixel[2] << 16 | pixel[1] << 8 | pixel[0]);
}

void	draw_hud(t_box *box)
{
	char	*str;

	str = ft_strjoin("SPEED: ", ft_itoa(box->player.speed));
	mlx_string_put(box->mlx, box->win, 20, 200, 0x00FFFFFF, str);
	free(str);
	str = ft_strjoin("RANGE: ", ft_itoa(box->player.range));
	mlx_string_put(box->mlx, box->win, 20, 240, 0x00FFFFFF, str);
	free(str);
	str = ft_strjoin("FIRE RATE: ", ft_itoa(box->player.fire_rate));
	mlx_string_put(box->mlx, box->win, 20, 280, 0x00FFFFFF, str);
	free(str);
	str = ft_strjoin("SHOT SPEED: ", ft_itoa(box->player.shot_speed));
	mlx_string_put(box->mlx, box->win, 20, 320, 0x00FFFFFF, str);
	free(str);
	str = ft_strjoin("DMG: ", ft_itoa(box->player.dmg));
	mlx_string_put(box->mlx, box->win, 20, 360, 0x00FFFFFF, str);
	free(str);
}

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
	cal_sprite_move(box);
	//print_map_contents(box);
    //fill_buffer_with_color(box->image.addr, SCREENWIDTH, SCREENHEIGHT, 0x00FF0000);

	drawMinimap(box);
	//single_square_test(box);
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
	fps = ft_itoa(1.0 / box->info.frame_time);
	mlx_string_put(box->mlx, box->win, 20, 20, 0x00FFFFFF, fps);
	draw_hud(box);

	free(fps);
}
