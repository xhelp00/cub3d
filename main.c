/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	menu(t_box *box)
{
	int		choice;

	do
	{
		printf("                                                     \n");
		printf("                       _|         _|_|_|     _|_|_|  \n");
		printf("   _|_|_|   _|    _|   _|_|_|           _|   _|    _|\n");
		printf(" _|         _|    _|   _|    _|     _|_|     _|    _|\n");
		printf(" _|         _|    _|   _|    _|         _|   _|    _|\n");
		printf("   _|_|_|     _|_|_|   _|_|_|     _|_|_|     _|_|_|  \n");
		printf("                                                     \n");
		printf("    42 project presented by jbartosi & phelebra      \n");
		printf("                                                     \n");
		printf("        ██╗███████╗ █████╗  █████╗  ██████╗          \n");
		printf("        ██║██╔════╝██╔══██╗██╔══██╗██╔════╝          \n");
		printf("        ██║███████╗███████║███████║██║               \n");
		printf("        ██║╚════██║██╔══██║██╔══██║██║               \n");
		printf("        ██║███████║██║  ██║██║  ██║╚██████╗          \n");
		printf("        ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝     v1.0 \n");
		printf("                                                     \n");
		printf("Terminal Menu:\n");
		printf("1. Choose map 1\n");
		printf("2. Choose map 2\n");
		printf("3. Exit\n");
		printf("4. Toggle Music On/Off\n");
        printf("Enter your choice (1-4): ");

        if (scanf("%d", &choice) != 1)
        {
            // Clear the input buffer if scanf() failed
            while (getchar() != '\n');
            continue; // Continue to the next iteration to re-display the menu
        }

        switch(choice)
        {
            case 1:
                box->map_filename = "maps/arena.cub";
                return;
            case 2:
                box->map_filename = "maps/exampleTexture.cub";
                return;
            case 3:
                printf("Exiting...\n");
                exit(0);
                break;
            case 4:
                if (box->music)
                {
                    // Stop the music. You need a function to handle this.
                    box->music = 0;
                    printf("Music turned off.\n");
                }
                else
                {
                    // Start the music
                    box->music = 1;
                    printf("Music turned on.\n");
                }
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    } while(1); // Infinite loop, since we handle exit explicitly with options.
}


/* Count_sprites

	Calculates how many sprites needs to be drawn each redraw
*/
int	count_sprites(t_box *box)
{
	int			counter;
	t_sprite	*sprites;

	sprites = box->sprites;
	if (!sprites)
		return (0);
	counter = 1;
	while (sprites->next)
	{
		sprites = sprites->next;
		counter++;
	}
	return (counter);
}

/*	Check

	Basic function for checking inputs
*/
void	check(t_box *box, int argc, char **argv)
{
	int	fd;
	char* map_path;

	if (argc == 1)
	{
		menu(box);
		if (!box->map_filename)
		{
			printf("Error\nNo map selected.\n");
			exit(1);
		}
		map_path = box->map_filename;
	}
	else if (argc == 2)
	{
		map_path = argv[1];
	}
	else
	{
		printf("Error\nInvalid number of arguments.\n");
		exit(1);
	}

	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open map file.\n");
		exit(1);
	}
		init_vals(box);
		parser(box, fd);
		close(fd);
}

/*	Timer

	Function for calculating FPS and redrawing screen every iteration
*/
int	timer(t_box *box)
{
	mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
	mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	/* while (box->info.angry && !box->info.sound)
	{
		printf("YOU ARE DEAD!!!\n");
		exit(0);
	}*/
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

int	main(int argc, char **argv, char **env)
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
	box.env = env;
	if (box.music)
		box.pid = music(env, "sounds/Isaac.mp3");
	mlx_mouse_move(box.mlx, box.win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	mlx_mouse_hide(box.mlx, box.win);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L << 0, key_press, &box);
	mlx_hook(box.win, 3, 1L << 1, key_release, &box);
	mlx_hook(box.win, 4, 1L << 2, mouse_press, &box);
	mlx_hook(box.win, 5, 1L << 3, mouse_release, &box);
	mlx_loop_hook(box.mlx, timer, &box);
	mlx_loop(box.mlx);
	return (0);
}

//***testing stuff below to be removed***s//

// void print_map_contents(t_box *box)
// {
//     for (int i = 0; i < box->map_height; i++)
//     {
//         for (int j = 0; j < box->map_width; j++)
//         {
//             printf("%c ", box->map[i][j]);
//         }
//         printf("\n");
//     }
// }

// void fill_buffer_with_color(unsigned char *buffer, int width, int height, int color)
// {
//     int x, y;
//     for (y = 0; y < height; y++)
//     {
//         for (x = 0; x < width; x++)
//         {
//             int pixel_pos = y * width + x;
//             buffer[pixel_pos * 4] = color & 0xFF;            // Blue channel
//             buffer[pixel_pos * 4 + 1] = (color >> 8) & 0xFF;  // Green channel
//             buffer[pixel_pos * 4 + 2] = (color >> 16) & 0xFF; // Red channel
//             buffer[pixel_pos * 4 + 3] = (color >> 24) & 0xFF; // Alpha channel
//         }
//     }
// }

// void single_square_test(t_box *box) {
//     t_rect rect;

//     char grid_item = box->map[0][0];  // Just picking the top-left item as a test

//     rect.x = 300;
//     rect.y = 400;
//     rect.width = 20;
//     rect.height = 20;
//     rect.border_color = 0x0014213d;
//     rect.border_width = 0;
//     rect.fill_color = get_fill_color(grid_item);
//     printf("Calling single_square_test\n");
//     draw_rect(&rect, box);
// }
