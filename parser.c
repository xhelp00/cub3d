/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/25 18:01:31 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite	*new_sprite(void)
{
	t_sprite	*new;

	new = ft_calloc(1, sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->data = ft_calloc(1, sizeof(t_data));
	if (!new->data)
		return (NULL);
	new->data->x = 0;
	new->data->y = 0;
	new->data->start_x = 0;
	new->data->start_y = 0;
	new->data->travel = 0;
	new->data->hp = 100;
	new->data->texture = 0;
	new->data->dir_x = 0;
	new->data->dir_y = 0;
	new->data->state = 0;
	new->data->frame = 0;
	new->data->state = IDLE;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_sprite	*last_sprite(t_sprite *s)
{
	if (!s)
		return (NULL);
	while (s->next)
		s = s->next;
	return (s);
}

void	sprite_add_back(t_box *box, t_sprite *new)
{
	if (box->sprites == NULL)
		box->sprites = new;
	else
	{
		new->prev = last_sprite(box->sprites);
		last_sprite(box->sprites)->next = new;
	}
}

void	sprite_append(t_box *box, float x, float y, int texture)
{
	t_sprite	*new;

	new = new_sprite();
	new->data->x = x;
	new->data->y = y;
	new->data->start_x = x;
	new->data->start_y = y;
	new->data->texture = texture;
	new->data->dir_x = box->info.dir_x;
	new->data->dir_y = box->info.dir_y;
	sprite_add_back(box, new);
}

void	sprite_remove(t_box *box, t_sprite *to_rem)
{
	if (to_rem == box->sprites)
		box->sprites = box->sprites->next;
	else
		to_rem->prev->next = to_rem->next;
	if (to_rem->next)
		to_rem->next->prev = to_rem->prev;
	free(to_rem->data);
	free(to_rem);
}

void	parser(t_box *box, int fd)
{
	char	*line;
	char	*tmp;
	int		i;
	int		s;
	int		c;

	box->map = malloc(sizeof(char *));
	box->map[0] = NULL;
	box->map_width = 0;
	box->map_height = 0;
	line = get_next_line(fd);
	while (line[0] != '\n')
	{
		box->map = ft_arrappend(box->map, ft_strtrim(line, "\n"));
		if ((int) ft_strlen(line) - 1 > box->map_width)
			box->map_width = ft_strlen(line) - 1;
		line = (free(line), get_next_line(fd));
		box->map_height++;
	}
	free(line);
	i = -1;
	while (box->map[++i])
	{
		c = -1;
		while (box->map[i][++c])
		{
			if (box->map[i][c] == ' ')
				box->map[i][c] = '1';
			if (box->map[i][c] == 'N')
			{
				box->info.pos_x = i;
				box->info.pos_y = c;
				box->map[i][c] = '0';
			}
			else if (box->map[i][c] == 'S')
			{
				box->info.pos_x = i;
				box->info.pos_y = c;
				box->info.rot_speed = 3.143;
				box->info.rotate = 1;
				cal_move(box);
				box->info.rotate = 0;
				box->map[i][c] = '0';
			}
			else if (box->map[i][c] == 'E')
			{
				box->info.pos_x = i;
				box->info.pos_y = c;
				box->info.rot_speed = 1.5715;
				box->info.rotate = 1;
				cal_move(box);
				box->info.rotate = 0;
				box->map[i][c] = '0';
			}
			else if (box->map[i][c] == 'W')
			{
				box->info.pos_x = i;
				box->info.pos_y = c;
				box->info.rot_speed = 1.5715;
				box->info.rotate = -1;
				cal_move(box);
				box->info.rotate = 0;
				box->map[i][c] = '0';
			}
		}
		if ((int) ft_strlen(box->map[i]) < box->map_width)
		{
			tmp = malloc(sizeof(char *) * box->map_width + 1);
			ft_memset(tmp, '1', box->map_width);
			c = -1;
			while (box->map[i][++c])
				tmp[c] = box->map[i][c];
			box->map[i] = (free(box->map[i]), tmp);
		}
	}
	line = get_next_line(fd);
	float	x = 0;
	float	y = 0;
	int		texture = 0;
	while (line)
	{
		s = 0;
		x = atof(line);
		while (line[s] != ',' && line[s] != '\n')
			s++;
		s++;
		y = atof(line + s);
		while (line[s] != ',' && line[s] != '\n')
			s++;
		s++;
		texture = ft_atoi(line + s);
		line = (free(line), get_next_line(fd));
		// printf("%s\n%f | %f | %i\n", "ADDING SPRITE IN PROGRESS!!!!", x, y, texture);
		sprite_append(box, x, y, texture);
		// i = -1;
		// printf("\nDUMP:\n");
		// while (++i < box->n_sprites)
		// 	printf("Texture: %i | x: %f | y: %f\n", box->sprites[i].texture, box->sprites[i].x, box->sprites[i].y);
	}
	free(line);
}
