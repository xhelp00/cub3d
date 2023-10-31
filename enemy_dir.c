/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_dir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	leech_vertical(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == UP)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec
									/ 100000.0) * 6) / 10)) * 4) + box
				->textures[sprites->data->texture].line_len * box->info.tex_y
				+ box->textures[sprites->data->texture].line_len * 16]);
	else if (dir == DOWN)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec
									/ 100000.0) * 6) / 10)) * 4) + box
				->textures[sprites->data->texture].line_len * box->info.tex_y
				+ box->textures[sprites->data->texture].line_len * 48]);
}

void	leech_horizontal(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == LEFT && !box->info.flipped)
	{
		box->info.tex_x = 46 - (box->info.tex_x - 16);
		box->info.flipped = 1;
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec
									/ 100000.0) * 6) / 10)) * 4)
				+ box->textures[sprites->data->texture].line_len * box->info
				.tex_y + box->textures[sprites->data->texture].line_len * -16]);
	}
	else
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec
									/ 100000.0) * 6) / 10)) * 4) + box
				->textures[sprites->data->texture].line_len * box->info.tex_y
				+ box->textures[sprites->data->texture].line_len * -16]);
}

void	larry_vertical(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == UP)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x + 32 + 48) * 4) + box->textures[sprites
				->data->texture].line_len * box->info.tex_y + box
				->textures[sprites->data->texture].line_len * (-20 + 48
					* ((int)((box->time.tv_usec / 100000.0) * 2) / 10))]);
	else if (dir == DOWN)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16 + 48 - 48 * ((int)((box->time
									.tv_usec / 100000.0) * 2) / 10)) * 4) + box
				->textures[sprites->data->texture].line_len * box->info.tex_y
				+ box->textures[sprites->data->texture].line_len * 28]);
}

void	larry_horizontal(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == LEFT && !box->info.flipped)
	{
		box->info.tex_x = 62 - (box->info.tex_x - 16);
		box->info.flipped = 1;
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16 + 48 - 48 * ((int)((box->time
									.tv_usec / 100000.0) * 2) / 10)) * 4) + box
				->textures[sprites->data->texture].line_len * box->info.tex_y
				+ box->textures[sprites->data->texture].line_len * -20]);
	}
	else
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16 + 48 - 48 * ((int)((box->time
									.tv_usec / 100000.0) * 2) / 10)) * 4) + box
				->textures[sprites->data->texture].line_len * box->info.tex_y
				+ box->textures[sprites->data->texture].line_len * -20]);
}
