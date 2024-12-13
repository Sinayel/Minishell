/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:04:59 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/13 23:30:16 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_path	*return_path(t_env *env)
{
	t_path	*path;
	char	*tmp;
	char	**path_breaker;
	int		i;

	path = NULL;
	i = 0;
	tmp = return_env_value(env, "PATH");
	if (!tmp)
		return (NULL);
	path_breaker = ft_split_for_path(tmp, ':');
	if(!path_breaker)
	{
		free(tmp);
		return (NULL);
	}
	while (path_breaker[i])
	{
		path = add_env(path, path_breaker[i]);
		i++;
	}
	i = 0;
	free(path_breaker);
	return (path);
}

void errno_check(int err)
{
	t_data *data;

	data = get_data();
	if (err == EACCES)
	{
		// printf("%s: ", token);
		ft_putstr_fd("Permission denied\n", 2);
		data->error = 126;
	}
	else
	{
		// printf("%s: ", token);
		ft_putstr_fd("Command not found\n", 2);
		data->error = 127;
	}
}

int is_directory(const char *path)
{
    struct stat path_stat;
    return (stat(path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode));
}

int check_access(char *path)
{
    if (access(path, X_OK) == -1)
	{
        if (errno == EISDIR || errno == EACCES)
		{
            errno_check(errno);
            return 1; // Erreur permission ou repertoire
        }
        return 2; // Command not found
    }
    return 0; // Aucun problème
}

int double_check(t_path *path, char *input)
{
    char *word;
    int result;

	word = NULL;
    if (is_directory(input))
	{
        printf("%s: Is a directory\n", input);
        return (1);
	}
    result = check_access(input);
    if (result == 1 || result == 0)
        return (result);
    while (path)
	{
        word = ft_magouilles(path->name, "/", input);
        if (is_directory(word))
		{
            printf("%s: Is a directory\n", word);
            free(word);
            return (1);
        }
        result = check_access(word);
        if (result == 1 || result == 0)
		{
			// printf("path ====== %s\n\n\n", 		word);
            free(word);
            return (result);
        }
		if (path->next == NULL)
			break;
        free(word);
        path = path->next;
    }
	// errno_check(0);
	free(word);
    return 1;
}
