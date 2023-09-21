/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/25 17:46:57 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*	Init_textures

	Loads textures into memory
*/
void	init_textures(t_box *box)
{
	int		k;
	int		j;
	int		i;

	box->textures = malloc(50 * sizeof(t_image));
	i = -1;
	while (++i < 50)
		box->textures[i].img = 0;
	box->textures[0].img = mlx_xpm_file_to_image(box->mlx, "textures/wall.xpm", &k, &j);
	box->textures[1].img = mlx_xpm_file_to_image(box->mlx, "textures/floor.xpm", &k, &j);
	box->textures[2].img = mlx_xpm_file_to_image(box->mlx, "textures/wall.xpm", &k, &j);
	box->textures[10].img = mlx_xpm_file_to_image(box->mlx, "textures/baby.xpm", &k, &j);
	box->textures[11].img = mlx_xpm_file_to_image(box->mlx, "textures/nerve_ending.xpm", &k, &j);
	box->textures[12].img = mlx_xpm_file_to_image(box->mlx, "textures/leech.xpm", &k, &j);
	box->textures[20].img = mlx_xpm_file_to_image(box->mlx, "textures/isaac.xpm", &k, &j);
	box->textures[30].img = mlx_xpm_file_to_image(box->mlx, "textures/tear.xpm", &k, &j);
	i = -1;
	while (++i < 50)
	{
		if (!box->textures[i].img)
			box->textures[i].img = mlx_xpm_file_to_image(box->mlx, "textures/grey_bricks.xpm", &k, &j);
		box->textures[i].addr = (unsigned char *)mlx_get_data_addr(box->textures[i].img,
			&box->textures[i].bits_pp, &box->textures[i].line_len, &box->textures[i].endian);
	}
}

/*	Init_vals

	Sets most of the values to 0
*/
void	init_vals(t_box *box)
{
	box->info.pos_x = 4;
	box->info.pos_y = 5;
	box->info.pos_z = 0;
	box->info.dir_x = -1.0;
	box->info.dir_y = 0;
	box->info.plane_x = 0;
	box->info.plane_y = 0.66;
	gettimeofday(&box->time, NULL);
	gettimeofday(&box->old_time, NULL);
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.rotate = 0;
	box->info.move_x = 0;
	box->info.move_y = 0;
	box->info.hit = 0;
	box->info.sprint = 0;
	box->info.pitch = 0;
	box->info.up_down = 0;
	box->info.old_dir_x = 0;
	box->info.old_plane_x = 0;
	box->mouse.xdistance = 0;
	box->mouse.ydistance = 0;
	box->mouse.x = 0;
	box->mouse.y = 0;
	box->info.distance = 0;
	box->info.color = 0;
	box->info.rot_speed = 0;
	box->info.move_speed = 0;
	box->info.zbuffer = malloc(SCREENWIDTH * sizeof(double));
	box->n_sprites = 0;
}

void	reset_vals(t_box *box)
{
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.map_x = 0;
	box->info.map_y = 0;
	box->info.hit = 0;
	box->info.text_num = 0;
	box->info.color = 0;
}

void	swap(t_sprite *x, t_sprite *y)
{
	t_sprite	tmp;

	tmp = *x;
	*x = *y;
	*y = tmp;
}

void	bubble_sort_sprites(t_box *box)
{
	int	i;
	int	j;

	i = -1;
	while (++i < box->n_sprites)
		box->sprites[i].dist = ((box->info.pos_x - box->sprites[i].x)
				* (box->info.pos_x - box->sprites[i].x)
				+ (box->info.pos_y - box->sprites[i].y)
				* (box->info.pos_y - box->sprites[i].y));
	i = -1;
	while (++i < box->n_sprites - 1)
	{
		j = -1;
		while (++j < box->n_sprites - i - 1)
			if (box->sprites[j].dist > box->sprites[j + 1].dist)
				swap(&box->sprites[j], &box->sprites[j + 1]);
	}
	i = -1;
	while (++i < box->n_sprites / 2)
		swap(&box->sprites[i], &box->sprites[box->n_sprites - i - 1]);
}
