/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gganteau <gganteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:15:46 by gganteau          #+#    #+#             */
/*   Updated: 2023/05/11 10:57:15 by gganteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	int	fd;
	char buffer[BUFFER_SIZE + 1];
	ssize_t bytesRead;
	
	
	fd = open ("tester.txt", O_RDONLY);
	if (fd == -1)
	{
		printf ("Failed to open file.\n");
		return (1);
	}
	while ((bytesRead = read (fd, buffer, BUFFER_SIZE))> 0)
	{
		buffer[bytesRead] = '\0';
		printf ("%s", buffer);
	}
	close (fd);
	return (0);
	
}