/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:19:30 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/15 15:53:38 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_eof(char *line, char *str, int fd)
{
	if (!line)
	{
		write(2,
			"bash :warning: here-document delimited by end-of-file (wanted `",
			64);
		write(2, str, ft_strlen(str));
		write(2, "`)\n", 3);
		close(fd);
		return (0);
	}
	return (1);
}

int	handle_end_of_line(char *line, char *str, int fd)
{
	if (ft_strcmp(line, str) == 0)
	{
		if (line)
			free(line);
		close(fd);
		return (1);
	}
	return (0);
}

int	process_and_write_line(char *line, t_env *envlist, int fd)
{
	char	*processed_line;

	if (ft_strcmp(line, "") != 0)
	{
		processed_line = proccess_dollar_value(line, envlist);
		if (processed_line)
		{
			write(fd, processed_line, ft_strlen(processed_line));
			free(processed_line);
		}
	}
	return (0);
}

int	heredoc_handler(char *str, t_env *envlist, int fd)
{
	char	*line;

	while (1)
	{
		line = readline(">");
		if (!handle_eof(line, str, fd))
			return (0);
		if (handle_end_of_line(line, str, fd))
			continue ;
		if (process_and_write_line(line, envlist, fd))
			continue ;
		write(fd, "\n", 1);
		if (line)
			free(line);
	}
	return (0);
}

int	here_doc(t_env *envlist, char *str)
{
	int	fd;

	fd = open(".tmp.heredoc", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (heredoc_handler(str, envlist, fd))
	{
		printf("here_doc = %d\n", fd);
		unlink(".tmp.heredoc");
		return (-1);
	}
	fd = open(".tmp.heredoc", O_RDONLY);
	if (fd > 0)
		unlink(".tmp.heredoc");
	return (fd);
}
