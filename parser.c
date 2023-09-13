/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 18:29:34 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/06 14:19:49 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	line = get_next_line(fd);
	while (line[0] != '\n')
	{
		box->map = ft_arrappend(box->map, ft_strtrim(line, "\n"));
		if ((int) ft_strlen(line) - 1 > box->map_width)
			box->map_width = ft_strlen(line) - 1;
		line = (free(line), get_next_line(fd));
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
			free(box->map[i]);
			box->map[i] = tmp;
		}
	}
	box->sprites = malloc(100 * sizeof(t_sprite));
	i = 0;
	while (i < 100)
	{
		box->sprites[i].x = 0;
		box->sprites[i].y = 0;
		box->sprites[i++].texture = 0;
	}
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		s = 0;
		box->sprites[i].x = atof(line);
		while (line[s] != ',' && line[s] != '\n')
			s++;
		s++;
		box->sprites[i].y = atof(line + s);
		while (line[s] != ',' && line[s] != '\n')
			s++;
		s++;
		box->sprites[i].texture = ft_atoi(line + s);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	free(line);
}
