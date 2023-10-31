/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
