/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gganteau <gganteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:35:29 by gganteau          #+#    #+#             */
/*   Updated: 2023/10/26 11:46:43 by gganteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *ft_read_and_rest(int fd, char *rest)
{
	int	bytesRead;
	char *buf;
	
	buf = malloc(sizeof (char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	bytesRead = 1;
	while (!ft_strchr_gnl(rest, '\n') && bytesRead != 0)
	{
		bytesRead = read(fd, buf, BUFFER_SIZE);
		buf[bytesRead] = '\0';
		printf("ft_read_and_rest '%s'\n", buf);
		if(bytesRead == -1)
		{
			free (buf);
			return (NULL);
		}
		buf[bytesRead] = '\0';
		rest = ft_strjoin(rest, buf);
	}
	free (buf);
	return (rest);
}

char *gnl(int fd)
{
	static char *rest = NULL; // la norma permite inicializar una static
	char buffer[BUFFER_SIZE + 1];
	ssize_t bytesRead;
	char *temp;
	char *delimiter;
	char *line;

	if (fd < 0)
		return NULL;
	if (rest == NULL) // rest estara vacia en la primera leida. 
		rest = ft_strdup(""); // para poder usar rest y que se inicie el bucle, duplicamos un string vacio en la primera leida.
	bytesRead = read(fd, buffer, BUFFER_SIZE);
	while (bytesRead > 0)
	{
		buffer[bytesRead] = '\0'; //acabar buffer en '\0' para evitar desbordes de memoria a medida que se van concatenando leidas
		temp = rest; //debido a que rest hay que limpiarla de leidas previas hasta '\n', necesitamos temp para almacenar el contenido temporalmente y luego liberar la memoria
		rest = ft_strjoin(rest, buffer);
		free(temp);
		delimiter = ft_strchr(rest, '\n'); //delimiter nos va a establecer la distancia entre la posicion 0 y el primer '\n' encontrado en rest
		if (delimiter != NULL)
		{
			line = ft_substr(rest, 0, rest - delimiter); // crea la linea limpia: desde la posicion 0 hasta delimiter (ie '\n')
			temp = rest;
			rest = ft_strdup(delimiter + 1);
			free(temp);
			return (line);
		}
		bytesRead = read(fd, buffer, BUFFER_SIZE);
	}
	if (ft_strlen(rest) > 0)
	{
		temp = rest;
		rest = NULL;
		return (temp);
	}
	return (NULL);
}

#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


int main()
{
	int fd;
	char *line;

	fd = open("tester.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n");
		return (1);
	}
	
	/* int padding = 25;
	int field_lenght = 20; */

	/* printf("%-*.*s", padding, field_lenght, "hola que tal weiuroiweruoiweu ioweruoi weuroiw eur oiweu");
	printf("%-30.25s\n", "hola que ");
	printf("%-30.25s", "hola que l");
	printf("%-30.25s\n", "hola que tal");
	printf("%-30.25s", "holatal");
	printf("%-30.25s\n", "latal"); */

	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
	line = gnl(fd);
	printf("%s", line);
	return (0);
}

int main1(int argc, char **argv)
{
	int	fd;
	char *line;
	char *rest;
	int i;
	
	i = 0;
	if (argc != 2)
	{
		printf("Error, se espera el nombre de archivo\n");
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	rest = ft_strdup("");
	line = gnl(fd);
	while (line)
	{
		printf ("%i, *%s*\n", i, line);
		free(line);
		++i;
		line = gnl(fd);
	}
	return(0);
}