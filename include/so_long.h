/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 09:18:14 by phelebra          #+#    #+#             */
/*   Updated: 2023/08/23 14:08:57 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <stddef.h>
# include <stdbool.h>
# include <fcntl.h>
# define TILE 32

typedef struct s_position
{
	int		x;
	int		y;
}			t_position;

typedef struct s_collectible
{
/* 	int				offset_x;
	int				offset_y; */
	int				c_x;
	int				c_y;
	xpm_t			*collectible_t;
	mlx_image_t		*collectible_img;
	mlx_image_t		*idle;
}					t_collectible;

typedef struct s_idle_t
{
	xpm_t			*idle_texture[8];
	mlx_image_t		*idle_img[8];
	mlx_image_t		*idle;
}					t_idle;

typedef struct s_texture
{
	xpm_t			*wall;
	xpm_t			*floor;
	xpm_t			*exit[2];
	xpm_t			*enemy[4];
	mlx_image_t		*exit_img[2];
	mlx_image_t		*floor_img;
	mlx_image_t		*wall_img;
	mlx_image_t		*enemy_img[4];

}					t_texture;

typedef struct s_map
{
	int				w;
	int				h;
	char			**grid;
	char			*allowed_symbols;
	int				count_steps;
	int				count_collect;
	int				count_exit;
	int				count_player;
}					t_map;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*counter_img;
	mlx_texture_t	*player;
	mlx_image_t		*player_img;
	t_idle			*idle_p;
	t_idle			*idle_e;
	char			*counter;
	void			*game_ptr;
	char			*map_arg;
	char			**grid;
	int				w;
	int				h;
	t_map			map;
	t_texture		*tiles;
	t_position		*movement[5];
	int				i;
	int				frames;
	t_collectible	*collectible;
	int				col;
	int				collected;
	int				open;
}					t_game;

typedef struct s_flood
{
	char		**map;
	int			cols;
	int			rows;
	int			count_collect;
	int			p_x;
	int			p_y;
	bool		exit_found;
}				t_flood;

void		check_arguments(int ac, char **av, t_game *game);
t_map		get_map(char *map, t_game *game);
void		whatsup(int i);
void		check_grid_symbols(t_map *game);
void		check_path(t_game *g, char *input_file);
void		free_flood(t_flood *flood);
void		load_game(t_game *g);
void		init_idle_texture(t_game *game);
//void		hook(mlx_key_data_t key, void *param);
void		idle_animation_p(void *param);
void		init_tile_textures(t_game *game);
void		draw_tiles(t_game *game);
t_position	*get_component(char **map, char type);
void		put_door(t_game *game);
void		put_floor(t_game *game, char c, int width, int height);
void		put_enemy(t_game *game);
int			is_valid_move(t_game *game, t_position *movement);
void		init_movements(t_game *game);
void		function_move(t_game *game, t_position *position);
void		add_player(t_game *game);
void		draw_collectibles(t_game *game);
void		load_collectibles(t_game *game);
void		put_collectible(t_game *game, char c, int x, int y);
void		get_collectible_count(t_game *game);
void		player_is_on_colectible(t_game *game);
void		collect(t_game *game, int posx, int posy);
void		win(t_game *game);
void		free_chars(char **grid, char **line);
void		player_is_on_enemy(t_game *game);
void		loose(t_game *game);
void		delete_tile_textures(t_game *game);
void		load_idle_images2(t_game *game);
void		load_idle_images1(t_game *game);
void		add_player(t_game *game);

#endif