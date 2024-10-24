/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:29:03 by judenis           #+#    #+#             */
/*   Updated: 2024/10/24 12:44:59 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/pipex.h"

static char	*set_line(char *line_buffer);
static char	*fill_line_buffer(int fd, char *left_c, char *buffer);
static char	*ft_strchr(const char *s, int c);

char	*get_next_line(int fd)
{
	static char	*left_c;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
	{
		free(left_c);
		free(buffer);
		left_c = NULL;
		buffer = NULL;
		return (NULL);
	}
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, left_c, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	left_c = set_line(line);
	return (line);
}

static char	*set_line(char *line_buffer)
{
	char	*left_c;
	ssize_t	i;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 || line_buffer[1] == 0)
		return (NULL);
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left_c == 0)
	{
		free(left_c);
		left_c = NULL;
	}
	line_buffer[i + 1] = 0;
	return (left_c);
}

static char	*fill_line_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = 0;
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin_gnl(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

static char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}
