/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_larry_jr_head(t_box *box, t_sprite_data *data)
{
	if (data->texture == LARRY_JR_HEAD && data->state == AWAKE)
	{
		enemy_angle(box, data);
		enemy_move(box, data);
	}
}

void	process_larry_jr_body(t_box *box, t_sprite_data *data)
{
	if (data->texture == LARRY_JR_BODY && data->state == AWAKE)
	{
		body_angle(box, data);
		enemy_move(box, data);
	}
}

void	process_leech_or_baby(t_box *box, t_sprite_data *data)
{
	if ((data->texture == LEECH || data->texture == BABY) && data->state
		== AWAKE)
	{
		enemy_angle(box, data);
		enemy_move(box, data);
	}
}

int	determine_sprite_action(t_box *box, t_sprite_data *data, t_sprite *sprites)
{
	if (data->texture < TEAR && data->texture != DOOR)
		return (check_player_hit(box, data));
	else if (data->texture == TEAR)
		return (handle_tear(box, data, sprites));
	else if (data->texture == ITEMS)
		return (handle_item(box, data, sprites));
	else if (data->texture == KEY && data->dist < 0.1 && data->dist != 0)
		return (handle_key(box, sprites));
	else if (data->texture == TROPHY && data->dist < 0.1 && data->dist != 0)
		return (handle_trophy(box, sprites));
	else if (data->texture == DOOR)
		return (handle_door(box, data));
	return (1);
}

void	cal_sprite_move(t_box *box)
{
	t_sprite	*sprites;
	int			continue_loop;

	sprites = box->sprites;
	while (sprites)
	{
		process_larry_jr_head(box, sprites->data);
		process_larry_jr_body(box, sprites->data);
		process_leech_or_baby(box, sprites->data);
		continue_loop = determine_sprite_action(box, sprites->data, sprites);
		if (continue_loop)
			sprites = sprites->next;
		else
			break ;
	}
}
