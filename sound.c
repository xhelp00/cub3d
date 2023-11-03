/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:43:58 by phelebra          #+#    #+#             */
/*   Updated: 2023/10/16 16:05:25 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*g_player;
#ifdef __linux__

char	*g_player = "/usr/bin/mpg123";

#elif __APPLE__

char	*g_player = "/Users/helebrant/.brew/bin/mpg123";

#endif

int	music(char **env, char *track)
{
	pid_t	pid;
	char	*argv[4];

	pid = fork();
	argv[0] = g_player;
	argv[1] = "-q";
	argv[2] = track;
	argv[3] = NULL;
	if (pid == 0)
	{
		execve(argv[0], argv, env);
		exit(0);
	}
	return (pid);
}
