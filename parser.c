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
