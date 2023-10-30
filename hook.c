/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 18:52:55 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:04:56 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_press(int keycode, int x, int y, t_box *box)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		box->player.cry = 1;
	if (keycode == 3)
		action_door(box);
	return (0);
}

int	mouse_release(int keycode, int x, int y, t_box *box)
{
	(void)x;
	(void)y;
	if (keycode == 1)
		box->player.cry = 0;
	return (0);
}

void	handle_rotate(int key, t_box *box)
{
	if (key == 113)
		box->info.rotate = -1;
	if (key == 101)
		box->info.rotate = 1;
}

void	handle_move(int key, t_box *box)
{
	if (key == 119 || key == 65362)
		box->info.move_x = 1;
	if (key == 115 || key == 65364)
		box->info.move_x = -1;
	if (key == 97 || key == 65361)
		box->info.move_y = -1;
	if (key == 100 || key == 65363)
		box->info.move_y = 1;
}

void	handle_position_adjustment(int key, t_box *box)
{
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
}

void	toggle_hud(int key, t_box *box)
{
	if (key == 65477)
	{
		box->hud = !box->hud;
	}
}

void	handle_input_buffer(int key, t_box *box)
{
	if (key >= 'a' && key <= 'z')
	{
		box->input_buffer[box->input_index] = (char)key;
		box->input_index++;
		box->input_buffer[box->input_index] = '\0';
		if (strstr(box->input_buffer, "iddqd"))
		{
			printf("GOD MODE active\n");
			box->god = 1;
			ft_memset(box->input_buffer, 0, sizeof(box->input_buffer));
			box->input_index = 0;
		}
		else if (box->input_index >= (int) sizeof(box->input_buffer) - 1)
		{
			ft_memmove(box->input_buffer, box->input_buffer + 1,
				sizeof(box->input_buffer) - 1);
			box->input_index--;
		}
	}
}

int	key_press(int key, t_box *box)
{
	if (box->won || box->lost)
		return (0);
	handle_rotate(key, box);
	handle_move(key, box);
	handle_position_adjustment(key, box);
	toggle_hud(key, box);
	handle_input_buffer(key, box);
	return (0);
}

/*	Key_release

	Processes let up key
*/
int	key_release(int key, t_box *box)
{
	if (key == 65307)
	{
		exit_hook(box);
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
	return (0);
}

/*	Exit_hook

	Closes the window when the x in the corner is pressed
*/
int	exit_hook(t_box *box)
{
	if (box->pid > 0)
	{
		if (kill(box->pid, SIGTERM) == -1)
			perror("Failed to terminate child process");
	}
	mlx_destroy_window(box->mlx, box->win);
	exit(0);
}
