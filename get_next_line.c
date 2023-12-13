/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gganteau <gganteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:09:32 by gganteau          #+#    #+#             */
/*   Updated: 2023/12/13 13:02:24 by gganteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>

void	reader(char *rest, char *buffer, char **prest, char **pline)
{
	char	*temp;
	char	*delimiter;
	char	*r;
	char	*l;

	r = NULL;
	l = NULL;
	if (rest == NULL)
		rest = ft_strdup("");//abriendo el resto para que se pueda usar en la lectura (proximas)
	temp = rest;
	r = ft_strjoin(rest, buffer);
	free(temp);
	delimiter = ft_strchr(r, '\n');
	if (delimiter != NULL)
	{
		l = ft_strdup2(r);
		temp = r;
		if (ft_strlen(delimiter) > 1) // si en delimiter hay algo mas que \n 
			r = ft_strdup(delimiter + 1); // lo meto en r
		else
			r = NULL;
		free(temp);
	}
	*prest = r;
	*pline = l;
}

void	restmaker(char *rest, char *line, char **prest, char **pline)
{
	char	*temp;
	char	*delimiter;

	if (!ft_strchr(rest, '\n')) // si solo queda una linea en el rest i.e no hay mas \n
	{
		temp = rest; // paso el contenido de rest a line usando una 
		rest = ""; // variable temporal y vacio el rest
		line = temp;
	}
	else // si hay mas lineas en el resto i.e existen mas \n
	{
		delimiter = ft_strchr(rest, '\n'); // saco cada linea similar a como he hecho en reader
		line = ft_strdup2(rest);
		temp = rest;
		if (ft_strlen(delimiter) > 1) // si en delimiter hay algo despues de \n lo metera en rest
			rest = ft_strdup(delimiter + 1);
		else
			rest = NULL;
		free(temp);
	}
	*prest = rest;
	*pline = line;
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytesread;
	char		*line;

	if (fd < 0)
		return (NULL);
	bytesread = read(fd, buffer, BUFFER_SIZE);
	if (bytesread < 0)
		free (rest);// libero el resto para que no haya memoria ocupada
	while (bytesread > 0)
	{
		buffer[bytesread] = '\0';
		reader(rest, buffer, &rest, &line); // uso puntero de puntero para procesar resto y line en la funcion de lectura y conservar lo obtenido
		if (line)
			return (line);
		bytesread = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytesread == 0 && rest != NULL && ft_strlen(rest) > 0)
	{
		restmaker(rest, line, &rest, &line);
		return (line);
	}
	rest = NULL;
	return (NULL);
}
/*
#include <fcntl.h>
int	main()
{
	int		fd;
	int		i = 1;

	fd = open("limits.txt", O_RDONLY);
	while(i <= 20)
	{
		printf("%i- %s", i, get_next_line(fd));
		i++;
	}
	return (0);
}*/