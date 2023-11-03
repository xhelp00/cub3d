/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extract_color(unsigned char *pixel)
{
	return (pixel[3] << 24 | pixel[2] << 16 | pixel[1] << 8 | pixel[0]);
}

void	my_mlx_pyxel_put(t_image *image, int x, int y, int color)
{
	unsigned char	*pixel;

	pixel = image->addr + (y * image->line_len + x
			* (image->bits_pp / 8));
	*(unsigned int *)pixel = color;
}

unsigned int	extract_heart_color(t_box *box, int x, int y, int i)
{
	int	xoffset;
	int	index;

	xoffset = 0;
	if (i < (box->player.hp / 2))
		xoffset = x - 50;
	else if (box->player.hp % 2 == 1 && i == (box->player.hp / 2))
		xoffset = x - 34;
	else
		xoffset = x - 18;
	index = (xoffset - ((x + (i * 32) - 50) / 2)) * 4
		+ box->textures[UI_HEARTS].line_len * (y - 15 - ((y - 15) / 2));
	return (extract_color(&box->textures[UI_HEARTS].addr[index]));
}
