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

int	mouse_move(int x, int y, t_box *box)
{
	if (!box->start_menu && !box->title_menu && box->pause_menu && !box->options_menu)
	{
		if (x > 540 && x < 740 && y > 380 && y < 420)
			box->pause_menu_choice = 1;
		else if (x > 520 && x < 760 && y > 440 && y < 470)
			box->pause_menu_choice = 2;
		else if (x > 540 && x < 740 && y > 480 && y < 520)
			box->pause_menu_choice = 3;
		else
			box->pause_menu_choice = 0;
	}
	else if (box->start_menu && !box->title_menu && !box->pause_menu && !box->options_menu)
	{
		if (x > 490 && x < 790 && y > 130 && y < 190)
			box->start_menu_choice = 1;
		else if (x > 500 && x < 790 && y > 230 && y < 280)
			box->start_menu_choice = 2;
		else if (x > 510 && x < 820 && y > 320 && y < 370)
			box->start_menu_choice = 3;
		else if (x > 530 && x < 740 && y > 410 && y < 460)
			box->start_menu_choice = 4;
		else if (x > 540 && x < 800 && y > 500 && y < 560)
			box->start_menu_choice = 5;
		else
			box->start_menu_choice = 0;
	}
	else if (!box->title_menu && box->options_menu)
	{
		if (x > 490 && x < 790 && y > 200 && y < 240)
			box->options_menu_choice = 1;
		else if (x > 490 && x < 790 && y > 250 && y < 290)
			box->options_menu_choice = 2;
		else
			box->options_menu_choice = 0;
	}
	return (0);
}

int	mouse_press(int keycode, int x, int y, t_box *box)
{
	if (!box->start_menu && !box->title_menu && !box->pause_menu && !box->options_menu)
	{
		if (keycode == 1)
			box->player.cry = 1;
		if (keycode == 3)
			action_door(box);
	}
	else if (!box->start_menu && !box->title_menu && box->pause_menu && !box->options_menu)
	{
		if (x > 540 && x < 740 && y > 380 && y < 420 && keycode == 1)
			box->options_menu = 1;
		else if (x > 520 && x < 760 && y > 440 && y < 470 && keycode == 1)
		{
			box->pause_menu = 0;
			gettimeofday(&box->time, NULL);
		}
		else if (x > 540 && x < 740 && y > 480 && y < 520 && keycode == 1)
		{
			box->pause_menu = 0;
			box->options_menu = 0;
			box->start_menu = 1;
		}
	}
	else if (box->start_menu && !box->title_menu && !box->pause_menu && !box->options_menu)
	{
		if (x > 490 && x < 790 && y > 130 && y < 190 && keycode == 1)
		{
			if (box->sprites != NULL)
			{
				free_sprites(box);
				free_map(box);
				init_vals(box);
			}
			int fd;
			fd = open("maps/hell.cub", O_RDONLY);
			parser(box, fd);
			close(fd);
			box->start_menu = 0;
			gettimeofday(&box->time, NULL);
		}
		else if (x > 500 && x < 790 && y > 230 && y < 280 && keycode == 1)
		{
			if (box->sprites)
			{
				box->start_menu = 0;
				gettimeofday(&box->time, NULL);
			}
		}
		else if (x > 510 && x < 820 && y > 320 && y < 370 && keycode == 1)
			printf("CHALLANGES\n");
		else if (x > 530 && x < 740 && y > 410 && y < 460 && keycode == 1)
			printf("STATS\n");
		else if (x > 540 && x < 800 && y > 500 && y < 560 && keycode == 1)
			box->options_menu = 1;
	}
	else if (!box->title_menu && box->options_menu)
	{
		if (y > 200 && y < 240 && keycode == 1)
		{
			if (x > 490 && x < 580)
			{
				if (box->sound.sfx_volume == 0)
					box->sound.sfx_volume = 1;
				else
					box->sound.sfx_volume = 0;
			}
			if (x > 650 && x < 770)
				box->sound.sfx_volume = (float)(x - 650) / (float)120;
			sound_play(box, &box->sound.sfx[OW]);
		}
		else if (y > 250 && y < 290 && keycode == 1)
		{
			if (x > 490 && x < 600)
			{
				if (box->sound.music_volume == 0)
					box->sound.music_volume = 1;
				else
					box->sound.music_volume = 0;
			}
			if (x > 650 && x < 770)
				box->sound.music_volume = (float)(x - 650) / (float)120;
			cs_set_volume(box->sound.playing[0].play, box->sound.music_volume, box->sound.music_volume);
		}
	}
	if (!box->start_menu && box->title_menu && !box->pause_menu && !box->options_menu && keycode == 1)
	{
		box->title_menu = 0;
		box->start_menu = 1;
	}
	// printf("X %i Y %i\n", x, y);
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
	if (!box->title_menu && !box->start_menu && !box->pause_menu && !box->options_menu)
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
		if (key == 65477)
		{
			if (box->hud)
				box->hud = 0;
			else
				box->hud = 1;
		}
	}
	if ((key == 32 || key == 65293) && box->title_menu && !box->start_menu && !box->pause_menu && !box->options_menu)
	{
		box->title_menu = 0;
		box->start_menu = 1;
	}

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
	// printf("Key pressed: %c, Current buffer: %s\n", (char)key, box->input_buffer);
	// printf("Key released: %i\n", key);
	return (0);
}

/*	Key_release

	Processes let up key
*/
int	key_release(int key, t_box *box)
{
	if (key == 65307)
	{
		if (!box->start_menu && !box->title_menu && !box->pause_menu && !box->options_menu)
			box->pause_menu = 1;
		else if (!box->start_menu && !box->title_menu && box->pause_menu && !box->options_menu)
		{
			box->pause_menu = 0;
			box->options_menu = 0;
			gettimeofday(&box->time, NULL);
		}
		else if (!box->start_menu && !box->title_menu && box->pause_menu && box->options_menu)
		{
			box->options_menu = 0;
			gettimeofday(&box->time, NULL);
			box->mouse.x = SCREENWIDTH / 2;
			box->mouse.y = SCREENHEIGHT / 2;
			redraw(box);
		}
		else if (box->start_menu && !box->title_menu && !box->pause_menu && box->options_menu)
			box->options_menu = 0;
		else if (box->start_menu && !box->title_menu && !box->pause_menu && !box->options_menu)
		{
			box->start_menu = 0;
			box->title_menu = 1;
		}
		else if (!box->start_menu && box->title_menu && !box->pause_menu && !box->options_menu)
			exit_hook(box);
		//mlx_destroy_window(box->mlx, box->win);
		// exit_hook(box);
		// exit(0);
	}
	if (!box->title_menu && !box->start_menu && !box->pause_menu && !box->options_menu)
	{
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
	}
	// printf("Key released: %i\n", key);
	return (0);
}

/*	Exit_hook

	Closes the window when the x in the corner is pressed
*/
int	exit_hook(t_box *box)
{

	// if (box->pid > 0)
	// {
	// 	if (kill(box->pid, SIGTERM) == -1)
	// 	{
    //     	perror("Failed to terminate child process");
    // 	}
	// 	//waitpid(box.pid, NULL, 0);  // This waits for the child to terminate
	// }

	free_stuff(box);
	exit(0);
}
