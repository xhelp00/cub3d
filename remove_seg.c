/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_seg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	remove_seg(t_box *box, t_sprite *to_rem)
{
	t_sprite	*next_head;

	if (to_rem->data->texture == LARRY_JR_BODY || to_rem->data->texture
		== LARRY_JR_HEAD)
	{
		if (to_rem->data->seg == 0)
		{
			next_head = find_next_seg(box, to_rem->data->seg + 1);
			if (next_head)
			{
				next_head->data->texture = LARRY_JR_HEAD;
			}
			decrement_segments(box, -1);
		}
		else
		{
			decrement_segments(box, to_rem->data->seg);
		}
		update_total_segments(box);
	}
}

void	sprite_remove(t_box *box, t_sprite *to_rem)
{
	remove_seg(box, to_rem);
	if (to_rem == box->sprites)
		box->sprites = box->sprites->next;
	else
		to_rem->prev->next = to_rem->next;
	if (to_rem->next)
		to_rem->next->prev = to_rem->prev;
	free(to_rem->data);
	free(to_rem);
}

void	set_player_position(t_box *box, int i, int c)
{
	box->info.pos_x = i;
	box->info.pos_y = c;
}
