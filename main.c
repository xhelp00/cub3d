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
void	check2(t_box *box)
{
	menu(box);
	if (!box->map_filename)
	{
		printf("Error\nNo map selected.\n");
		exit(1);
	}
}

void	check(t_box *box, int argc, char **argv)
{
	int		fd;

	box->exit_menu = 0;
	box->map_filename = NULL;
	if (argc == 1)
		check2(box);
	else if (argc == 2)
	{
		box->map_filename = argv[1];
	}
	else
	{
		printf("Error\nInvalid number of arguments.\n");
		exit(1);
	}
	fd = open(box->map_filename, O_RDONLY);
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
	redraw(box);
	return (0);
}

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
