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

// void	menu(t_box *box)
// {
// 	int		choice;

// 	do
// 	{
// 		printf("                                                     \n");
// 		printf("                       _|         _|_|_|     _|_|_|  \n");
// 		printf("   _|_|_|   _|    _|   _|_|_|           _|   _|    _|\n");
// 		printf(" _|         _|    _|   _|    _|     _|_|     _|    _|\n");
// 		printf(" _|         _|    _|   _|    _|         _|   _|    _|\n");
// 		printf("   _|_|_|     _|_|_|   _|_|_|     _|_|_|     _|_|_|  \n");
// 		printf("                                                     \n");
// 		printf("    42 project presented by jbartosi & phelebra      \n");
// 		printf("                                                     \n");
// 		printf("        ██╗███████╗ █████╗  █████╗  ██████╗          \n");
// 		printf("        ██║██╔════╝██╔══██╗██╔══██╗██╔════╝          \n");
// 		printf("        ██║███████╗███████║███████║██║               \n");
// 		printf("        ██║╚════██║██╔══██║██╔══██║██║               \n");
// 		printf("        ██║███████║██║  ██║██║  ██║╚██████╗          \n");
// 		printf("        ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝     v1.0 \n");
// 		printf("                                                     \n");
// 		printf("Terminal Menu:\n");
// 		printf("1. Choose map hell\n");
// 		printf("2. Choose map arena\n");
// 		printf("3. Choose map exampleTexture\n");
// 		printf("4. Exit\n");
// 		printf("5. Toggle Music On/Off\n");
//         printf("Enter your choice (1-4): ");

//         if (scanf("%d", &choice) != 1)
//         {
//             // Clear the input buffer if scanf() failed
//             while (getchar() != '\n');
//             continue; // Continue to the next iteration to re-display the menu
//         }

//         switch(choice)
//         {
//             case 1:
//                 box->map_filename = "maps/hell.cub";
//                 return;
// 			case 2:
//                 box->map_filename = "maps/arena.cub";
//                 return;
//             case 3:
//                 box->map_filename = "maps/exampleTexture.cub";
//                 return;
//             case 4:
//                 printf("Exiting...\n");
//                 exit(0);
//                 break;
//             case 5:
//                 if (box->music)
//                 {
//                     // Stop the music. You need a function to handle this.
//                     box->music = 0;
//                     printf("Music turned off.\n");
//                 }
//                 else
//                 {
//                     // Start the music
//                     box->music = 1;
//                     printf("Music turned on.\n");
//                 }
//                 break;
//             default:
//                 printf("Invalid choice. Please enter a number between 1 and 4.\n");
//         }
//     } while(1); // Infinite loop, since we handle exit explicitly with options.
// }


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

// /*	Check

// 	Basic function for checking inputs
// */
// void	check(t_box *box, int argc, char **argv)
// {
// 	int	fd;
// 	char* map_path;

// 	if (argc == 1)
// 	{
// 		menu(box);
// 		if (!box->map_filename)
// 		{
// 			printf("Error\nNo map selected.\n");
// 			exit(1);
// 		}
// 		map_path = box->map_filename;
// 	}
// 	else if (argc == 2)
// 	{
// 		map_path = argv[1];
// 	}
// 	else
// 	{
// 		printf("Error\nInvalid number of arguments.\n");
// 		exit(1);
// 	}

// 	fd = open(map_path, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error\nCannot open map file.\n");
// 		exit(1);
// 	}
// 	init_vals(box);
// 	parser(box, fd);
// 	close(fd);
// }

/*	Timer

	Function for calculating FPS and redrawing screen every iteration
*/
int	timer(t_box *box)
{
	gettimeofday(&box->time, NULL);
	if (!box->won && !box->lost)
	{
		if (box->title_menu)
		{
			if (box->mouse_hidden)
			{
				mlx_mouse_show(box->mlx, box->win);
				box->mouse_hidden = 0;
			}
			my_mlx_put_image_to_window(box, &box->textures[TITLE_MENU], 0, 0, -1);
			gettimeofday(&box->time, NULL);
			if (((int)((box->time.tv_usec / 100000.0) * 4) / 10) % 2 == 1)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 400, 215, 0, 1000, 450, 450); //press start
			else
				mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 400, 215, 432, 1000, 450, 450); //press start 2
			if (((int)((box->time.tv_usec / 100000.0) * 8) / 10) % 2 == 1)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 1000, 400, 950, 1030, 200, 200); //fly
			else
				mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 1000, 400, 950, 1250, 200, 200); //fly 2
			if (((int)((box->time.tv_usec / 100000.0) * 4) / 10) / 2 == 0)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 275, -10 + ((int)((box->time.tv_usec / 100000.0) * 20) / 10), 280, 740, 800, 300); //logo going down
			else
				mlx_put_image_to_window(box->mlx, box->win, box->textures[TITLE_MENU].img, 275, 10 - ((int)((box->time.tv_usec / 100000.0) * 20) / 10), 280, 740, 800, 300); //logo going up
		}
		else if (!box->pause_menu && box->options_menu)
		{
			my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 400, 100, 0, 0, 460, 480);
			mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 500, 200, 0, 480, 100, 40); //SFX
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 500, 260, 0, 920, 100, 40); //MUSIC

			if (box->options_menu_choice == 1)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 450, 200, 460, 50, 100, 100); //SFX HIGHLIGTH
			else if (box->options_menu_choice == 2)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 450, 260, 460, 50, 100, 100); //MUSIC HIGHLIGTH

			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 650, 200, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.sfx_volume))), 150, 32); //SFX VOLUME SLIDER

			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU].img, 650, 260, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.music_volume))), 150, 32); //MUSIC VOLUME SLIDER
		}
		else if (box->start_menu)
		{
			if (box->mouse_hidden)
			{
				mlx_mouse_show(box->mlx, box->win);
				box->mouse_hidden = 0;
			}
			my_mlx_put_image_to_window(box, &box->textures[MENU_BACK], 0, 0, -1);
			my_mlx_put_image_to_window(box, &box->textures[START_MENU], 0, 0, -1);
			mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 120, 80, 800, 310, 100); //NEW RUN
			if (box->sprites)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 200, 80, 920, 310, 100); //CONTINUE
			else
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 200, 420, 920, 310, 100); //CONTINUE GRAYED OUT
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 500, 280, 80, 1040, 330, 110); //CHALLANGE
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 510, 370, 80, 1160, 330, 110); //STATS
			mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 520, 440, 80, 1280, 340, 150); //OPTIONS
			if (box->start_menu_choice == 1)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 430, 120, 20, 800, 50, 100);
			else if (box->start_menu_choice == 2)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 440, 210, 20, 800, 50, 100);
			else if (box->start_menu_choice == 3)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 455, 300, 20, 800, 50, 100);
			else if (box->start_menu_choice == 4)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 470, 390, 20, 800, 50, 100);
			else if (box->start_menu_choice == 5)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[START_MENU].img, 480, 480, 20, 800, 50, 100);
		}
		else if (box->pause_menu && box->options_menu)
		{
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 400, 100, 0, 0, 460, 480);
			mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 500, 200, 0, 480, 100, 40); //SFX
			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 500, 260, 0, 920, 100, 40); //MUSIC

			if (box->options_menu_choice == 1)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 450, 200, 460, 50, 100, 100); //SFX HIGHLIGTH
			else if (box->options_menu_choice == 2)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 450, 260, 460, 50, 100, 100); //MUSIC HIGHLIGTH

			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 650, 200, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.sfx_volume))), 150, 32); //SFX VOLUME SLIDER

			mlx_put_image_to_window(box->mlx, box->win, box->textures[OPTIONS_MENU_DARK].img, 650, 260, 390, 480 + (32 * (int)(10 *  (1.0 - box->sound.music_volume))), 150, 32); //MUSIC VOLUME SLIDER
		}
		else if (box->pause_menu)
		{
			if (box->mouse_hidden)
			{
				mlx_mouse_show(box->mlx, box->win);
				box->mouse_hidden = 0;
			}
			mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 400, 150, 0, 0, 480, 480);
			mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
			if (box->pause_menu_choice == 1)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 500, 390, 475, 5, 30, 30);
			else if (box->pause_menu_choice == 2)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 480, 440, 475, 5, 30, 30);
			else if (box->pause_menu_choice == 3)
				mlx_put_image_to_window(box->mlx, box->win, box->textures[PAUSE_MENU].img, 505, 485, 475, 5, 30, 30);
		}
		else
		{
			if (!box->mouse_hidden)
			{
				mlx_mouse_hide(box->mlx, box->win);
				mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
				box->mouse_hidden = 1;
			}
			mlx_mouse_get_pos(box->mlx, box->win, &box->mouse.x, &box->mouse.y);
			mlx_mouse_move(box->mlx, box->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);

				redraw(box);

		}
	}
	else if (box->lost)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img, 400, 100, 400, 0, 512, 512); //DEATH NOTE
		mlx_put_image_to_window(box->mlx, box->win, box->textures[GRIM].img, 650, 300, 64, 64, 64, 64); //POOP
		if (box->player.frame > 85)
			exit_hook(box);
	}
	else if (box->win)
	{
		box->player.frame = ((((box->time.tv_sec - box->fin_time.tv_sec) + ((box->time.tv_usec - box->fin_time.tv_usec) / 1000000.0)) * 10) * 16) / 10;
		my_mlx_put_image_to_window(box, &box->textures[WIN], 400, 100, -1);
		if (box->player.frame > 115)
			exit_hook(box);
	}
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

int	main(void)
{
	t_box			box;

	init_vals(&box);
	// check(&box, argc, argv);
	box.mlx = mlx_init();
	box.win = mlx_new_window(box.mlx, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	init_textures(&box);
	new_image(box.mlx, &box.image, SCREENWIDTH, SCREENHEIGHT);
	new_image(box.mlx, &box.shaders, SCREENWIDTH, SCREENHEIGHT);
	init_sounds(&box);
	// redraw(&box);
	// box.env = env;
	// if (box.music)
	// 	box.pid = music(env, "sounds/Isaac.mp3");
	// mlx_mouse_move(box.mlx, box.win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	// mlx_mouse_hide(box.mlx, box.win);
	mlx_hook(box.win, 17, 0, exit_hook, &box);
	mlx_hook(box.win, 2, 1L << 0, key_press, &box);
	mlx_hook(box.win, 3, 1L << 1, key_release, &box);
	mlx_hook(box.win, 4, 1L << 2, mouse_press, &box);
	mlx_hook(box.win, 5, 1L << 3, mouse_release, &box);
	mlx_hook(box.win, 6, 1L << 6, mouse_move, &box);
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
