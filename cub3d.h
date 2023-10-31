/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:51:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:04:47 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
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

# define MOUSE_CONTROL 1
# define SCREENWIDTH 1280
# define SCREENHEIGHT 720
# define TEXTUREWIDTH 64
# define TEXTUREHEIGHT 64
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define MINIMAP_OFFSET 10
# define PI 3.14159265358979323846

typedef struct s_ray
{
	int		end_x;
	int		end_y;
}				t_ray;

typedef struct s_point
{
	float	x;
	float	y;
}				t_point;

typedef struct s_info
{
	int		move_y;
	int		move_x;
	int		rotate;
	int		sprint;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	start_dir_x;
	double	start_dir_y;
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
	double	ene_move_speed;
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
	double	now_angle;
	int		text_n;
	double	pitch;
	int		is_floor;
	float	cam_z;
	int		up_down;
	int		distance;
	t_ray	*ray;
	int		to_destroy;
	int		flipped;
	int		door;
	int		door_x;
	int		door_y;
	double	door_dist_x;
	double	door_dist_y;
	int		door_side;
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
# define AWAKE 1

# define CLOSE 0
# define OPEN 1

# define UP 0
# define DOWN 1
# define LEFT 2
# define RIGHT 3

typedef struct s_sprite_data
{
	double			x;
	double			y;
	double			start_x;
	double			start_y;
	double			travel;
	int				id;
	int				texture;
	double			dist;
	double			dir_x;
	double			dir_y;
	int				state;
	int				frame;
	int				hp;
	int				n_seg;
	int				start_n_seg;
	int				seg;
	int				hit;
	struct timeval	hit_time;
	int				opening;
	struct timeval	action_time;
	int				sound;
}				t_sprite_data;

//Texture numbers
# define DOOR 2
# define BLACKHOLE 3
# define BABY 10
# define NERVE_ENDING 11
# define LEECH 12
# define ISAAC 20
# define LARRY_JR_HEAD 30
# define LARRY_JR_BODY 31
# define TEAR 40
# define KEY 43
# define UI_PICKUPS 44
# define UI_HEARTS 45
# define UI_STATS 46
# define ITEMS 47
# define ITEM_ALTAR 48
# define TROPHY 49
# define WIN 42
# define GRIM 39

typedef struct s_sprite
{
	t_sprite_data		*data;
	struct s_sprite		*prev;
	struct s_sprite		*next;
}				t_sprite;

typedef struct s_item_data
{
	int				id;
	int				texture;
}				t_item_data;

typedef struct s_item
{
	t_item_data			*data;
	struct s_item		*prev;
	struct s_item		*next;
}				t_item;

typedef struct s_player
{
	int				hp;
	int				max_hp;
	int				n_key;
	int				speed;
	int				range;
	int				fire_rate;
	int				shot_speed;
	int				dmg;
	int				cry;
	int				state;
	int				frame;
	int				hit;
	struct timeval	last_tear;
	struct timeval	hit_time;
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
	int				music;
	char			*map_filename;
	int				pid;
	int				p;
	char			**env;
	void			*mlx;
	void			*win;
	t_image			image;
	t_image			*textures;
	t_sprite		*sprites;
	t_item			*items;
	t_player		player;
	int				n_sprites;
	char			**map;
	int				map_width;
	int				map_height;
	t_info			info;
	struct timeval	time;
	struct timeval	old_time;
	t_mouse			mouse;
	char			input_buffer[6];
	int				input_index;
	int				god;
	int				hud;
	int				lost;
	int				won;
	struct timeval	fin_time;
	int				exit_menu;
}				t_box;

//shape rect used for drawing minimap
typedef struct s_rect
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
typedef struct s_line
{
	int			begin_x;
	int			begin_y;
	int			end_x;
	int			end_y;
	int			color;
	int			width;
}				t_line;

//cast_init
void			setup_floor_and_ceiling(t_box *box, int y);
void			calculate_ray_directions(t_box *box);
void			compute_perspective_values(t_box *box, int y);
void			compute_row_and_step_values(t_box *box);
void			compute_floor_values(t_box *box);
//cast_floor
void			initialize_floor_positions(t_box *box);
void			initialize_floor_casting(t_box *box, int y);
void			handle_floor_casting(t_box *box, int x, int y);
void			calculate_drawing_bounds(t_box *box);
void			cast_floor(t_box *box);
//cast_door
void			find_door_and_wall_dist(t_box *box);
void			determine_texture_properties(t_box *box);
void			loop_draw_door(t_box *box, t_sprite *door, int x);
void			draw_the_door(t_box *box, int x);
void			draw_door(t_box *box, int x);
//dda
void			init_rays(t_box *box, int x);
void			init_side_distances(t_box *box);
void			handle_wall_and_door_collisions(t_box *box);
void			do_dda(t_box *box);
void			perform_dda(t_box *box);
//cast_wall
void			compute_wall_values2(t_box *box);
void			compute_wall_values(t_box *box);
void			draw_wall_column(t_box *box, int x);
void			cast_wall(t_box *box);
//enemy_dir
void			leech_vertical(t_box *box, t_sprite *sprites, int dir);
void			leech_horizontal(t_box *box, t_sprite *sprites, int dir);
void			larry_vertical(t_box *box, t_sprite *sprites, int dir);
void			larry_horizontal(t_box *box, t_sprite *sprites, int dir);
//cast_enemy
void			cast_leech(t_box *box, t_sprite *sprites, int dir);
void			cast_larry(t_box *box, t_sprite *sprites, int dir);
//cast_sprite
void			init_sprite_position(t_box *box, t_sprite *sprites);
void			calculate_transformations(t_box *box);
void			calculate_screen_coordinates(t_box *box);
void			set_draw_limits(t_box *box);
//cast_stripe
void			calculate_stripe_start(t_box *box, t_sprite *sprites);
void			init_stripe(t_box *box, t_sprite *sprites);
//baby_nerve_leech
void			process_baby(t_box *box, t_sprite *sprites);
void			process_nerve(t_box *box, t_sprite *sprites);
void			process_leech(t_box *box, t_sprite *sprites);
//tear_larry_isaac
void			process_isaac(t_box *box, t_sprite *sprites);
void			process_tear_hit(t_box *box, t_sprite *sprites);
void			process_tear_travel(t_box *box, t_sprite *sprites);
void			process_larry_head(t_box *box, t_sprite *sprites);
void			process_larry_body(t_box *box, t_sprite *sprites);
//cast_item
void			process_items(t_box *box, t_sprite *sprites);
void			process_trophy(t_box *box, t_sprite *sprites);
void			process_key(t_box *box, t_sprite *sprites);
void			process_altar(t_box *box, t_sprite *sprites);
void			process_other(t_box *box, t_sprite *sprites);
//cast_obj
void			process_texture_next(t_box *box, t_sprite *sprites);
void			process_texture(t_box *box, t_sprite *sprites);
void			process_stripe(t_box *box, t_sprite *sprites);
void			process_sprite(t_box *box);
void			cast_obj(t_box *box);
//cast_util
void			check_and_cast_leech(t_box *box, t_sprite *sprites,
					double dir_x, double dir_y);
void			process_leech_directions(t_box *box, t_sprite *sprites,
					double sprite_dir_x, double sprite_dir_y);
void			check_and_cast_larry(t_box *box, t_sprite *sprites,
					double dir_x, double dir_y);
void			process_larry_directions(t_box *box, t_sprite *sprites,
					double sprite_dir_x, double sprite_dir_y);
//draw_image
unsigned int	blend_red_with_current_color(unsigned int current_color,
					unsigned char alpha, unsigned char red_value);
void			process_row_for_red_blending(t_box *box, int y);
void			fill_screen_red(t_box *box);
void			apply_fog(t_box *box, double dist);
void			hit_mark(t_box *box, t_sprite *sprite);
//extract_color
int				extract_color(unsigned char *pixel);
void			my_mlx_pyxel_put(t_image *image, int x, int y, int color);
unsigned int	extract_heart_color(t_box *box, int x, int y, int i);
//hud
void			draw_stats_on_hud(t_box *box, int x, int y);
void			draw_pickups_on_hud(t_box *box, int x, int y);
void			draw_hearts_on_hud(t_box *box, int x, int y);
void			draw_items_on_hud(t_box *box, int x, int y);
void			draw_hud(t_box *box);
//redraw
void			init_redraw(t_box *box);
void			handle_game_state(t_box *box);
void			display_and_free_stat(t_box *box, int value, int x, int y);
void			update_hud(t_box *box);
void			redraw(t_box *box);
//graphics
void			draw_rect(t_rect *rect, t_box *box);
void			draw_line(t_line *line, t_box *box);
//hook_handle 
void			handle_rotate(int key, t_box *box);
void			handle_move(int key, t_box *box);
void			handle_position_adjustment(int key, t_box *box);
void			toggle_hud(int key, t_box *box);
void			handle_input_buffer(int key, t_box *box);
//keyhook
int				mouse_press(int keycode, int x, int y, t_box *box);
int				mouse_release(int keycode, int x, int y, t_box *box);
int				key_press(int key, t_box *box);
int				key_release(int key, t_box *box);
int				exit_hook(t_box *box);
//items_n
t_item			*new_item(void);
//items_a
t_item			*last_item(t_item *i);
void			item_add_back(t_box *box, t_item *new);
t_item			*find_item(t_box *box, int id);
void			item_append(t_box *box, t_sprite *sprite);
void			item_remove(t_box *box, t_item *to_rem);
//map_file
void			set_map_filename(int choice, t_box *box);
void			initialize_and_read_map(t_box *box, int fd, char **line);
void			check3(t_box *box, char **argv);
void			check_around(t_box *box, char **map);

//menu
void			handle_other_choices(int choice, t_box *box);
void			process_choice(int choice, t_box *box);
void			print_menu(void);
void			get_user_input(t_box *box);
void			menu(t_box *box);
//main
int				count_sprites(t_box *box);
void			check2(t_box *box);
void			check(t_box *box, int argc, char **argv);
int				timer(t_box *box);
int				main(int argc, char **argv, char **env);
//minimap
void			draw_minimap(t_box *box);
void			draw_map(t_box *box);
void			draw_player(t_box *box);
int				get_fill_color(char grid_item, t_box *box, int i, int j);
void			draw_rays(t_box *box);
//action
void			action_door(t_box *box);
void			rotate_right(t_box *box);
void			rotate_left(t_box *box);
void			cry(t_box *box);
void			cal_move(t_box *box);
//movement
void			move_right(t_box *box);
void			move_left(t_box *box);
void			move_forward(t_box *box);
void			move_back(t_box *box);
void			mouse_y(t_box *box);
//enemy_move
void			sprite_hit(t_box *box, t_sprite *who, t_sprite *what);
void			enemy_angle(t_box *box, t_sprite_data *data);
void			body_angle(t_box *box, t_sprite_data *data);
void			enemy_move(t_box *box, t_sprite_data *data);
//collision
int				check_player_hit(t_box *box, t_sprite_data *data);
int				check_frame_and_remove(t_box *box, t_sprite_data *data,
					t_sprite *sprites);
int				check_collision_with_map(t_box *box, t_sprite_data *data);
int				check_collision_with_door(t_box *box, t_sprite_data *data);
int				check_collision_sprites(t_box *box, t_sprite_data *data,
					t_sprite *sprites);
//hit
int				update_player_frame_when_hit(t_box *box);
int				handle_player_getting_hit(t_box *box);
int				handle_tear(t_box *box, t_sprite_data *data, t_sprite *sprites);
double			calculate_frame_time(t_box *box, t_sprite_data *data);
void			apply_item_effects(t_box *box, int item_id);
//item_move
int				handle_item(t_box *box, t_sprite_data *data, t_sprite *sprites);
int				handle_key(t_box *box, t_sprite *sprites);
int				handle_trophy(t_box *box, t_sprite *sprites);
int				handle_door(t_box *box, t_sprite_data *data);
//sprite_move
void			process_larry_jr_head(t_box *box, t_sprite_data *data);
void			process_larry_jr_body(t_box *box, t_sprite_data *data);
void			process_leech_or_baby(t_box *box, t_sprite_data *data);
int				determine_sprite_action(t_box *box, t_sprite_data *data,
					t_sprite *sprites);
void			cal_sprite_move(t_box *box);
//init_sprite
void			set_data(t_sprite *new);
t_sprite		*new_sprite(void);
t_sprite		*last_sprite(t_sprite *s);
void			sprite_add_back(t_box *box, t_sprite *new);
void			sprite_append(t_box *box, float x, float y, int texture);
//find_seg
t_sprite		*find_seg(t_box *box, int seg);
t_sprite		*find_door(t_box *box, int x, int y);
t_sprite		*find_next_seg(t_box *box, int target_seg);
void			decrement_segments(t_box *box, int seg_limit);
void			update_total_segments(t_box *box);
//remove_seg
void			remove_seg(t_box *box, t_sprite *to_rem);
void			sprite_remove(t_box *box, t_sprite *to_rem);
void			set_player_position(t_box *box, int i, int c);
//handle_dir
void			handle_direction_n(t_box *box, int i, int c);
void			handle_direction_s(t_box *box, int i, int c);
void			handle_direction_e(t_box *box, int i, int c);
void			handle_direction_w(t_box *box, int i, int c);
//process_map
void			process_direction_character(t_box *box, int i, int c);
void			process_single_character(t_box *box, int i, int c);
void			process_map_characters(t_box *box);
void			adjust_map_width(t_box *box);
int				suffix_check(char *s);
//parser
t_point			parse_attribute_values(char *line, int *texture, int *s);
void			handle_larry_jr_head(t_box *box, t_point point, t_sprite *last);
void			read_process_additional_attributes(t_box *box, int fd);
void			parser(t_box *box, int fd);
//sound
int				music(char **env, char *track);
//init_texture
void			alloc_textures(t_box *box);
void			load_specific_textures(t_box *box, int idx, char *path);
void			set_texture_defaults(t_box *box);
void			init_textures(t_box *box);
//init_general
void			init_general_vals(t_box *box);
void			init_pos_dir_vals(t_box *box);
void			init_time_move_vals(t_box *box);
void			init_attr_vals(t_box *box);
void			init_misc_vals(t_box *box);
//reset_vals
void			init_mouse_vals(t_box *box);
void			init_player_vals(t_box *box);
void			init_vals(t_box *box);
void			reset_vals(t_box *box);
void			swap(t_sprite *x);
//sort
void			calc_sprite_distances(t_box *box, t_sprite *sprites);
void			inner_bubble_sort(t_sprite *sprites);
void			outer_bubble_sort(t_box *box);
void			bubble_sort_sprites(t_box *box);

#endif
