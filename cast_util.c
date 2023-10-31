/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:04:56 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:12:41 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_and_cast_leech(t_box *box, t_sprite *sprites, double dir_x,
		double dir_y)
{
	if (box->info.dir_x < dir_x && box->info.dir_y > -dir_y && box->info.dir_y
		< dir_y)
		cast_leech(box, sprites, UP);
	else if (box->info.dir_x > -dir_x && box->info.dir_y < dir_y && box->info
		.dir_y > -dir_y)
		cast_leech(box, sprites, DOWN);
	else if (box->info.dir_x > -dir_y && box->info.dir_x < dir_y && box->info
		.dir_y < -dir_x)
		cast_leech(box, sprites, RIGHT);
	else
		cast_leech(box, sprites, LEFT);
}

void	process_leech_directions(t_box *box, t_sprite *sprites,
		double sprite_dir_x, double sprite_dir_y)
{
	if (sprite_dir_x < -0.7 && sprite_dir_y > -0.75 && sprite_dir_y < 0.75)
		check_and_cast_leech(box, sprites, -0.7, 0.75);
	else if (sprite_dir_x > 0.7 && sprite_dir_y > -0.75 && sprite_dir_y < 0.75)
		check_and_cast_leech(box, sprites, 0.7, 0.75);
	else if (sprite_dir_x > -0.75 && sprite_dir_x < 0.75 && sprite_dir_y < -0.7)
		check_and_cast_leech(box, sprites, 0.75, -0.7);
	else
		check_and_cast_leech(box, sprites, 0.75, 0.7);
}

void	check_and_cast_larry(t_box *box, t_sprite *sprites, double dir_x,
		double dir_y)
{
	if (box->info.dir_x < dir_x && box->info.dir_y > -dir_y && box->info.dir_y
		< dir_y)
		cast_larry(box, sprites, UP);
	else if (box->info.dir_x > -dir_x && box->info.dir_y < dir_y && box->info
		.dir_y > -dir_y)
		cast_larry(box, sprites, DOWN);
	else if (box->info.dir_x > -dir_y && box->info.dir_x < dir_y && box->info
		.dir_y < -dir_x)
		cast_larry(box, sprites, RIGHT);
	else
		cast_larry(box, sprites, LEFT);
}

void	process_larry_directions(t_box *box, t_sprite *sprites,
		double sprite_dir_x, double sprite_dir_y)
{
	if (sprite_dir_x < -0.7 && sprite_dir_y > -0.75 && sprite_dir_y < 0.75)
		check_and_cast_larry(box, sprites, -0.7, 0.75);
	else if (sprite_dir_x > 0.7 && sprite_dir_y > -0.75 && sprite_dir_y < 0.75)
		check_and_cast_larry(box, sprites, 0.7, 0.75);
	else if (sprite_dir_x > -0.75 && sprite_dir_x < 0.75 && sprite_dir_y < -0.7)
		check_and_cast_larry(box, sprites, 0.75, -0.7);
	else
		check_and_cast_larry(box, sprites, 0.75, 0.7);
}
