/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gganteau <gganteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:52:15 by gganteau          #+#    #+#             */
/*   Updated: 2023/06/21 09:58:38 by gganteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line_read;
	char		*aux;
	static char	*rest;
	int			bytesRead;
	
	buffer = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
	{
		free (buffer);
		buffer = NULL;
		return (NULL);
	}
	line_read = "";
	if (rest)
		line_read = ft_strdup(rest);
	if (buffer == NULL)
		return (NULL);
	
	bytesRead = 1;
	while (bytesRead > 0)
	{
		bytesRead = read(fd, buffer, BUFFER_SIZE);
		if(bytesRead == -1)
		{
			free (buffer);
			return (NULL);
		}
		if (bytesRead != 0)
		{
			buffer[bytesRead] = '\0';
			if (*line_read)
				free(line_read);
			line_read = ft_strjoin2(line_read, buffer);
		}
		if (bytesRead == 0 && line_read[0] == '\0')
		{
			free(buffer);
			return (NULL);
		}
	//	printf("buffer1: %s\n", buffer);
		if (ft_strchr(buffer, '\n'))
			break;
	//	free (buffer); este free empeora
		//buffer[bytesRead] = '\0';
		if (bytesRead == 0)
			break;
	//	free (buffer); este free empeora
	}
	if (bytesRead == 0 && *line_read)
	{
		rest = ft_strchr(line_read, '\n');
		if (rest)
			rest++;
		free(buffer); //este free no consigue nada
		aux = ft_substr(line_read, 0, rest - line_read);
		free(line_read);
		return (aux);
		//printf("buffer2: %s\n", buffer);
	}
	else
	{
		rest = "";
		rest = ft_strchr(buffer, '\n');
		if (rest)
			rest++;
	//	printf("buffer3: %s\n", buffer);
		free(buffer); //este free empeora los leaks
	}
	return (line_read);
	//free (buffer); este free no mejora nada
}
// void leaks(void)
// {
// 	system("leaks -q a.out");
// }

// #include <stddef.h>
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <fcntl.h>
// int main ()
// {
// 	int		fd;
// 	char *line;
// 	int i;

// 	atexit(leaks);
// 	i = 0;
// 	fd = open ("tester.txt", O_RDONLY);
// 	while(i < 2)
// 	{
// 		line = get_next_line(fd);
// 		++i;
// 		printf("Esta es la linea: %s\n", line);
// 		free(line);
// 	}
// 	// printf ("|%s|\n", get_next_line(fd));
// 	// printf ("<%s>\n", get_next_line(fd));
// 	// printf ("*%s*\n", get_next_line(fd));
// 	// printf ("-%s-\n", get_next_line(fd));
// 	// printf ("$%s$\n", get_next_line(fd));
// 	return (0);
// }