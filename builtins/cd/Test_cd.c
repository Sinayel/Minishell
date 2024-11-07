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

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && (s1[i] == s2[i]) && s1[i] != '\0')
	{
		i++;
	}
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}

int	word_count(char *str)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
			i++;
		if (str && str[i] != '\0')
			wc++;
		while (str[i] && (str[i] != ' ' && str[i] != '\n' && str[i] != '\t'))
			i++;
	}
	return (wc);
}

void ch_pwd(t_env *env_list)
{
	t_env *temp;
	char cwd[1024];

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(temp->name, "PWD") == 0)
			break;
		temp = temp->next;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		temp->value = ft_strdup(cwd);
	else
		printf("Erreur lors de la récupération du répertoire\n");
}

void ch_oldpwd(t_env *env_list)
{
	t_env *temp;
	char cwd[1024];

	temp = env_list;
	if (return_env_value(env_list, "OLDPWD") == NULL)
	{
		env_create_oldpwd(&env_list);
		return;
	}
	while (temp)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
			break;
		temp = temp->next;
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		temp->value = ft_strdup(cwd);
	else
		printf("Erreur lors de la récupération du répertoire\n");
}

void ft_pwd(t_env *env_list, char *arg)
{
	char cwd[4096];

	(void)env_list;
	getcwd(cwd, sizeof(cwd));
	
	if (arg == NULL || arg[0] != '-')
	{
		// ch_pwd(env_list);
		printf("%s\n", cwd);
		return;
	}
	if (arg[0] == '-' && arg[1] == '-')
	{
		printf("bash: pwd: --: invalid option\n");
		return;
	}
	if (arg[0] == '-' && arg[1])
	{
		printf("bash: pwd: %s: invalid option\n", arg);
		return;
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

void free_tabtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char *skip_spaces_input(char *input)
{
	int i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input + i);
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
    char **split_input;
	char *name;
    t_env *env_list = env_import(env); //!Verfifer si env existe avant de l'utiliser
    // print_env_vars(env_list, "OLDPWD");
    input = NULL;
    
    while (1)
    {
        input = readline("$> ");
        if (word_count(input) == 0)
            continue;
        if (ft_strcmp(input, "pwd") == 0)
        {
            ft_pwd(env_list, NULL);
            continue;
        }
		if (ft_strcmp(input, "env") == 0)
        {
            print_env(env_list);
            continue;
        }
        if (word_count(input) == 1)
        {
            ch_oldpwd(env_list);  // On sauvegarde OLDPWD avant de changer de répertoire
			if (ft_strcmp(skip_spaces_input(input), "cd") == 0) //! ICI 
			{
            	if (chdir(return_env_value(env_list, "HOME")) != 0) //! GERE LE CAS OU HOME EST UNSET ET GERER LE CAS OU HOME EST INCORRECT
                	printf("bash: cd: %s: No such file or directory\n", return_env_value(env_list, "HOME"));
			}
			ch_pwd(env_list);
			free(input);
			continue;
        }
        else
        {
			ch_oldpwd(env_list);
            split_input = ft_split(input, ' ');
			if (ft_strcmp(split_input[0], "pwd") == 0)
				ft_pwd(env_list, split_input[1]);
			if (ft_strcmp(split_input[0], "cd") == 0 && word_count(input) > 2)
			{
				printf("bash: cd: too many arguments\n");
				free_tabtab(split_input);
				free(input);
				continue;
			}
            if (ft_strcmp(split_input[0], "cd") == 0)
            {
				if (ft_strncmp(split_input[1], "$", 1) == 0) //! NOrmalement a enlever
				{
					printf("->%ld<-\n", ft_strlen(split_input[1]) - 1);
					name = ft_substr(split_input[1], 1, ft_strlen(split_input[1]) - 1);
					free(split_input[1]);
					printf("\n-> %s\n", name);
					split_input[1] = return_env_value(env_list, name);
					free(name);
				}
                if (ft_strcmp(split_input[1], "-") == 0 || ft_strcmp(split_input[1], "~") == 0)
                {
                    free(split_input[1]);
                    split_input[1] = return_env_value(env_list, "OLDPWD");
					printf("%s\n", split_input[1]);
                }
				if (split_input[1][0] == '-' && split_input[1][1] == '-')
                {
					printf("bash: cd: --: invalid option\n");
					free_tabtab(split_input);
					free(input);
					continue;
                }
                if (chdir(split_input[1]) != 0)
				{
					if (errno == ENOTDIR)
						printf("bash: cd: %s: Not a directory\n", split_input[1]);
					if (errno == ENOENT)
                    	printf("bash: cd: %s: No such file or directory\n", split_input[1]);
				}
            }
        }
		ch_pwd(env_list);
		ft_free_env(env_list);
		free_tabtab(split_input);
        free(input);
        input = NULL;
    }
    return 0;
}
