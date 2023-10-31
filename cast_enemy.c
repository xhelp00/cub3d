/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_leech(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == UP || dir == DOWN)
		leech_vertical(box, sprites, dir);
	else
		leech_horizontal(box, sprites, dir);
}

void	cast_larry(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == UP || dir == DOWN)
		larry_vertical(box, sprites, dir);
	else
		larry_horizontal(box, sprites, dir);
}
