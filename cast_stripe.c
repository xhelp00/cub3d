/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_stripe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calculate_stripe_start(t_box *box, t_sprite *sprites)
{
	box->info.dx = sprites->data->x - box->info.pos_x;
	box->info.dy = sprites->data->y - box->info.pos_y;
	box->info.t_angle = atan2(box->info.dy, box->info.dx);
	box->info.stripe = box->info.draw_start_x;
}

void	init_stripe(t_box *box, t_sprite *sprites)
{
	init_sprite_position(box, sprites);
	calculate_transformations(box);
	calculate_screen_coordinates(box);
	set_draw_limits(box);
	calculate_stripe_start(box, sprites);
}
