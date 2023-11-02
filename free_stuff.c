/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_sprites(t_box *box)
{
	t_sprite	*next;

	next = box->sprites;
	if (!next)
		return (0);
	while (next)
	{
		next = box->sprites->next;
		free(box->sprites->data);
		free(box->sprites);
		box->sprites = next;
	}
	return (0);
}

int	free_map(t_box *box)
{
	int	i;

	i = 0;
	while (box->map[i])
		free(box->map[i++]);
	free(box->map);
	return (0);
}

void	free_stuff(t_box *box)
{
	int	i;

	i = -1;
	while (++i < 50)
		mlx_destroy_image(box->mlx, box->textures[i].img);
	free(box->textures);
	free_sprites(box);
	free_map(box);
	mlx_destroy_image(box->mlx, box->image.img);
	mlx_destroy_window(box->mlx, box->win);
	mlx_destroy_display(box->mlx);
	free(box->mlx);
	free(box->info.ray);
	free(box->info.zbuffer);
}
