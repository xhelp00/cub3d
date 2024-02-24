/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 14:04:56 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:12:41 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"

void	cast_floor(t_box *box)
{
	int	y;
	int	x;

	y = -1;
	while (++y < SCREENHEIGHT)
	{
		reset_vals(box);
		if (y > SCREENHEIGHT / 2 + box->info.pitch)
			box->info.is_floor = 1;
		else
			box->info.is_floor = 0;
		box->info.ray_dir_x0 = box->info.dir_x - box->info.plane_x;
		box->info.ray_dir_y0 = box->info.dir_y - box->info.plane_y;
		box->info.ray_dir_x1 = box->info.dir_x + box->info.plane_x;
		box->info.ray_dir_y1 = box->info.dir_y + box->info.plane_y;

		if (box->info.is_floor)
			box->info.p = y - SCREENHEIGHT / 2 - box->info.pitch;
		else
			box->info.p = SCREENHEIGHT / 2 - y + box->info.pitch;

		if (box->info.is_floor)
			box->info.cam_z = 0.5 * SCREENHEIGHT + box->info.pos_z;
		else
			box->info.cam_z = 0.5 * SCREENHEIGHT - box->info.pos_z;

		box->info.row_distance = box->info.cam_z / box->info.p;

		box->info.floor_step_x = box->info.row_distance * (box->info.ray_dir_x1 - box->info.ray_dir_x0) / SCREENWIDTH;
		box->info.floor_step_y = box->info.row_distance * (box->info.ray_dir_y1 - box->info.ray_dir_y0) / SCREENWIDTH;

		box->info.floor_x = box->info.pos_x + box->info.row_distance * box->info.ray_dir_x0;
		box->info.floor_y = box->info.pos_y + box->info.row_distance * box->info.ray_dir_y0;

		x = -1;
		while (++x < SCREENWIDTH)
		{
			box->info.cell_x = (int)(box->info.floor_x);
			box->info.cell_y = (int)(box->info.floor_y);

			box->info.tx = (int)(TEXTUREWIDTH * (box->info.floor_x - box->info.cell_x)) & (TEXTUREWIDTH - 1);
			box->info.ty = (int)(TEXTUREHEIGHT * (box->info.floor_y - box->info.cell_y)) & (TEXTUREHEIGHT - 1);

			box->info.floor_x += box->info.floor_step_x;
			box->info.floor_y += box->info.floor_step_y;

			box->info.floor_texture = 1;
			box->info.ceiling_texture = 1;

			box->info.distance = (int)((box->info.pos_x - box->info.floor_x) * (box->info.pos_x - box->info.floor_x) + (box->info.pos_y - box->info.floor_y) * (box->info.pos_y - box->info.floor_y));

			if (box->info.distance < 100)
			{
				box->info.color = extract_color(&box->textures[box->info.ceiling_texture].addr[box->info.tx * 4 + box->textures[box->info.floor_texture].line_len * box->info.ty]);
				box->info.color = (box->info.color >> 1) & 8355711;
				my_mlx_pyxel_put(&box->image, x, y, 0xFF << 24 | box->info.color);
				// printf("%d\n", box->info.distance);
				my_mlx_pyxel_put(&box->shaders, x, y, pixel_visibility((float)(100 - (box->info.distance))/100));
				// my_mlx_pyxel_put(&box->shaders, x, y, pixel_visibility(1));
			}
		}
	}
}

void	draw_door(t_box *box, int x)
{
	t_sprite	*door;

	door = find_door(box, box->info.door_x, box->info.door_y);
	if (!box->info.door_side)
		box->info.prep_wall_dist = (box->info.door_dist_x - box->info.delta_dist_x);
	else
		box->info.prep_wall_dist = (box->info.door_dist_y - box->info.delta_dist_y);
	box->info.line_height = (int)(SCREENHEIGHT / box->info.prep_wall_dist);
	box->info.draw_start = -box->info.line_height / 2 + SCREENHEIGHT / 2 + box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
	if (box->info.draw_start < 0)
		box->info.draw_start = 0;
	box->info.draw_end = box->info.line_height / 2 + SCREENHEIGHT / 2 + box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
	if (box->info.draw_end >= SCREENHEIGHT)
		box->info.draw_end = SCREENHEIGHT - 1;
	box->info.text_num = box->map[box->info.door_x][box->info.door_y] - 1 - '0';
	if (!box->info.door_side)
		box->info.wall_x = box->info.pos_y + box->info.prep_wall_dist * box->info.ray_dir_y;
	else
		box->info.wall_x = box->info.pos_x + box->info.prep_wall_dist * box->info.ray_dir_x;
	box->info.wall_x -= floor((box->info.wall_x));
	box->info.text_x = (int)(box->info.wall_x * (double)TEXTUREWIDTH);
	if (!box->info.door_side && box->info.ray_dir_x > 0)
		box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
	if (box->info.door_side && box->info.ray_dir_y < 0)
		box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
	box->info.step = 1.0 * TEXTUREHEIGHT / box->info.line_height;
	box->info.tex_pos = (box->info.draw_start - box->info.pitch - (box->info.pos_z / box->info.prep_wall_dist) - SCREENHEIGHT / 2 + box->info.line_height / 2) * box->info.step;
	box->info.draw = box->info.draw_start;
	while (box->info.draw++ < box->info.draw_end)
	{
		box->info.text_y = (int)box->info.tex_pos & (TEXTUREHEIGHT - 1);
		box->info.tex_pos += box->info.step;
		// printf("DOOR OPENING: %i | DOOR STATE %i\n", door->data->opening, door->data->state);
		if (!door->data->opening)
			box->info.color = extract_color(&box->textures[box->info.text_num].addr[box->info.text_x * 4 + box->textures[box->info.text_num].line_len * box->info.text_y]);
		else if (door->data->opening)
		{
			if (box->info.text_x - door->data->frame * 2 < 64 && box->info.text_x - door->data->frame * 2 > 0)
				box->info.color = extract_color(&box->textures[box->info.text_num].addr[(box->info.text_x - door->data->frame * 2) * 4 + box->textures[box->info.text_num].line_len * box->info.text_y]);
			else
				box->info.color = 0;
		}
		if ((box->info.color & 0x00FFFFFF) != 0)
		{
			// apply_fog(box, box->info.prep_wall_dist * 9);
			my_mlx_pyxel_put(&box->image, x, box->info.draw, 0xFF << 24 | box->info.color);
			if ((int)box->info.prep_wall_dist < 12)
				my_mlx_pyxel_put(&box->shaders, x, box->info.draw, pixel_visibility((float)(12 - box->info.prep_wall_dist)/12));
			else
				my_mlx_pyxel_put(&box->shaders, x, box->info.draw, pixel_visibility(0));
		}
	}
	box->info.zbuffer[x] = box->info.prep_wall_dist;
}

void	cast_wall(t_box *box)
{
	int	x;
	//t_line	line;
	//box->info.ray = malloc(sizeof(t_ray) * SCREENWIDTH + 1);

	x = -1;
	while (++x < SCREENWIDTH)
	{
		reset_vals(box);
		box->info.camera_x = 2 * x / (double)SCREENWIDTH - 1;
		box->info.ray_dir_x = box->info.dir_x + box->info.plane_x * box->info.camera_x;
		box->info.ray_dir_y = box->info.dir_y + box->info.plane_y * box->info.camera_x;
		box->info.map_x = (int)box->info.pos_x;
		box->info.map_y = (int)box->info.pos_y;
		box->info.delta_dist_x = fabs(1 / box->info.ray_dir_x);
		box->info.delta_dist_y = fabs(1 / box->info.ray_dir_y);



		if (box->info.ray_dir_x < 0)
		{
			box->info.step_x = -1;
			box->info.side_dist_x = (box->info.pos_x - box->info.map_x) * box->info.delta_dist_x;
		}
		else
		{
			box->info.step_x = 1;
			box->info.side_dist_x = (box->info.map_x + 1.0 - box->info.pos_x) * box->info.delta_dist_x;
		}
		if (box->info.ray_dir_y < 0)
		{
			box->info.step_y = -1;
			box->info.side_dist_y = (box->info.pos_y - box->info.map_y) * box->info.delta_dist_y;
		}
		else
		{
			box->info.step_y = 1;
			box->info.side_dist_y = (box->info.map_y + 1.0 - box->info.pos_y) * box->info.delta_dist_y;
		}
		while(!box->info.hit)
		{
			if (box->info.side_dist_x < box->info.side_dist_y)
			{
				box->info.side_dist_x += box->info.delta_dist_x;
				box->info.map_x += box->info.step_x;
				box->info.side = 0;
			}
			else
			{
				box->info.side_dist_y += box->info.delta_dist_y;
				box->info.map_y += box->info.step_y;
				box->info.side = 1;
			}
			if (box->map[box->info.map_x][box->info.map_y] > '0' && box->map[box->info.map_x][box->info.map_y] != DOOR + 1 + '0')
				box->info.hit = 1;
			else if (box->map[box->info.map_x][box->info.map_y] == DOOR + 1 + '0' && !box->info.door && !(find_door(box, box->info.map_x, box->info.map_y)->data->state == OPEN && !find_door(box, box->info.map_x, box->info.map_y)->data->opening))
			{
				box->info.door_side = box->info.side;
				box->info.door = 1;
				box->info.door_x = box->info.map_x;
				box->info.door_y = box->info.map_y;
				box->info.door_dist_x = box->info.side_dist_x;
				box->info.door_dist_y = box->info.side_dist_y;
			}
		}
		if (!box->info.side)
			box->info.prep_wall_dist = (box->info.side_dist_x - box->info.delta_dist_x);
		else
			box->info.prep_wall_dist = (box->info.side_dist_y - box->info.delta_dist_y);
		box->info.line_height = (int)(SCREENHEIGHT / box->info.prep_wall_dist);
		box->info.draw_start = -box->info.line_height / 2 + SCREENHEIGHT / 2 + box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
		if (box->info.draw_start < 0)
			box->info.draw_start = 0;
		box->info.draw_end = box->info.line_height / 2 + SCREENHEIGHT / 2 + box->info.pitch + (box->info.pos_z / box->info.prep_wall_dist);
		if (box->info.draw_end >= SCREENHEIGHT)
			box->info.draw_end = SCREENHEIGHT - 1;

		box->info.text_num = box->map[box->info.map_x][box->info.map_y] - 1 - '0';
		if (!box->info.side)
			box->info.wall_x = box->info.pos_y + box->info.prep_wall_dist * box->info.ray_dir_y;
		else
			box->info.wall_x = box->info.pos_x + box->info.prep_wall_dist * box->info.ray_dir_x;
		box->info.wall_x -= floor((box->info.wall_x));

		box->info.text_x = (int)(box->info.wall_x * (double)TEXTUREWIDTH);
		if (!box->info.side && box->info.ray_dir_x > 0)
			box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;
		if (box->info.side && box->info.ray_dir_y < 0)
			box->info.text_x = TEXTUREWIDTH - box->info.text_x - 1;

		box->info.step = 1.0 * TEXTUREHEIGHT / box->info.line_height;
		box->info.tex_pos = (box->info.draw_start - box->info.pitch - (box->info.pos_z / box->info.prep_wall_dist) - SCREENHEIGHT / 2 + box->info.line_height / 2) * box->info.step;

		box->info.draw = box->info.draw_start;
		while (box->info.draw++ < box->info.draw_end)
		{
			box->info.text_y = (int)box->info.tex_pos & (TEXTUREHEIGHT - 1);
			box->info.tex_pos += box->info.step;
			box->info.color = extract_color(&box->textures[box->info.text_num].addr[box->info.text_x * 4 + box->textures[box->info.text_num].line_len * box->info.text_y]);
			if (box->info.side)
				box->info.color = (box->info.color >> 1) & 8355711;
			// apply_fog(box, box->info.prep_wall_dist * 9);
			// printf("%f\n", box->info.prep_wall_dist);
			my_mlx_pyxel_put(&box->image, x, box->info.draw, 0xFF << 24 | box->info.color);
			if ((int)box->info.prep_wall_dist < 12)
				my_mlx_pyxel_put(&box->shaders, x, box->info.draw, pixel_visibility((float)(12 - box->info.prep_wall_dist)/12));
			else
				my_mlx_pyxel_put(&box->shaders, x, box->info.draw, pixel_visibility(0));
		}
		box->info.zbuffer[x] = box->info.prep_wall_dist;
		if (box->info.door)
			draw_door(box, x);
		//printf("%i: %f\n", x, box->info.zbuffer[x]);

		//this part is updating array of rays (their endings)
		box->info.ray[x].end_x = (box->info.map_y *10) - (box->map_width * 10) + SCREENWIDTH - MINIMAP_OFFSET;
		box->info.ray[x].end_y = (box->info.map_x *10) + MINIMAP_OFFSET;
		if (box->info.ray[x].end_x < (box->info.pos_y * 10) + SCREENWIDTH - (box->map_width * 10) - MINIMAP_OFFSET -5)
			box->info.ray[x].end_x += 10;
		if (box->info.ray[x].end_y < (box->info.pos_x * 10) + MINIMAP_OFFSET -5)
			box->info.ray[x].end_y += 10;
	}
}

void	cast_leech(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == UP)
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec / 100000.0) * 6) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 16]);
	else if (dir == DOWN)
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec / 100000.0) * 6) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 48]);
	else if (dir == LEFT && !box->info.flipped)
	{
		box->info.tex_x = 46 - (box->info.tex_x - 16);
		box->info.flipped = 1;
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec / 100000.0) * 6) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -16]);
	}
	else
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 16 + 32 * ((int)((box->time.tv_usec / 100000.0) * 6) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -16]);
}

void	cast_larry(t_box *box, t_sprite *sprites, int dir)
{
	if (dir == UP)
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 32 + 48) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * (-20 + 48 * ((int)((box->time.tv_usec / 100000.0) * 2) / 10))]);
	else if (dir == DOWN)
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16 + 48 - 48 * ((int)((box->time.tv_usec / 100000.0) * 2) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 28]);
	else if (dir == LEFT && !box->info.flipped)
	{
		box->info.tex_x = 62 - (box->info.tex_x - 16);
		box->info.flipped = 1;
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16 + 48 - 48 * ((int)((box->time.tv_usec / 100000.0) * 2) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -20]);
	}
	else
		box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16 + 48 - 48 * ((int)((box->time.tv_usec / 100000.0) * 2) / 10)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -20]);
}

void	cast_obj(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	bubble_sort_sprites(box);
	while (sprites)
	{
		box->info.sprite_x = sprites->data->x - box->info.pos_x;
		box->info.sprite_y = sprites->data->y - box->info.pos_y;
		box->info.inv_det = 1.0 / (box->info.plane_x * box->info.dir_y - box->info.dir_x * box->info.plane_y);
		box->info.transform_x = box->info.inv_det * (box->info.dir_y * box->info.sprite_x - box->info.dir_x * box->info.sprite_y);
		box->info.transform_y = box->info.inv_det * (-box->info.plane_y * box->info.sprite_x + box->info.plane_x * box->info.sprite_y);
		box->info.sprite_screen_x = (int)((SCREENWIDTH / 2) * (1 + box->info.transform_x / box->info.transform_y));

		box->info.v_move_screen = (int)(VMOVE / box->info.transform_y) + box->info.pitch + box->info.pos_z / box->info.transform_y;
		box->info.sprite_height = abs((int)(SCREENHEIGHT / (box->info.transform_y))) / VDIV;

		box->info.draw_start_y = (-box->info.sprite_height / 2 + SCREENHEIGHT / 2) + box->info.v_move_screen;
		if (box->info.draw_start_y < 0)
			box->info.draw_start_y = 0;

		box->info.draw_end_y = (box->info.sprite_height / 2 + SCREENHEIGHT / 2) + box->info.v_move_screen;
		if (box->info.draw_end_y >= SCREENHEIGHT)
			box->info.draw_end_y = SCREENHEIGHT - 1;

		box->info.sprite_width = abs((int)(SCREENHEIGHT / (box->info.transform_y))) / UDIV;

		box->info.draw_start_x = -box->info.sprite_width / 2 + box->info.sprite_screen_x;
		if (box->info.draw_start_x < 0)
			box->info.draw_start_x = 0;

		box->info.draw_end_x = box->info.sprite_width / 2 + box->info.sprite_screen_x;
		if (box->info.draw_end_x >= SCREENWIDTH)
			box->info.draw_end_x = SCREENWIDTH - 1;

		box->info.dx = sprites->data->x - box->info.pos_x;
		box->info.dy = sprites->data->y - box->info.pos_y;
		box->info.t_angle = atan2(box->info.dy, box->info.dx);
		//printf("Angle: %f | %f %f %f - %f %f - %f\n", angle, dx, dy, sprites->data->x, box->info.pos_x, sprites->data->y, box->info.pos_y);

		box->info.stripe = box->info.draw_start_x;
		while (box->info.stripe < box->info.draw_end_x)
		{
			box->info.tex_x = (int)(256 * (box->info.stripe - (-box->info.sprite_width / 2 + box->info.sprite_screen_x)) * TEXTUREWIDTH / box->info.sprite_width) / 256;
			box->info.flipped = 0;
			if (box->info.transform_y > 0 && box->info.transform_y < box->info.zbuffer[box->info.stripe])
			{
				//printf("Sprite n: %i // %f > 0 | %d > 0 | %d < %d | %f < %f\n", i, box->info.transform_y, box->info.stripe, box->info.stripe, SCREENWIDTH, box->info.transform_y, box->info.zbuffer[box->info.stripe]);
				box->info.part = box->info.draw_start_y;
				while (box->info.part < box->info.draw_end_y)
				{
					box->info.d = (box->info.part - box->info.v_move_screen) * 256 - SCREENHEIGHT * 128 + box->info.sprite_height * 128;
					box->info.tex_y = ((box->info.d * TEXTUREHEIGHT) / box->info.sprite_height) / 256;
					//printf("Color from: %i\n", sprites->data->texture);
					if (sprites->data->texture == BABY)
					{
						if (box->info.tex_y < 47 && box->info.tex_y > 15)
						{
							if (sprites->data->dist < 2)
							{
								sprites->data->state = AWAKE;
								box->info.color = extract_color(&box->textures[sprites->data->texture].addr[(box->info.tex_x * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 16]);
								if (!sprites->data->sound)
								{
									sprites->data->sound = 1;
									sound_play(box, &box->sound.sfx[ANGRY]);
								}
							}
							else
								box->info.color = extract_color(&box->textures[sprites->data->texture].addr[(box->info.tex_x * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -16]);
						}
						else
							box->info.color = 0;

					}
					else if (sprites->data->texture == NERVE_ENDING)
					{
						if (box->info.tex_x < 48 && box->info.tex_x > 15)
							box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 16 + 32 * ((int)(box->time.tv_usec / 100000.0) / 2)) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y]);
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == LEECH)
					{
						if (box->info.tex_x < 48 && box->info.tex_x > 15 && box->info.tex_y < 47 && box->info.tex_y > 15)
						{
							//SPRITE UP
							if (sprites->data->dir_x < -0.7
									&& sprites->data->dir_y > -0.75 && sprites->data->dir_y < 0.75)
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, UP);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, DOWN);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_leech(box, sprites, RIGHT);
								//PLAYER RIGHT
								else
									cast_leech(box, sprites, LEFT);
							}
							//SPRITE DOWN
							else if (sprites->data->dir_x > 0.7
									&& sprites->data->dir_y > -0.75 && sprites->data->dir_y < 0.75)
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, DOWN);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, UP);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_leech(box, sprites, LEFT);
								//PLAYER RIGHT
								else
									cast_leech(box, sprites, RIGHT);
							}
							//SPRITE LEFT
							else if (sprites->data->dir_x > -0.75 && sprites->data->dir_x < 0.75
									&& sprites->data->dir_y < -0.7 && !box->info.flipped)
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, LEFT);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, RIGHT);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_leech(box, sprites, UP);
								//PLAYER RIGHT
								else
									cast_leech(box, sprites, DOWN);
							}
							//SPRITE RIGHT
							else
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, RIGHT);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_leech(box, sprites, LEFT);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_leech(box, sprites, DOWN);
								//PLAYER RIGHT
								else
									cast_leech(box, sprites, UP);
							}
						}
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == ISAAC)
					{
						if (box->info.tex_x < 56 && box->info.tex_x > 20 && box->info.tex_y < 60 && box->info.tex_y > 12)
						{
							box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16 + 32 * ((int)(box->time.tv_usec / 100000.0))) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 42]);
							if ((box->info.color & 0x00FFFFFF) != 0)
							{
								hit_mark(box, sprites);
								// apply_fog(box, sprites->data->dist);
								my_mlx_pyxel_put(&box->image, box->info.stripe, box->info.part, 0xFF << 24 | box->info.color);
								if (sprites->data->dist < 100)
									my_mlx_pyxel_put(&box->shaders, box->info.stripe, box->info.part, pixel_visibility((float)(100 - (sprites->data->dist))/100));
								else
									my_mlx_pyxel_put(&box->shaders, box->info.stripe, box->info.part, pixel_visibility(0));
							}
							box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 8]);
						}
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == TEAR && sprites->data->hit)
						box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x + 64 * sprites->data->frame) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * 64 * (sprites->data->frame / 4)]);
					else if (sprites->data->texture == TEAR && !sprites->data->hit && sprites->data->travel * 10 > 1)
						box->info.color = extract_color(&box->textures[sprites->data->texture].addr[(box->info.tex_x * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len]);
					else if (sprites->data->texture == LARRY_JR_HEAD)
					{
						if (box->info.tex_x < 60 && box->info.tex_x > 20 && box->info.tex_y < 60 && box->info.tex_y > 25)
						{
							//SPRITE UP
							if (sprites->data->dir_x < -0.7
									&& sprites->data->dir_y > -0.75 && sprites->data->dir_y < 0.75)
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, UP);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, DOWN);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_larry(box, sprites, RIGHT);
								//PLAYER RIGHT
								else
									cast_larry(box, sprites, LEFT);
							}
							//SPRITE DOWN
							else if (sprites->data->dir_x > 0.7
									&& sprites->data->dir_y > -0.75 && sprites->data->dir_y < 0.75)
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, DOWN);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, UP);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_larry(box, sprites, LEFT);
								//PLAYER RIGHT
								else
									cast_larry(box, sprites, RIGHT);
							}
							//SPRITE LEFT
							else if (sprites->data->dir_x > -0.75 && sprites->data->dir_x < 0.75
									&& sprites->data->dir_y < -0.7 && !box->info.flipped)
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, LEFT);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, RIGHT);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_larry(box, sprites, UP);
								//PLAYER RIGHT
								else
									cast_larry(box, sprites, DOWN);
							}
							//SPRITE RIGHT
							else
							{
								//PLAYER UP
								if (box->info.dir_x < -0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, RIGHT);
								//PLAYER DOWN
								else if (box->info.dir_x > 0.7
									&& box->info.dir_y > -0.75 && box->info.dir_y < 0.75)
									cast_larry(box, sprites, LEFT);
								//PLAYER LEFT
								else if (box->info.dir_x > -0.75 && box->info.dir_x < 0.75
									&& box->info.dir_y < -0.7)
									cast_larry(box, sprites, DOWN);
								//PLAYER RIGHT
								else
									cast_larry(box, sprites, UP);
							}
						}
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == LARRY_JR_BODY)
					{
						if (box->info.tex_x < 50 && box->info.tex_x > 20 && box->info.tex_y < 60 && box->info.tex_y > 30)
						{
							if (sprites->data->seg == sprites->data->n_seg)
								box->info.color = extract_color(&box->textures[LARRY_JR_HEAD].addr[((box->info.tex_x - 20 + 32 * ((int)((box->time.tv_usec / 100000.0) * 2) / 10)) * 4) + box->textures[LARRY_JR_HEAD].line_len * box->info.tex_y + box->textures[LARRY_JR_HEAD].line_len * 96]);
							else
								box->info.color = extract_color(&box->textures[LARRY_JR_HEAD].addr[((box->info.tex_x - 20 + 32 - 32 * ((int)((box->time.tv_usec / 100000.0) * 2) / 10)) * 4) + box->textures[LARRY_JR_HEAD].line_len * box->info.tex_y + box->textures[LARRY_JR_HEAD].line_len * 64]);
						}
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == ITEMS)
					{
						sprites->data->frame = ((int)((box->time.tv_usec / 100000.0) * 4) / 5);
						if (sprites->data->frame > 4)
							sprites->data->frame = 8 - sprites->data->frame;
						if (box->info.tex_x < 48 && box->info.tex_x > 16 && box->info.tex_y < 48 - 1 * sprites->data->frame && box->info.tex_y > 16 - 1 * sprites->data->frame)
							box->info.color = extract_color(&box->textures[ITEMS].addr[((box->info.tex_x - 16 + ((sprites->data->id % 20) * 32)) * 4) + box->textures[ITEMS].line_len * box->info.tex_y + box->textures[ITEMS].line_len * ((-16 + sprites->data->frame) + (sprites->data->id / 20) * 32)]);
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == TROPHY)
					{
						if (box->info.tex_x < 48 && box->info.tex_x > 16 && box->info.tex_y < 64 && box->info.tex_y > 8)
							box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -8]);
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == KEY)
					{
						if (box->info.tex_x < 32 && box->info.tex_x > 16 && box->info.tex_y < 64 && box->info.tex_y > 32)
							box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -32]);
						else
							box->info.color = 0;
					}
					else if (sprites->data->texture == ITEM_ALTAR)
					{
						if (box->info.tex_x < 48 && box->info.tex_x > 16 && box->info.tex_y < 64 && box->info.tex_y > 40)
							box->info.color = extract_color(&box->textures[sprites->data->texture].addr[((box->info.tex_x - 16) * 4) + box->textures[sprites->data->texture].line_len * box->info.tex_y + box->textures[sprites->data->texture].line_len * -40]);
						else
							box->info.color = 0;
					}
					else
						box->info.color = 0;
					if ((box->info.color & 0xFFFFFFFF) != 0)
					{
						hit_mark(box, sprites);
						// apply_fog(box, sprites->data->dist);
						my_mlx_pyxel_put(&box->image, box->info.stripe, box->info.part, 0xFF << 24 | box->info.color);
						if (sprites->data->dist < 100)
							my_mlx_pyxel_put(&box->shaders, box->info.stripe, box->info.part, pixel_visibility((float)(100 - (sprites->data->dist))/100));
						else
							my_mlx_pyxel_put(&box->shaders, box->info.stripe, box->info.part, pixel_visibility(0));
					}
					box->info.part++;
				}
			}
			box->info.stripe++;
		}
		sprites = sprites->next;
	}
}
