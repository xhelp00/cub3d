/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phelebra <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 09:52:22 by phelebra          #+#    #+#             */
/*   Updated: 2023/02/03 10:48:34 by phelebra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*read_file(int fd, char *s)
{
	int		bytes_number;
	char	*buffer;

	bytes_number = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes_number != 0 && !ft_strchrgnl(s, '\n'))
	{
		bytes_number = read(fd, buffer, BUFFER_SIZE);
		if (bytes_number == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_number] = '\0';
		s = ft_strjoingnl(s, buffer);
	}
	free(buffer);
	return (s);
}

char	*single_line(char *s)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!*s)
		return (NULL);
	while (s[i] != '\n' && s[i])
		i++;
	ptr = malloc (sizeof(char) * (i + 2));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*update_static(char *s)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	while (s[i] != '\n' && s[i])
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	ptr = malloc(sizeof(char) * (ft_strlengnl(s) + 1 - i));
	if (!ptr)
		return (NULL);
	i++;
	j = 0;
	while (s[i])
		ptr[j++] = s[i++];
	ptr[j] = '\0';
	free(s);
	return (ptr);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*next_line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	s = read_file(fd, s);
	if (!s)
		return (NULL);
	next_line = single_line(s);
	s = update_static(s);
	return (next_line);
}
