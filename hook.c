/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:52:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/25 14:55:38 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse(int keycode, int x, int y, t_box *box)
{
	(void)x;
	(void)y;
	if (keycode == 1)
	{
		sprite_append(box, box->info.pos_x, box->info.pos_y, 30);
		// printf("\e[0;36mAdded tear to index %i\e[0m\n", box->n_sprites);
		box->sprites[box->n_sprites - 1].dir_x = box->info.dir_x;
		box->sprites[box->n_sprites - 1].dir_y = box->info.dir_y;
		// printf("\e[0;32mNumber of sprites after adding %i\e[0m\n", box->n_sprites);
	}
	return (0);
}

/*	Key_press

	Processes pressed down key
*/
int	key_press(int key, t_box *box)
{
	if (key == 113)
		box->info.rotate = -1;
	if (key == 101)
		box->info.rotate = 1;
	if (key == 119 || key == 65362)
		box->info.move_x = 1;
	if (key == 115 || key == 65364)
		box->info.move_x = -1;
	if (key == 97 || key == 65361)
		box->info.move_y = -1;
	if (key == 100 || key == 65363)
		box->info.move_y = 1;
	if (key == 65505)
		box->info.sprint = 1;
	if (key == 65365)
		box->info.up_down = 1;
	if (key == 65366)
		box->info.up_down = -1;
	if (key == 32)
		box->info.pos_z = 200;
	if (key == 65507)
		box->info.pos_z = -200;
	return (0);
}

/*	Key_release

	Processes let up key
*/
int	key_release(int key, t_box *box)
{
	if (key == 65307)
	{
		mlx_destroy_window(box->mlx, box->win);
		exit(0);
	}
	if (key == 113)
		box->info.rotate = 0;
	if (key == 101)
		box->info.rotate = 0;
	if (key == 119 || key == 65362)
		box->info.move_x = 0;
	if (key == 115 || key == 65364)
		box->info.move_x = 0;
	if (key == 97 || key == 65361)
		box->info.move_y = 0;
	if (key == 100 || key == 65363)
		box->info.move_y = 0;
	if (key == 65505)
		box->info.sprint = 0;
	if (key == 65365 || key == 65366)
		box->info.up_down = 0;
	if (key == 65507)
		box->info.pos_z = 0;
	// printf("Key released: %i\n", key);
	return (0);
}

/*	Exit_hook

	Closes the window when the x in the corner is pressed
*/
int	exit_hook(t_box *box)
{
	mlx_destroy_window(box->mlx, box->win);
	exit(0);
}
