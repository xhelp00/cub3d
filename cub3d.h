/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:51:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/11 16:39:21 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <dirent.h>
# include <pthread.h>
# include "Libft/libft.h"
# include "minilibx/mlx.h"
# include <signal.h>
# include <sys/wait.h>


# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TEXTUREWIDTH 64
# define TEXTUREHEIGHT 64
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define MINIMAP_OFFSET 10

typedef struct s_ray
{
	int		end_x;
	int		end_y;
}				t_ray;

typedef struct s_info
{
	int		angry; //if close to BABY
	int 	sound; //tracking if played sound
	int		move_y;
	int		move_x;
	int		rotate;
	int		sprint;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_y;
	int		map_x;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	prep_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		color;
	int		draw;
	double	frame_time;
	double	move_speed;
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;
	int		text_num;
	double	wall_x;
	int		text_x;
	int		text_y;
	double	step;
	double	tex_pos;
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	int		p;
	double	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		floor_texture;
	int		ceiling_texture;
	double	*zbuffer;
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	int		tex_x;
	int		d;
	int		tex_y;
	int		stripe;
	int		part;
	int		v_move_screen;
	double	dx;
	double	dy;
	double	t_angle;
	int		text_n;
	double	pitch;
	int		is_floor;
	float	cam_z;
	int		up_down;
	int		distance;
	t_ray		*ray;
	int		to_destroy;
}				t_info;

typedef struct s_image
{
	void			*img;
	unsigned char	*addr;
	int				bits_pp;
	int				line_len;
	int				endian;
	char			*name;
}				t_image;

# define IDLE 0
# define HIT 1

typedef struct s_data
{
	double			x;
	double			y;
	double			start_x;
	double			start_y;
	double			travel;
	int				texture;
	double			dist;
	double			dir_x;
	double			dir_y;
	int				state;
	int				frame;
	int				hp;
	int				n_segments;
	int				seg;
	struct timeval	hit_time;
}				t_data;

//Texture numbers
# define BABY 10
# define NERVE_ENDING 11
# define LEECH 12
# define ISAAC 20
# define TEAR 30
# define LARRY_JR_HEAD 40
# define LARRY_JR_BODY 41

typedef struct s_sprite
{
	t_data			*data;
	struct s_sprite	*prev;
	struct s_sprite	*next;
}				t_sprite;

typedef struct s_player
{
	int				speed;
	int				range;
	int				fire_rate;
	int				shot_speed;
	int				dmg;
	int				cry;
	struct timeval	last_tear;
}				t_player;

typedef struct s_mouse
{
	int		x;
	int		y;
	double	xdistance;
	double	ydistance;
}				t_mouse;

typedef struct s_box
{
	int				pid;
	int				p;
	char 			**env;
	void			*mlx;
	void			*win;
	t_image			image;
	t_image			*textures;
	t_sprite		*sprites;
	t_player		player;
	int				n_sprites;
	char			**map;
	int				map_width;
	int				map_height;
	t_info			info;
	struct timeval	time;
	struct timeval	old_time;
	t_mouse			mouse;
}				t_box;

//shape rect used for drawing minimap
typedef struct	s_rect
{
	int			x;
	int			y;
	double		width;
	double		height;
	int			fill_color;
	int			border_color;
	int			border_width;
}				t_rect;

//shape line
typedef struct	s_line
{
	int			begin_x;
	int			begin_y;
	int			end_x;
	int			end_y;
	int			color;
	int			width;
}				t_line;

//Hook.c
int		exit_hook(t_box *box);
int		key_press(int key, t_box *box);
int		key_release(int key, t_box *box);
int		mouse_press(int keycode, int x, int y, t_box *box);
int		mouse_release(int keycode, int x, int y, t_box *box);

//Parser.c
void	parser(t_box *box, int fd);
void	sprite_append(t_box *box, float x, float y, int texture);
void	sprite_remove(t_box *box, t_sprite *to_rem);

//Values.c
void	init_vals(t_box *box);
void	init_textures(t_box *box);
void	reset_vals(t_box *box);
void	bubble_sort_sprites(t_box *box);

//Draw_image.c
void	redraw(t_box *box);
int		extract_color(unsigned char *pixel);
void	my_mlx_pyxel_put(t_image *image, int x, int y, int color);
void	apply_fog(t_box *box, double dist);
void	hit_mark(t_box *box, t_sprite *sprite);

//Casting.c
void	cast_floor(t_box *box);
void	cast_wall(t_box *box);
void	cast_obj(t_box *box);

//Minimap.c
void	drawMinimap(t_box *box);
void	draw_map(t_box *box);
int		get_fill_color(char grid_item);
void	draw_player(t_box *box);
void	draw_rays(t_box *box);

//Graphics.c
void	draw_rect(t_rect *rect, t_box *box);
void	draw_line(t_line *line, t_box *box);

//Sound.c
int		music(char **env, char *track);

//testing
void	print_map_contents(t_box *box);
void	fill_buffer_with_color(unsigned char *buffer, int width,
			int height, int color);
void	single_square_test(t_box *box);

//Movement.c
void	cal_move(t_box *box);
void	cal_sprite_move(t_box *box);

//Main.c
int		count_sprites(t_box *box);

#endif
