// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   Test_cd.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/10/29 21:10:38 by judenis           #+#    #+#             */
// /*   Updated: 2024/10/31 13:24:50 by judenis          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>


size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = (char*)malloc(sizeof(*s) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = 0;
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1)
		return (1);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*my_getenv(char *name, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}


void ft_cd(char *path, char **env)
{
	
}

int main(int argc, char *argv[], char **env)
{
	char *input;
	input = NULL;
	printf("%s\n", my_getenv("HOME", env));
	while (1)
	{
		input = readline("test >");
		if (ft_strcmp(input, "-") == 0)
		{
			free(input);
			input = ft_strjoin(my_getenv("OLDPWD", env), "/");
		}
		else if (ft_strlen(input) == 0)
			input = ft_strjoin(my_getenv("HOME", env), "/");
		if (chdir(input) == -1)
    	    perror("Erreur lors du changement de répertoire");

    	// Obtenir et afficher le répertoire courant
    	char cwd[1024];
    	if (getcwd(cwd, sizeof(cwd)) != NULL) {
			printf("Répertoire precedent : %s\n", my_getenv("OLDPWD", env));
    	    printf("Répertoire actuel : %s\n", cwd);
    	} else {
    	    printf("Erreur lors de la récupération du répertoire\n");
    	}
		free(input);
		input = NULL;
	}
    return 0;
}
