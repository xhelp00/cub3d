/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	alloc_textures(t_box *box)
{
	int	i;

	box->textures = malloc(50 * sizeof(t_image));
	i = -1;
	while (++i < 50)
		box->textures[i].img = 0;
}

void	load_specific_textures(t_box *box, int idx, char *path)
{
	int	k;
	int	j;

	box->textures[idx].img = mlx_xpm_file_to_image(box->mlx, path, &k, &j);
}

void	set_texture_defaults(t_box *box)
{
	int	k;
	int	j;
	int	i;

	k = -1;
	j = -1;
	i = -1;
	while (++i < 50)
	{
		if (!box->textures[i].img)
			box->textures[i].img = mlx_xpm_file_to_image(box->mlx,
					"textures/grey_bricks.xpm", &k, &j);
		box->textures[i].addr = (unsigned char *)
			mlx_get_data_addr(box->textures[i].img,
				&box->textures[i].bits_pp, &box->textures[i].line_len,
				&box->textures[i].endian);
	}
}

//load_specific_textures(box, 1, "textures/floor.xpm");
void	init_textures(t_box *box)
{
	alloc_textures(box);
	load_specific_textures(box, 0, "textures/wall.xpm");
	load_specific_textures(box, BLACKHOLE, "textures/blackhole.xpm");
	load_specific_textures(box, 1, "textures/floor.xpm");
	load_specific_textures(box, DOOR, "textures/bars.xpm");
	load_specific_textures(box, BABY, "textures/baby.xpm");
	load_specific_textures(box, NERVE_ENDING, "textures/nerve_ending.xpm");
	load_specific_textures(box, LEECH, "textures/leech.xpm");
	load_specific_textures(box, ISAAC, "textures/isaac.xpm");
	load_specific_textures(box, TEAR, "textures/tear.xpm");
	load_specific_textures(box, LARRY_JR_HEAD, "textures/larry_jr.xpm");
	load_specific_textures(box, UI_PICKUPS, "textures/ui_pickups.xpm");
	load_specific_textures(box, UI_HEARTS, "textures/ui_hearts.xpm");
	load_specific_textures(box, UI_STATS, "textures/ui_stats.xpm");
	load_specific_textures(box, ITEMS, "textures/items.xpm");
	load_specific_textures(box, ITEM_ALTAR, "textures/item_altar.xpm");
	load_specific_textures(box, KEY, "textures/pickup_key.xpm");
	load_specific_textures(box, TROPHY, "textures/trophy.xpm");
	load_specific_textures(box, WIN, "textures/win.xpm");
	load_specific_textures(box, GRIM, "textures/grim.xpm");
	set_texture_defaults(box);
}
