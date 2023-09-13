/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <jbartosi@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:23:13 by jbartosi          #+#    #+#             */
/*   Updated: 2023/09/13 16:45:01 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_ene_move(t_box *box)
{
	int		i;
	float	speed;

	i = -1;
	speed = 0.05;
	while (++i < box->n_sprites)
	{
		/*
		if (box->sprites[i].texture == 10)
		{
			if (box->sprites[i].x < box->info.pos_x)
				box->sprites[i].x += 0.01;
			if (box->sprites[i].x > box->info.pos_x)
				box->sprites[i].x -= 0.01;
			if (box->sprites[i].y < box->info.pos_y)
				box->sprites[i].y += 0.01;
			if (box->sprites[i].y > box->info.pos_y)
				box->sprites[i].y -= 0.01;
		}
		*/
	/*
		if (box->sprites[i].texture == 12)
		{
			if (box->map[(int)(box->sprites[i].x + speed)][(int)(box->sprites[i].y)] == '0')
				box->sprites[i].x += speed;
			else if (box->map[(int)(box->sprites[i].x)][(int)(box->sprites[i].y + speed)] == '0')
				box->sprites[i].y += speed;
			else if (box->map[(int)(box->sprites[i].x - speed)][(int)(box->sprites[i].y)] == '0')
				box->sprites[i].x -= speed;
			else if (box->map[(int)(box->sprites[i].x)][(int)(box->sprites[i].y - speed)] == '0')
				box->sprites[i].y -= speed;
		}
	*/
	}
}
