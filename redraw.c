/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (box->player.hit)
		fill_screen_red(box);
	mlx_put_image_to_window(box->mlx, box->win, box->image.img, 0, 0);
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
