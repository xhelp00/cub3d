/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_texture_next(t_box *box, t_sprite *sprites)
{
	if (sprites->data->texture == NERVE_ENDING)
		process_nerve(box, sprites);
	else if (sprites->data->texture == TEAR && sprites->data->hit)
		process_tear_hit(box, sprites);
	else if (sprites->data->texture == TEAR && !sprites->data->hit
		&& sprites->data->travel * 10 > 1)
		process_tear_travel(box, sprites);
	else if (sprites->data->texture == LARRY_JR_HEAD)
		process_larry_head(box, sprites);
	else if (sprites->data->texture == LARRY_JR_BODY)
		process_larry_body(box, sprites);
	else if (sprites->data->texture == ITEMS)
		process_items(box, sprites);
	else if (sprites->data->texture == TROPHY)
		process_trophy(box, sprites);
	else if (sprites->data->texture == KEY)
		process_key(box, sprites);
	else if (sprites->data->texture == ITEM_ALTAR)
		process_altar(box, sprites);
	else
		box->info.color = 0;
}

void	process_texture(t_box *box, t_sprite *sprites)
{
	if (box->info.transform_y > 0 && box->info.transform_y < box->info
		.zbuffer[box->info.stripe])
	{
		box->info.part = box->info.draw_start_y;
		while (box->info.part < box->info.draw_end_y)
		{
			box->info.d = (box->info.part - box->info.v_move_screen) * 256
				- SCREENHEIGHT * 128 + box->info.sprite_height * 128;
			box->info.tex_y = ((box->info.d * TEXTUREHEIGHT) / box->info
					.sprite_height) / 256;
			if (sprites->data->texture == BABY)
				process_baby(box, sprites);
			else if (sprites->data->texture == LEECH)
				process_leech(box, sprites);
			else if (sprites->data->texture == ISAAC)
				process_isaac(box, sprites);
			else
				process_texture_next(box, sprites);
			process_other(box, sprites);
			box->info.part++;
		}
	}
}

void	process_stripe(t_box *box, t_sprite *sprites)
{
	while (box->info.stripe < box->info.draw_end_x)
	{
		box->info.tex_x = (int)(256 * (box->info.stripe -(-box->info
						.sprite_width / 2 + box->info.sprite_screen_x))
				* TEXTUREWIDTH / box->info.sprite_width) / 256;
		box->info.flipped = 0;
		process_texture(box, sprites);
		box->info.stripe++;
	}
}

void	process_sprite(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		init_stripe(box, sprites);
		process_stripe(box, sprites);
		sprites = sprites->next;
	}
}

void	cast_obj(t_box *box)
{
	bubble_sort_sprites(box);
	process_sprite(box);
}
