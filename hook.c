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

	//IDDQD for god mode
	if (key >= 'a' && key <= 'z')  // Assuming ASCII values
	{
		// Assign the character to the buffer
		box->input_buffer[box->input_index] = (char)key;
		box->input_index++;
		box->input_buffer[box->input_index] = '\0'; // Null terminate

		// Using strstr to check for "iddqd" in the buffer
		if (strstr(box->input_buffer, "iddqd"))
		{
			printf("GOD MODE active\n");
			box->god = 1;
			// Reset the buffer after detecting the code
			ft_memset(box->input_buffer, 0, sizeof(box->input_buffer));
			box->input_index = 0;
		}
		else if (box->input_index >= (int)sizeof(box->input_buffer) - 1) // If buffer is full
		{
			// Shift the buffer to the left by one character
			ft_memmove(box->input_buffer, box->input_buffer + 1, sizeof(box->input_buffer) - 1);
			box->input_index--;
		}
	}
	//printf("Key pressed: %c, Current buffer: %s\n", (char)key, box->input_buffer);	s
	return (0);
}

/*	Key_release

	Processes let up key
*/
int	key_release(int key, t_box *box)
{
	if (key == 65307)
	{
		//mlx_destroy_window(box->mlx, box->win);
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
	// printf("Key released: %i\n", key);
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
		{
        	perror("Failed to terminate child process");
    	}
		//waitpid(box.pid, NULL, 0);  // This waits for the child to terminate
	}

	mlx_destroy_window(box->mlx, box->win);
	exit(0);
}
