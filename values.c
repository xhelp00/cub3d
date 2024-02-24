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

/*	Init_textures

	Loads textures into memory
*/
void	init_textures(t_box *box)
{
	int		i;

	box->textures = malloc(100 * sizeof(t_image));
	i = -1;
	while (++i < 100)
		box->textures[i].img = NULL;
	png_file_to_image(box->mlx, &box->textures[WALL], "textures/wall.png");
	png_file_to_image(box->mlx, &box->textures[FLOOR], "textures/floor.png");
	png_file_to_image(box->mlx, &box->textures[BRICKS], "textures/grey_bricks.png");
	png_file_to_image(box->mlx, &box->textures[DOOR], "textures/bars.png");
	// box->textures[0].img = mlx_xpm_file_to_image(box->mlx, "textures/wall.xpm", &k, &j);
	// box->textures[1].img = mlx_xpm_file_to_image(box->mlx, "textures/floor.xpm", &k, &j);
	// box->textures[1].img = mlx_xpm_file_to_image(box->mlx, "textures/blackhole.xpm", &k, &j);
	// box->textures[DOOR].img = mlx_xpm_file_to_image(box->mlx, "textures/bars.xpm", &k, &j);
	png_file_to_image(box->mlx, &box->textures[BABY], "textures/baby.png");
	png_file_to_image(box->mlx, &box->textures[NERVE_ENDING], "textures/nerve_ending.png");
	png_file_to_image(box->mlx, &box->textures[LEECH], "textures/leech.png");
	png_file_to_image(box->mlx, &box->textures[ISAAC], "textures/isaac.png");
	png_file_to_image(box->mlx, &box->textures[TEAR], "textures/tear.png");
	png_file_to_image(box->mlx, &box->textures[LARRY_JR_HEAD], "textures/larry_jr.png");
	// box->textures[BABY].img = mlx_xpm_file_to_image(box->mlx, "textures/baby.xpm", &k, &j);
	// box->textures[NERVE_ENDING].img = mlx_xpm_file_to_image(box->mlx, "textures/nerve_ending.xpm", &k, &j);
	// box->textures[LEECH].img = mlx_xpm_file_to_image(box->mlx, "textures/leech.xpm", &k, &j);
	// box->textures[ISAAC].img = mlx_xpm_file_to_image(box->mlx, "textures/isaac.xpm", &k, &j);
	// box->textures[TEAR].img = mlx_xpm_file_to_image(box->mlx, "textures/tear.xpm", &k, &j);
	// box->textures[LARRY_JR_HEAD].img = mlx_xpm_file_to_image(box->mlx, "textures/larry_jr.xpm", &k, &j);
	// box->textures[UI_PICKUPS].img = mlx_xpm_file_to_image(box->mlx, "textures/ui_pickups.xpm", &k, &j);
	png_file_to_image(box->mlx, &box->textures[UI_PICKUPS], "textures/ui_pickups.png");
	img_resize(box->mlx, &box->textures[UI_PICKUPS], 2);
	split_spritesheet(&box->textures[UI_PICKUPS], 8, 5, 32, 32);
	// box->textures[UI_HEARTS].img = mlx_xpm_file_to_image(box->mlx, "textures/ui_hearts.xpm", &k, &j);
	png_file_to_image(box->mlx, &box->textures[UI_HEARTS], "textures/ui_hearts.png");
	img_resize(box->mlx, &box->textures[UI_HEARTS], 2);
	split_spritesheet(&box->textures[UI_HEARTS], 7, 4, 32, 32);
	// box->textures[UI_STATS].img = mlx_xpm_file_to_image(box->mlx, "textures/ui_stats.xpm", &k, &j);
	png_file_to_image(box->mlx, &box->textures[UI_STATS], "textures/ui_stats.png");
	img_resize(box->mlx, &box->textures[UI_STATS], 2);
	split_spritesheet(&box->textures[UI_STATS], 4, 4, 32, 32);
	// box->textures[ITEMS].img = mlx_xpm_file_to_image(box->mlx, "textures/items.xpm", &k, &j);
	png_file_to_image(box->mlx, &box->textures[ITEMS], "textures/items.png");
	split_spritesheet(&box->textures[ITEMS], 20, 28, 32, 32);
	png_file_to_image(box->mlx, &box->textures[ITEM_ALTAR], "textures/item_altar.png");
	png_file_to_image(box->mlx, &box->textures[KEY], "textures/pickup_key.png");
	png_file_to_image(box->mlx, &box->textures[TROPHY], "textures/trophy.png");
	// box->textures[ITEM_ALTAR].img = mlx_xpm_file_to_image(box->mlx, "textures/item_altar.xpm", &k, &j);
	// box->textures[KEY].img = mlx_xpm_file_to_image(box->mlx, "textures/pickup_key.xpm", &k, &j);
	// box->textures[TROPHY].img = mlx_xpm_file_to_image(box->mlx, "textures/trophy.xpm", &k, &j);

	// box->textures[WIN].img = mlx_xpm_file_to_image(box->mlx, "textures/win.xpm", &k, &j);
	// box->textures[GRIM].img = mlx_xpm_file_to_image(box->mlx, "textures/grim.xpm", &k, &j);
	png_file_to_image(box->mlx, &box->textures[WIN], "textures/win.png");
	img_resize(box->mlx, &box->textures[WIN], 4);

	png_file_to_image(box->mlx, &box->textures[GRIM], "textures/deathnote.png");
	img_resize(box->mlx, &box->textures[GRIM], 2);

	png_file_to_image(box->mlx, &box->textures[PAUSE_MENU], "textures/pausescreen.png");
	img_resize(box->mlx, &box->textures[PAUSE_MENU], 2);

	png_file_to_image(box->mlx, &box->textures[TITLE_MENU], "textures/titlemenu.png");
	img_resize(box->mlx, &box->textures[TITLE_MENU], 2.7);

	png_file_to_image(box->mlx, &box->textures[START_MENU], "textures/gamemenu.png");
	img_resize(box->mlx, &box->textures[START_MENU], 2.7);

	png_file_to_image(box->mlx, &box->textures[MENU_BACK], "textures/emptyscreen.png");
	img_resize(box->mlx, &box->textures[MENU_BACK], 2.7);

	png_file_to_image(box->mlx, &box->textures[OPTIONS_MENU], "textures/optionsmenu.png");
	img_resize(box->mlx, &box->textures[OPTIONS_MENU], 2);

	png_file_to_image(box->mlx, &box->textures[OPTIONS_MENU_DARK], "textures/optionsmenudark.png");
	img_resize(box->mlx, &box->textures[OPTIONS_MENU_DARK], 2);
	i = -1;
	while (++i < 100)
		if (box->textures[i].img == NULL){
			png_file_to_image(box->mlx, &box->textures[i], "textures/missing.png");
			img_resize(box->mlx, &box->textures[i], 0.5);
		}
		// box->textures[i].addr = (unsigned char *)mlx_get_data_addr(box->textures[i].img,
			// &box->textures[i].bits_pp, &box->textures[i].line_len, &box->textures[i].endian);
	box->title_menu = 1;
	box->pause_menu = 0;
	box->pause_menu_choice = 0;
	box->start_menu = 0;
	box->start_menu_choice = 0;
	box->options_menu = 0;
	box->options_menu_choice = 0;
	box->mouse_hidden = 0;
	box->sound.music_volume = 0.5;
	box->sound.sfx_volume = 0.5;
}

void	init_sounds(t_box *box)
{
	int	i;

	i = -1;
	while (++i < 50)
		box->sound.playing[i].play = NULL;
	box->sound.ctx = cs_make_context(0, 44100, 4096, 24, "cub3d");
	cs_spawn_mix_thread(box->sound.ctx);
	cs_thread_sleep_delay(box->sound.ctx, 10);
	load_audio_file(&box->sound.music, "sounds/Isaac.wav");
	load_audio_file(&box->sound.sfx[ANGRY], "sounds/angry.wav");
	load_audio_file(&box->sound.sfx[DIE], "sounds/die.wav");
	load_audio_file(&box->sound.sfx[DOOR], "sounds/door.wav");
	load_audio_file(&box->sound.sfx[FAIL], "sounds/fail.wav");
	load_audio_file(&box->sound.sfx[FANFARE], "sounds/fanfare.wav");
	load_audio_file(&box->sound.sfx[KEY_PICKUP], "sounds/key.wav");
	load_audio_file(&box->sound.sfx[OW], "sounds/ow.wav");
	load_audio_file(&box->sound.sfx[PAIN], "sounds/pain.wav");
	load_audio_file(&box->sound.sfx[SHOT], "sounds/shot.wav");
	load_audio_file(&box->sound.sfx[SPLASH], "sounds/splash.wav");

	box->sound.playing[0].play = cs_play_sound(box->sound.ctx, box->sound.music.def);
	cs_loop_sound(box->sound.playing[0].play, 1);
	cs_set_volume(box->sound.playing[0].play, box->sound.music_volume, box->sound.music_volume);
}

/*	Init_vals

	Sets most of the values to 0
*/
void	init_vals(t_box *box)
{
	box->info.ray = malloc(sizeof(t_ray) * SCREENWIDTH + 1);
	box->sprites = NULL;
	box->items = NULL;
	box->info.pos_x = 4;
	box->info.pos_y = 5;
	box->info.pos_z = 0;
	box->info.dir_x = -1.0;
	box->info.dir_y = 0;
	box->info.start_dir_x = -1.0;
	box->info.start_dir_y = 0;
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
	box->info.door = 0;
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
	box->player.state = 0;
	box->player.hp = 6;
	box->player.max_hp = 6;
	box->player.hit = 0;
	box->player.n_key = 0;
	box->god = 0;
	box->hud = 1;
	box->won = 0;
	box->lost = 0;
	gettimeofday(&box->player.last_tear, NULL);
	box->input_index = 0;
	ft_memset(box->input_buffer, 0, sizeof(box->input_buffer));
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
	//box->info.ray = malloc(sizeof(t_ray) * SCREENWIDTH + 1);
}

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
	while (++i < 100)
		mlx_destroy_image(box->mlx, box->textures[i].img);
	i = -1;
	while (++i < 10)
		cs_free_sound(&box->sound.sfx[i].loaded);
	cs_free_sound(&box->sound.music.loaded);
	cs_shutdown_context(box->sound.ctx);
	// pthread_join(box->sound.ctx->thread, NULL);
	free(box->textures);
	if (box->sprites)
	{
		free_sprites(box);
		free_map(box);
	}
	mlx_destroy_image(box->mlx, box->image.img);
	// mlx_destroy_window(box->mlx, box->win);
	mlx_destroy_display(box->mlx);
	free(box->mlx);
	free(box->info.ray);
	free(box->info.zbuffer);
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
