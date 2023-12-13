/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gganteau <gganteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:09:26 by gganteau          #+#    #+#             */
/*   Updated: 2023/12/12 14:04:12 by gganteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlen(const char *c)
{
	int	i;

	i = 0;
	while (c[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = ft_strlen(s1);
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s1[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

char	*ft_strdup2(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*dup;

	i = 0;
	while (s1[i] && s1[i] != '\n')
	{
		i++;
	}
	if (s1[i] == '\n')
		i++;
	dup = malloc(sizeof(char) * (i + 1));
	if (!dup)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dup[j] = s1[j];
		j++;
	}
	dup[j] = '\0';
	return (dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = '\0';
	return (s3);
}
