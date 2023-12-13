/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gganteau <gganteau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:09:37 by gganteau          #+#    #+#             */
/*   Updated: 2023/12/13 11:52:06 by gganteau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	reader(char *rest, char *buffer, char **prest, char **pline);
void	restmaker(char *rest, char *line, char **prest, char **pline);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strdup2(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif