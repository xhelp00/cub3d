/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <phelebra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:46:15 by phelebra          #+#    #+#             */
/*   Updated: 2023/09/14 17:54:43 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void drawMinimap(t_box *box)
{
	my_mlx_pyxel_put(&box->image, SCREENWIDTH - 10, SCREENHEIGHT -10, 987130);
}
	