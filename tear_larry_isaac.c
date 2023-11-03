/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tear_larry_isaac.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_isaac(t_box *box, t_sprite *sprites)
{
	if (box->info.tex_x < 56 && box->info.tex_x > 20 && box->info.tex_y < 60
		&& box->info.tex_y > 12)
	{
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16 + 32 * ((int)(box->time.tv_usec
								/ 100000.0))) * 4) + box->textures[sprites->data
				->texture].line_len * box->info.tex_y + box
				->textures[sprites->data->texture].line_len * 42]);
		if ((box->info.color & 0x00FFFFFF) != 0)
		{
			hit_mark(box, sprites);
			apply_fog(box, sprites->data->dist);
			my_mlx_pyxel_put(&box->image, box->info.stripe, box->info.part,
				box->info.color);
		}
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data
				->texture].line_len * box->info.tex_y + box->textures[sprites
				->data->texture].line_len * 8]);
	}
	else
		box->info.color = 0;
}

void	process_tear_hit(t_box *box, t_sprite *sprites)
{
	box->info.color = extract_color(&box->textures[sprites->data->texture]
			.addr[((box->info.tex_x + 64 * sprites->data->frame) * 4) + box
			->textures[sprites->data->texture].line_len * box->info.tex_y
			+ box->textures[sprites->data->texture].line_len * 64
			* (sprites->data->frame / 4)]);
}

void	process_tear_travel(t_box *box, t_sprite *sprites)
{
	box->info.color = extract_color(&box->textures[sprites->data->texture]
			.addr[(box->info.tex_x * 4) + box->textures[sprites->data->texture]
			.line_len * box->info.tex_y + box->textures[sprites->data->texture]
			.line_len]);
}

void	process_larry_head(t_box *box, t_sprite *sprites)
{
	if (sprites->data->dist < 5)
		sprites->data->state = AWAKE;
	if (box->info.tex_x < 60 && box->info.tex_x > 20 && box->info.tex_y < 60
		&& box->info.tex_y > 25)
		process_larry_directions(box, sprites, sprites->data->dir_x, sprites
			->data->dir_y);
	else
		box->info.color = 0;
}

void	process_larry_body(t_box *box, t_sprite *sprites)
{
	if (!sprites->data->state && find_seg(box, 0)->data->state == AWAKE)
		sprites->data->state = AWAKE;
	if (box->info.tex_x < 50 && box->info.tex_x > 20 && box->info.tex_y < 60
		&& box->info.tex_y > 30)
	{
		if (sprites->data->seg == sprites->data->n_seg)
			box->info.color = extract_color(&box->textures[LARRY_JR_HEAD]
					.addr[((box->info.tex_x - 20 + 32 * ((int)((box->time
										.tv_usec / 100000.0) * 2) / 10)) * 4)
					+ box->textures[LARRY_JR_HEAD].line_len * box->info.tex_y
					+ box->textures[LARRY_JR_HEAD].line_len * 96]);
		else
			box->info.color = extract_color(&box->textures[LARRY_JR_HEAD]
					.addr[((box->info.tex_x - 20 + 32 - 32 * ((int)((box
										->time.tv_usec / 100000.0) * 2) / 10))
						* 4) + box->textures[LARRY_JR_HEAD].line_len * box
					->info.tex_y + box->textures[LARRY_JR_HEAD].line_len * 64]);
	}
	else
		box->info.color = 0;
}
