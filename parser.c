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

t_sprite	*new_sprite(void)
{
	t_sprite	*new;

	new = ft_calloc(1, sizeof(t_sprite));
	if (!new)
		return (NULL);
	new->data = ft_calloc(1, sizeof(t_sprite_data));
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
		if (sprites->data->seg == seg && (sprites->data->texture == LARRY_JR_BODY || sprites->data->texture == LARRY_JR_HEAD))
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
		if (sprites->data->x == x && sprites->data->y == y && sprites->data->texture == DOOR)
			return (sprites);
		sprites = sprites->next;
	}
	return (NULL);
}

void	remove_seg(t_box *box, t_sprite *to_rem)
{
	t_sprite	*sprites;

	if (to_rem->data->texture == LARRY_JR_BODY || to_rem->data->texture == LARRY_JR_HEAD)
	{
		if (to_rem->data->seg == 0)
		{
			// printf("KILLED HEAD: %i\n", to_rem->data->seg);
			sprites = box->sprites;
			while (sprites)
			{
				if (sprites->data->seg == to_rem->data->seg + 1)
				{
					sprites->data->texture = LARRY_JR_HEAD;
					break;
				}
				sprites = sprites->next;
			}
			sprites = box->sprites;
			while (sprites)
			{
				if (sprites->data->texture == LARRY_JR_HEAD || sprites->data->texture == LARRY_JR_BODY)
					sprites->data->seg--;
				sprites = sprites->next;
			}
		}
		else
		{
			// printf("KILLED SEGMENT: %i\n", to_rem->data->seg);
			sprites = box->sprites;
			while (sprites)
			{
				if (sprites->data->texture == LARRY_JR_BODY && sprites->data->seg > to_rem->data->seg)
				{
					// sprites->data->x = find_seg(box, sprites->data->seg - 1)->data->x;
					// sprites->data->y = find_seg(box, sprites->data->seg - 1)->data->y;
					sprites->data->seg--;
				}
				sprites = sprites->next;
			}

		}
		sprites = box->sprites;
		while (sprites)
		{
			if (sprites->data->texture == LARRY_JR_HEAD || sprites->data->texture == LARRY_JR_BODY)
				sprites->data->n_seg = sprites->data->n_seg - 1;
			sprites = sprites->next;
		}

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
			if (box->map[i][c] == DOOR + 1 + '0')
				sprite_append(box, i, c, DOOR);
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
		t_sprite	*last;
		last = last_sprite(box->sprites);
		if (last->data->texture == LARRY_JR_HEAD)
		{
			// printf("JARRY LUNIOR\n");
			while (last->data->seg++ < last->data->n_seg)
			{
				// printf("JARRY BODY SEG %i\n", last->data->seg);
				sprite_append(box, x + last->data->seg / 3.0, y + last->data->seg / 3.0, LARRY_JR_BODY);
				last_sprite(box->sprites)->data->seg = last->data->seg;
				last_sprite(box->sprites)->data->n_seg = last->data->n_seg;
				last_sprite(box->sprites)->data->start_n_seg = last->data->start_n_seg;
			}
			last->data->seg = 0;
		}
		else if (last->data->texture == ITEMS)
			sprite_append(box, x, y, ITEM_ALTAR);
		// i = -1;
		// printf("\nDUMP:\n");
		// while (++i < box->n_sprites)
		// 	printf("Texture: %i | x: %f | y: %f\n", box->sprites[i].texture, box->sprites[i].x, box->sprites[i].y);
	}
	free(line);
}
