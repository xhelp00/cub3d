/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:52:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/23 15:50:39 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse(int keycode, int x, int y, t_box *box)
{
	int	i;

	(void)x;
	(void)y;
	if (keycode == 1)
	{
		i = 0;
		while (box->sprites[i].texture > 0)
			i++;
		box->sprites[i].texture = 30;
		box->sprites[i].x = box->info.pos_x;
		box->sprites[i].y = box->info.pos_y;
		box->sprites[i].dir_x = box->info.dir_x;
		box->sprites[i].dir_y = box->info.dir_y;
		count_sprites(box);
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
