/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:43:58 by phelebra          #+#    #+#             */
/*   Updated: 2023/10/16 16:03:15 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int music(char **env, char *track)
{

	char *player;

	#ifdef __linux__
		player = "/usr/bin/mpg123";
	#elif __APPLE__
		player = "/Users/helebrant/.brew/bin/mpg123";
	#endif

	pid_t	pid;
	char	*argv[4];

	pid = fork();
	argv[0] = player;
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