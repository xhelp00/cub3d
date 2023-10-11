/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 10:43:58 by phelebra          #+#    #+#             */
/*   Updated: 2023/10/11 13:08:52 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int music(char **env, char *track)
{

	char *player;

	#ifdef __linux__
		player = "/usr/bin/paplay";
	#elif __APPLE__
		player = "/Users/helebrant/.brew/bin/paplay";
	#endif

	pid_t	pid;
	char	*argv[3];

	pid = fork();
	argv[0] = player;
	argv[1] = track;
	argv[2] = NULL;
	if (pid == 0)
	{
		execve(argv[0], argv, env);
		exit(0);
	}
	return (pid);
}