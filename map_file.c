/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_map_filename(int choice, t_box *box)
{
	if (choice == 1)
		box->map_filename = "maps/hell.cub";
	else if (choice == 2)
		box->map_filename = "maps/arena.cub";
	else if (choice == 3)
		box->map_filename = "maps/exampleTexture.cub";
	else if (choice > 3 && choice < 5)
		printf("Invalid map choice. Please select a valid map number.\n");
}

// Function for initialization and reading the map.
void	initialize_and_read_map(t_box *box, int fd, char **line)
{
	box->map = malloc(sizeof(char *));
	box->map[0] = NULL;
	box->map_width = 0;
	box->map_height = 0;
	*line = get_next_line(fd);
	if (!*line)
	{
		ft_printf("%s\n", "Error map.");
		exit(1);
	}
	while (*line && (*line)[0] && (*line)[0] != '\n')
	{
		box->map = ft_arrappend(box->map, ft_strtrim(*line, "\n"));
		if ((int) ft_strlen(*line) - 1 > box->map_width)
			box->map_width = ft_strlen(*line) - 1;
		*line = (free(*line), get_next_line(fd));
		box->map_height++;
	}
	free(*line);
}

void	check3(t_box *box, char **argv)
{
	if (!suffix_check(argv[1]))
	{
		printf("Error\nWrong map format.\n");
		exit(1);
	}
	box->map_filename = argv[1];
}

void	check_around(t_box *box, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (i == 0 || i == box->map_height - 1 || j == 0
				|| j == box->map_width - 1)
			{
				if (map[i][j] != '1' && map[i][j] != '8' && map[i][j] != '4')
				{
					ft_printf("Error\nInvalid map.\n");
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}
