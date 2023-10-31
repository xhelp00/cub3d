/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_item.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_items(t_box *box, t_sprite *sprites)
{
	sprites->data->frame = ((int)((box->time.tv_usec / 100000.0) * 4) / 5);
	if (sprites->data->frame > 4)
		sprites->data->frame = 8 - sprites->data->frame;
	if (box->info.tex_x < 48 && box->info.tex_x > 16 && box->info.tex_y < 48
		- 1 * sprites->data->frame && box->info.tex_y > 16 - 1
		* sprites->data->frame)
		box->info.color = extract_color(&box->textures[ITEMS].addr[((box
						->info.tex_x - 16 + ((sprites->data->id % 20) * 32))
					* 4) + box->textures[ITEMS].line_len * box->info.tex_y + box
				->textures[ITEMS].line_len * ((-16 + sprites->data->frame)
					+ (sprites->data->id / 20) * 32)]);
	else
		box->info.color = 0;
}

void	process_trophy(t_box *box, t_sprite *sprites)
{
	if (box->info.tex_x < 48 && box->info.tex_x > 16 && box->info.tex_y < 64
		&& box->info.tex_y > 8)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data
				->texture].line_len * box->info.tex_y + box->textures[sprites
				->data->texture].line_len * -8]);
	else
		box->info.color = 0;
}

void	process_key(t_box *box, t_sprite *sprites)
{
	if (box->info.tex_x < 32 && box->info.tex_x > 16 && box->info.tex_y < 64
		&& box->info.tex_y > 32)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data
				->texture].line_len * box->info.tex_y + box->textures[sprites
				->data->texture].line_len * -32]);
	else
		box->info.color = 0;
}

void	process_altar(t_box *box, t_sprite *sprites)
{
	if (box->info.tex_x < 48 && box->info.tex_x > 16 && box->info.tex_y < 64
		&& box->info.tex_y > 40)
		box->info.color = extract_color(&box->textures[sprites->data->texture]
				.addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data
				->texture].line_len * box->info.tex_y + box->textures[sprites
				->data->texture].line_len * -40]);
	else
		box->info.color = 0;
}

void	process_other(t_box *box, t_sprite *sprites)
{
	if ((box->info.color & 0x00FFFFFF) != 0)
	{
		hit_mark(box, sprites);
		apply_fog(box, sprites->data->dist);
		my_mlx_pyxel_put(&box->image, box->info.stripe, box->info.part,
			box->info.color);
	}
}
