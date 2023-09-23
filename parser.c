/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/23 18:27:13 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_append(t_box *box, float x, float y, int texture)
{
	t_sprite	*new;
	int			i;

	new = (t_sprite *) malloc(sizeof(t_sprite) * (box->n_sprites + 1));
	i = -1;
	while (++i < box->n_sprites)
	{
		new[i].x = box->sprites[i].x;
		new[i].y = box->sprites[i].y;
		new[i].texture = box->sprites[i].texture;
		new[i].dir_x = box->sprites[i].dir_x;
		new[i].dir_y = box->sprites[i].dir_y;
	}
	new[i].x = x;
	new[i].y = y;
	new[i].texture = texture;
	new[i].dir_x = 0;
	new[i].dir_y = 0;
	free(box->sprites);
	box->sprites = new;
	box->n_sprites++;
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
	box->sprites = malloc(sizeof(t_sprite));
	box->sprites = NULL;
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
		printf("%s\n%f | %f | %i\n", "ADDING SPRITE IN PROGRESS!!!!", x, y, texture);
		sprite_append(box, x, y, texture);
		i = -1;
		printf("\nDUMP:\n");
		while (++i < box->n_sprites)
			printf("Texture: %i | x: %f | y: %f\n", box->sprites[i].texture, box->sprites[i].x, box->sprites[i].y);
	}
	free(line);
}
