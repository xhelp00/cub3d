/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   baby_nerve_leech.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_baby(t_box *box, t_sprite *sprites)
{
	if (box->info.tex_y < 47 && box->info.tex_y > 15)
	{
		if (sprites->data->dist < 5)
		{
			sprites->data->state = AWAKE;
			box->info.color = extract_color(&box->textures[sprites->data
					->texture].addr[(box->info.tex_x * 4) + box
					->textures[sprites->data->texture].line_len * box->info
					.tex_y + box->textures[sprites->data->texture].line_len
					* 16]);
			if (!sprites->data->sound)
			{
				sprites->data->sound = 1;
				box->p = music(box->env, "sounds/angry.mp3");
			}
		}
		else
			box->info.color = extract_color(&box->textures[sprites->data
					->texture].addr[(box->info.tex_x * 4) + box
					->textures[sprites->data->texture].line_len * box->info
					.tex_y + box->textures[sprites->data->texture].line_len
					* -16]);
	}
	else
		box->info.color = 0;
}

void	process_nerve(t_box *box, t_sprite *sprites)
{
	if (box->info.tex_x < 48 && box->info.tex_x > 15)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x + 16 + 32 * ((int)(box->time.tv_usec
								/ 100000.0) / 2)) * 4) + box->textures[sprites
				->data->texture].line_len * box->info.tex_y]);
	else
		box->info.color = 0;
}

void	process_leech(t_box *box, t_sprite *sprites)
{
	if (sprites->data->dist < 5)
		sprites->data->state = AWAKE;
	if (box->info.tex_x < 48 && box->info.tex_x > 15 && box->info.tex_y < 47
		&& box->info.tex_y > 15)
		process_leech_directions(box, sprites, sprites->data->dir_x, sprites
			->data->dir_y);
	else
		box->info.color = 0;
}
