/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/19 14:11:45 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Count_sprites

	Calculates how many sprites needs to be drawn each redraw
*/
int	count_sprites(t_box *box)
{
	int	i;

	i = 0;
	while (box->sprites[i].x != 0)
		i++;
	return (i);
}

/*	Check

	Basic function for checking inputs
*/
void	check(t_box *box, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (printf("Error\nNo argument supplied.\n"), exit(1));
	fd = open(argv[1], O_RDONLY);
	if (!fd)
		return (printf("Error\nCannot open file.\n"), exit(1));
	init_vals(box);
	parser(box, fd);
	box->n_sprites = count_sprites(box);
	close(fd);
}

/*	Timer

	Function for calculating FPS and redrawing screen every iteration
*/
int	timer(t_box *box)
{
	if (box->timer > 1000000000)
		box->timer = 0;
	box->timer++;
	redraw(box);
	return (0);
}

/*
	struct dirent	*dir;
	struct dirent	*subdir;
	DIR				*pdir;
	DIR				*psubdir;
	char			*tmp;

	pdir = opendir("textures");
	if (!pdir)
		return (printf("Cannot open directory textures\n"), 1);
	dir = readdir(pdir);
	while (dir)
	{
		if (ft_strchr(dir->d_name, '.') && dir->d_name[0] != '.')
			printf("Im a file [%s]\n", dir->d_name);
		else if (dir->d_name[0] != '.')
		{
			printf("Im a folder [%s]\n", dir->d_name);
			tmp = ft_strjoin("textures/", dir->d_name);
			psubdir = opendir(tmp);
			free(tmp);
			if (!psubdir)
				return (printf("Cannot open directory %s\n", dir->d_name), 1);
			subdir = readdir(psubdir);
			while (subdir)
			{
				if (ft_strchr(subdir->d_name, '.') && subdir->d_name[0] != '.')
					printf("Im a file [%s/%s]\n", dir->d_name, subdir->d_name);
				subdir = readdir(psubdir);
			}
			closedir(psubdir);
		}
		dir = readdir(pdir);
	}
	closedir(pdir);
*/

int	main(int argc, char **argv)
{
	t_box			box;

	check(&box, argc, argv);
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	init_textures(&box);
	box.image.img = mlx_new_image(box.mlx, SCREENWIDTH, SCREENHEIGHT);
	box.image.addr = (unsigned char *)mlx_get_data_addr(box.image.img,
			&box.image.bits_pp, &box.image.line_len, &box.image.endian);
	redraw(&box);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L << 0, key_press, &box);
	mlx_hook(box.win, 3, 1L << 1, key_release, &box);
	mlx_loop_hook(box.mlx, timer, &box);
	mlx_loop(box.mlx);
	return (0);
}

void print_map_contents(t_box *box)
{
    for (int i = 0; i < box->map_height; i++)
    {
        for (int j = 0; j < box->map_width; j++)
        {
            printf("%c ", box->map[i][j]);
        }
        printf("\n");
    }
}

void fill_buffer_with_color(unsigned char *buffer, int width, int height, int color)
{
    int x, y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            int pixel_pos = y * width + x;
            buffer[pixel_pos * 4] = color & 0xFF;            // Blue channel
            buffer[pixel_pos * 4 + 1] = (color >> 8) & 0xFF;  // Green channel
            buffer[pixel_pos * 4 + 2] = (color >> 16) & 0xFF; // Red channel
            buffer[pixel_pos * 4 + 3] = (color >> 24) & 0xFF; // Alpha channel
        }
    }
}

void single_square_test(t_box *box) {
    t_rect rect;

    char grid_item = box->map[0][0];  // Just picking the top-left item as a test
    
    rect.x = 300;
    rect.y = 400;
    rect.width = 20;
    rect.height = 20;
    rect.border_color = 0x0014213d;
    rect.border_width = 0;
    rect.fill_color = get_fill_color(grid_item);
    printf("Calling single_square_test\n");
    draw_rect(&rect, box->image.addr, SCREENWIDTH, box);
}