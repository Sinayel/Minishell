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

#include "../env/env.h"

void ch_oldpwd(t_env *env_list)
{
	t_env *temp;
	char cwd[1024];

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
		{
			break;
		}
		temp = temp->next;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp->value = ft_strdup(cwd);
	}
	else
	{
		printf("Erreur lors de la récupération du répertoire\n");
	}
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




int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	char *input;
	t_env *env_list = env_import(env); //!Verfifer si env existe avant de l'utiliser
	print_env_vars(env_list, "OLDPWD");
	input = NULL;
    char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", my_getenv("HOME", env));
	while (1)
	{
		input = readline("test >");
		if (ft_strcmp(input, "-") == 0)
		{
			free(input);
			input = return_env_value(env_list, "OLDPWD");
		}
		else if (ft_strlen(input) == 0)
			input = return_env_value(env_list, "HOME");
		// if (input == cwd)
		// {
		// 	printf("test\n");
		// 	free(input);
		// 	input = NULL;
		// 	continue;
		// }
		if (chdir(input) == 0)
			ch_oldpwd(env_list);
		else
    	    perror("Erreur lors du changement de répertoire");

    	// Obtenir et afficher le répertoire courant
		getcwd(cwd, sizeof(cwd));
    	if (cwd != NULL) {
			print_env_vars(env_list, "OLDPWD");
    	    printf("Répertoire actuel : %s\n", cwd);
    	} else {
    	    printf("Erreur lors de la récupération du répertoire\n");
    	}
		free(input);
		input = NULL;
	}
    return 0;
}
