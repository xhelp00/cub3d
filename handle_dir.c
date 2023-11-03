/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:50:14 by jbartosi          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:02 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_direction_n(t_box *box, int i, int c)
{
	box->map[i][c] = '0';
}

void	handle_direction_s(t_box *box, int i, int c)
{
	box->info.rot_speed = 3.143;
	box->info.rotate = 1;
	box->mouse.x = SCREENWIDTH / 2;
	box->mouse.y = SCREENHEIGHT / 2;
	cal_move(box);
	box->info.rotate = 0;
	box->map[i][c] = '0';
}

void	handle_direction_e(t_box *box, int i, int c)
{
	box->info.rot_speed = 1.5715;
	box->info.rotate = 1;
	box->mouse.x = SCREENWIDTH / 2;
	box->mouse.y = SCREENHEIGHT / 2;
	cal_move(box);
	box->info.rotate = 0;
	box->map[i][c] = '0';
}

void	handle_direction_w(t_box *box, int i, int c)
{
	box->info.rot_speed = 1.5715;
	box->info.rotate = -1;
	box->mouse.x = SCREENWIDTH / 2;
	box->mouse.y = SCREENHEIGHT / 2;
	cal_move(box);
	box->info.rotate = 0;
	box->map[i][c] = '0';
}
