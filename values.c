/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/02 15:00:41 by phelebra         ###   ########.fr       */
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
	box->textures[BABY].img = mlx_xpm_file_to_image(box->mlx, "textures/baby.xpm", &k, &j);
	box->textures[NERVE_ENDING].img = mlx_xpm_file_to_image(box->mlx, "textures/nerve_ending.xpm", &k, &j);
	box->textures[LEECH].img = mlx_xpm_file_to_image(box->mlx, "textures/leech.xpm", &k, &j);
	box->textures[ISAAC].img = mlx_xpm_file_to_image(box->mlx, "textures/isaac.xpm", &k, &j);
	box->textures[TEAR].img = mlx_xpm_file_to_image(box->mlx, "textures/tear.xpm", &k, &j);
	box->textures[LARRY_JR_HEAD].img = mlx_xpm_file_to_image(box->mlx, "textures/larry_jr.xpm", &k, &j);
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
	box->sprites = NULL;
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
	box->player.speed = 100;
	box->player.range = 65;
	box->player.fire_rate = 50;
	box->player.shot_speed = 10;
	box->player.dmg = 35;
	box->player.cry = 0;
	gettimeofday(&box->player.last_tear, NULL);
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

void	swap(t_sprite *x)
{
	t_data	*tmp;

	if (!x || (x->data == NULL && x->next == NULL))
		return ;
	tmp = x->data;
	x->data = x->next->data;
	x->next->data = tmp;
}

void	bubble_sort_sprites(t_box *box)
{
	t_sprite	*sprites;
	t_sprite	*tmp;

	sprites = box->sprites;
	while (sprites)
	{
		sprites->data->dist = ((box->info.pos_x - sprites->data->x)
				* (box->info.pos_x - sprites->data->x)
				+ (box->info.pos_y - sprites->data->y)
				* (box->info.pos_y - sprites->data->y));
		sprites->data->travel = ((sprites->data->start_x - sprites->data->x)
				* (sprites->data->start_x - sprites->data->x)
				+ (sprites->data->start_y - sprites->data->y)
				* (sprites->data->start_y - sprites->data->y));
		sprites = sprites->next;
	}
	sprites = box->sprites;
	while (sprites)
	{
		tmp = sprites;
		while (tmp->next)
		{
			if (tmp->data->dist < tmp->next->data->dist)
				swap(tmp);
			tmp = tmp->next;
		}
		sprites = sprites->next;
	}
}
