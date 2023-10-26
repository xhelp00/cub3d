/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 16:15:23 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:30 by phelebra         ###   ########.fr       */
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
	load_specific_textures(box, 2, "textures/blackhole.xpm");
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

void	init_general_vals(t_box *box)
{
	box->info.ray = malloc(sizeof(t_ray) * SCREENWIDTH + 1);
	box->sprites = NULL;
	box->items = NULL;
	box->n_sprites = 0;
	box->god = 0;
	box->hud = 1;
	box->won = 0;
	box->lost = 0;
	box->input_index = 0;
	ft_memset(box->input_buffer, 0, sizeof(box->input_buffer));
}

void	init_pos_dir_vals(t_box *box)
{
	box->info.pos_x = 4;
	box->info.pos_y = 5;
	box->info.pos_z = 0;
	box->info.dir_x = -1.0;
	box->info.dir_y = 0;
	box->info.start_dir_x = -1.0;
	box->info.start_dir_y = 0;
	box->info.plane_x = 0;
	box->info.plane_y = 0.66;
}

void	init_time_move_vals(t_box *box)
{
	gettimeofday(&box->time, NULL);
	gettimeofday(&box->old_time, NULL);
	box->info.camera_x = 0;
	box->info.ray_dir_x = 0;
	box->info.ray_dir_y = 0;
	box->info.rotate = 0;
	box->info.move_x = 0;
	box->info.move_y = 0;
}

void	init_attr_vals(t_box *box)
{
	box->info.hit = 0;
	box->info.sprint = 0;
	box->info.pitch = 0;
	box->info.up_down = 0;
	box->info.old_dir_x = 0;
	box->info.old_plane_x = 0;
	box->info.door = 0;
}

void	init_misc_vals(t_box *box)
{
	box->info.distance = 0;
	box->info.color = 0;
	box->info.rot_speed = 0;
	box->info.move_speed = 0;
	box->info.zbuffer = malloc(SCREENWIDTH * sizeof(double));
}

void	init_mouse_vals(t_box *box)
{
	box->mouse.xdistance = 0;
	box->mouse.ydistance = 0;
	box->mouse.x = 0;
	box->mouse.y = 0;
}

void	init_player_vals(t_box *box)
{
	box->player.speed = 100;
	box->player.range = 65;
	box->player.fire_rate = 50;
	box->player.shot_speed = 10;
	box->player.dmg = 35;
	box->player.cry = 0;
	box->player.state = 0;
	box->player.hp = 6;
	box->player.max_hp = 6;
	box->player.hit = 0;
	box->player.n_key = 0;
	gettimeofday(&box->player.last_tear, NULL);
}

void	init_vals(t_box *box)
{
	init_general_vals(box);
	init_pos_dir_vals(box);
	init_time_move_vals(box);
	init_attr_vals(box);
	init_misc_vals(box);
	init_mouse_vals(box);
	init_player_vals(box);
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
	box->info.door = 0;
	box->info.door_x = 0;
	box->info.door_y = 0;
	box->info.door_dist_x = 0;
	box->info.door_dist_y = 0;
	box->info.door_side = 0;
}

void	swap(t_sprite *x)
{
	t_sprite_data	*tmp;

	if (!x || (x->data == NULL && x->next == NULL))
		return ;
	tmp = x->data;
	x->data = x->next->data;
	x->next->data = tmp;
}

void	calc_sprite_distances(t_box *box, t_sprite *sprites)
{
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
}

void	inner_bubble_sort(t_sprite *sprites)
{
	t_sprite	*tmp;

	tmp = sprites;
	while (tmp->next)
	{
		if (tmp->data->dist < tmp->next->data->dist)
			swap(tmp);
		tmp = tmp->next;
	}
}

void	outer_bubble_sort(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		inner_bubble_sort(sprites);
		sprites = sprites->next;
	}
}

void	bubble_sort_sprites(t_box *box)
{
	calc_sprite_distances(box, box->sprites);
	outer_bubble_sort(box);
}
