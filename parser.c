/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:19 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_data(t_sprite *new)
{
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
	new->data->n_seg = 0;
	new->data->start_n_seg = 0;
	new->data->seg = 0;
	new->data->hit = 0;
	new->data->id = 0;
	new->data->sound = 0;
	new->data->opening = 0;
	new->data->state = IDLE;
	new->next = NULL;
	new->prev = NULL;
}

t_sprite	*new_sprite(void)
{
	t_sprite	*new;

	new = ft_calloc(1, sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->data = ft_calloc(1, sizeof(t_sprite_data));
	if (!new->data)
		return (NULL);
	set_data(new);
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
	if (new->data->texture == LARRY_JR_HEAD)
	{
		new->data->n_seg = 5;
		new->data->start_n_seg = 5;
	}
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
	if (texture > 50)
	{
		new->data->id = texture - 100;
		new->data->texture = ITEMS;
	}
	else
		new->data->texture = texture;
	new->data->dir_x = box->info.dir_x;
	new->data->dir_y = box->info.dir_y;
	sprite_add_back(box, new);
}

t_sprite	*find_seg(t_box *box, int seg)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if (sprites->data->seg == seg && (sprites->data->texture
				== LARRY_JR_BODY || sprites->data->texture == LARRY_JR_HEAD))
			return (sprites);
		sprites = sprites->next;
	}
	return (sprites);
}

t_sprite	*find_door(t_box *box, int x, int y)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	if (!sprites)
		return (NULL);
	while (sprites)
	{
		if (sprites->data->x == x && sprites->data->y == y
			&& sprites->data->texture == DOOR)
			return (sprites);
		sprites = sprites->next;
	}
	return (NULL);
}

t_sprite	*find_next_seg(t_box *box, int target_seg)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if (sprites->data->seg == target_seg)
		{
			return (sprites);
		}
		sprites = sprites->next;
	}
	return (NULL);
}

void	decrement_segments(t_box *box, int seg_limit)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if ((sprites->data->texture == LARRY_JR_HEAD || sprites->data->texture
				== LARRY_JR_BODY)
			&& sprites->data->seg > seg_limit)
		{
			sprites->data->seg--;
		}
		sprites = sprites->next;
	}
}

void	update_total_segments(t_box *box)
{
	t_sprite	*sprites;

	sprites = box->sprites;
	while (sprites)
	{
		if (sprites->data->texture == LARRY_JR_HEAD || sprites->data->texture
			== LARRY_JR_BODY)
		{
			sprites->data->n_seg--;
		}
		sprites = sprites->next;
	}
}

void	remove_seg(t_box *box, t_sprite *to_rem)
{
	t_sprite	*next_head;

	if (to_rem->data->texture == LARRY_JR_BODY || to_rem->data->texture
		== LARRY_JR_HEAD)
	{
		if (to_rem->data->seg == 0)
		{
			next_head = find_next_seg(box, to_rem->data->seg + 1);
			if (next_head)
			{
				next_head->data->texture = LARRY_JR_HEAD;
			}
			decrement_segments(box, -1);
		}
		else
		{
			decrement_segments(box, to_rem->data->seg);
		}
		update_total_segments(box);
	}
}

void	sprite_remove(t_box *box, t_sprite *to_rem)
{
	remove_seg(box, to_rem);
	if (to_rem == box->sprites)
		box->sprites = box->sprites->next;
	else
		to_rem->prev->next = to_rem->next;
	if (to_rem->next)
		to_rem->next->prev = to_rem->prev;
	free(to_rem->data);
	free(to_rem);
}

// Function for initialization and reading the map.
void	initialize_and_read_map(t_box *box, int fd, char **line)
{
	box->map = malloc(sizeof(char *));
	box->map[0] = NULL;
	box->map_width = 0;
	box->map_height = 0;
	*line = get_next_line(fd);
	while ((*line)[0] != '\n')
	{
		box->map = ft_arrappend(box->map, ft_strtrim(*line, "\n"));
		if ((int) ft_strlen(*line) - 1 > box->map_width)
			box->map_width = ft_strlen(*line) - 1;
		*line = (free(*line), get_next_line(fd));
		box->map_height++;
	}
	free(*line);
}

void	set_player_position(t_box *box, int i, int c)
{
	box->info.pos_x = i;
	box->info.pos_y = c;
}

void	handle_direction_n(t_box *box, int i, int c)
{
	box->map[i][c] = '0';
}

void	handle_direction_s(t_box *box, int i, int c)
{
	box->info.rot_speed = 3.143;
	box->info.rotate = 1;
	cal_move(box);
	box->info.rotate = 0;
	box->map[i][c] = '0';
}

void	handle_direction_e(t_box *box, int i, int c)
{
	box->info.rot_speed = 1.5715;
	box->info.rotate = 1;
	cal_move(box);
	box->info.rotate = 0;
	box->map[i][c] = '0';
}

void	handle_direction_w(t_box *box, int i, int c)
{
	box->info.rot_speed = 1.5715;
	box->info.rotate = -1;
	cal_move(box);
	box->info.rotate = 0;
	box->map[i][c] = '0';
}

void	process_direction_character(t_box *box, int i, int c)
{
	char	current_char;

	set_player_position(box, i, c);
	current_char = box->map[i][c];
	if (current_char == 'N')
		handle_direction_n(box, i, c);
	else if (current_char == 'S')
		handle_direction_s(box, i, c);
	else if (current_char == 'E')
		handle_direction_e(box, i, c);
	else if (current_char == 'W')
		handle_direction_w(box, i, c);
}

void	process_single_character(t_box *box, int i, int c)
{
	if (box->map[i][c] == ' ')
		box->map[i][c] = '1';
	else if (box->map[i][c] == DOOR + 1 + '0')
		sprite_append(box, i, c, DOOR);
	else if (box->map[i][c] == 'N' || box->map[i][c] == 'S' || box->map[i][c]
		== 'E' || box->map[i][c] == 'W')
		process_direction_character(box, i, c);
}

void	process_map_characters(t_box *box)
{
	int	i;
	int	c;

	i = -1;
	while (box->map[++i])
	{
		c = -1;
		while (box->map[i][++c])
		{
			process_single_character(box, i, c);
		}
	}
}

// Function for adjusting the map width.
void	adjust_map_width(t_box *box)
{
	int		c;
	int		i;
	char	*tmp;

	i = -1;
	while (box->map[++i])
	{
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
}

// Function for reading and processing additional map attributes.
t_point	parse_attribute_values(char *line, int *texture, int *s)
{
	t_point	point;

	*s = 0;
	point.x = atof(line);
	while (line[*s] != ',' && line[*s] != '\n')
		(*s)++;
	(*s)++;
	point.y = atof(line + *s);
	while (line[*s] != ',' && line[*s] != '\n')
		(*s)++;
	(*s)++;
	*texture = ft_atoi(line + *s);
	return (point);
}

void	handle_larry_jr_head(t_box *box, t_point point, t_sprite *last)
{
	while (last->data->seg++ < last->data->n_seg)
	{
		sprite_append(box, point.x + last->data->seg / 3.0, point.y
			+ last->data->seg / 3.0, LARRY_JR_BODY);
		last_sprite(box->sprites)->data->seg = last->data->seg;
		last_sprite(box->sprites)->data->n_seg = last->data->n_seg;
		last_sprite(box->sprites)->data->start_n_seg = last->data->start_n_seg;
	}
	last->data->seg = 0;
}

void	read_process_additional_attributes(t_box *box, int fd)
{
	char		*line;
	t_point		point;
	t_sprite	*last;
	int			s;
	int			texture;

	line = get_next_line(fd);
	while (line)
	{
		point = parse_attribute_values(line, &texture, &s);
		line = (free(line), get_next_line(fd));
		sprite_append(box, point.x, point.y, texture);
		last = last_sprite(box->sprites);
		if (last->data->texture == LARRY_JR_HEAD)
		{
			handle_larry_jr_head(box, point, last);
		}
		else if (last->data->texture == ITEMS)
		{
			sprite_append(box, point.x, point.y, ITEM_ALTAR);
		}
	}
	free(line);
}

void	parser(t_box *box, int fd)
{
	char	*line;

	initialize_and_read_map(box, fd, &line);
	process_map_characters(box);
	adjust_map_width(box);
	read_process_additional_attributes(box, fd);
}
