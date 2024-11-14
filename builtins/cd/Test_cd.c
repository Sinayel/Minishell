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

void ft_sig_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
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

void ch_pwd(t_env **env_list)
{
	t_env *temp;
	char cwd[4096];
	int found;

	found = 0;
	getcwd(cwd, sizeof(cwd));
	temp = *env_list;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, "PWD", 3) == 0)
		{
			found = 1;
			break;
		}
		temp = temp->next;
	}
	if (found == 0)
		return;
	if (cwd != NULL)
	{
		free(temp->value);
		temp->value = ft_strdup(cwd);
	}
	else
		printf("Erreur lors de la récupération du répertoire\n");
}

void ch_oldpwd(t_env **env_list) //! LE PROBLEME EST LA !!!!!
{
	t_env *temp;
	char *oldpwd;
	char *oldpwd_join;
	char cwd[4096];

	getcwd(cwd, sizeof(cwd));
	temp = *env_list;
	oldpwd = return_env_value(temp, "OLDPWD");
	oldpwd_join = ft_strjoin("OLDPWD=", cwd);
	if (oldpwd == NULL)
	{
		ft_export(*env_list, oldpwd_join);
		// replace_env_value(env_list, oldpwd_join); //! PAS ADAPTE SI !OLDPWD
		free(oldpwd_join);
		return;
	}
		// ft_export(*env_list, oldpwd_join);
	free(oldpwd_join);
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
			break;
		temp = temp->next;
	}
	if (cwd != NULL)
	{
		free(temp->value);
		temp->value = ft_strdup(cwd);
	}
	else
		temp->value = NULL;
}

void ft_pwd(char *arg)
{
	char cwd[4096];

	getcwd(cwd, sizeof(cwd));
	if (arg == NULL || arg[0] != '-')
	{
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

char *cd_handle_dollar(t_env *env_list, char *input)
{
	char *name;
	char *path;

	name = ft_substr(input, 1, ft_strlen(input) - 1);
	path = return_env_value(env_list, name);
	if (!path)
	{
		printf("bash: cd: %s not set\n", name);
		free(name);
		return (NULL);
	}
	free(name);
	return (path);
}

void ft_cd(t_env *env_list, char *input)
{
	char *path;
	char *initial_path;

	path = NULL;
	initial_path = NULL;
	if (input == NULL)
	{
		path = return_env_value(env_list, "HOME");
		if (!path)
		{
			printf("bash: cd: HOME not set\n");
			return;
		}
		initial_path = ft_strdup(path);
		if (access(path, X_OK) == 0)
			ch_oldpwd(&env_list); //! prend la valeur du cwd avant le pwd ?!?!?!?!!?!?!?!?!!?!?
		if (chdir(initial_path) != 0)
		{
			if (errno == ENOTDIR)
				printf("bash: cd: %s: Not a directory\n", path);
			if (errno == ENOENT)
				printf("bash: cd: %s: No such file or directory\n", path);
			else
				perror("chdir");
		}
		free(initial_path);
	}
	else
	{
		if (input[0] == '$')
		{
			path = cd_handle_dollar(env_list, input); //! Noramlement fait par le parsing (heureusement parce ca marche qu'a moitie)
			if (!path)
				return;
		}
		else if (input[0] == '-' && input[1] == '-')
		{
			printf("bash: cd: --: invalid option\n");
			return;
		}
		else if (input[0] == '-' || input[0] == '~')
		{
			path = return_env_value(env_list, "OLDPWD");
			if (!path)
			{
				printf("bash: cd: OLDPWD not set\n");
				return;
			}
			printf("%s\n", path);
		}
		else
			path = input;
		initial_path = ft_strdup(path);
		if (access(path, X_OK) == 0)
			ch_oldpwd(&env_list);
		if (chdir(initial_path) != 0)
		{
			if (errno == ENOTDIR)
				printf("bash: cd: %s: Not a directory\n", path);
			if (errno == ENOENT)
				printf("bash: cd: %s: No such file or directory\n", path);
			else
				perror("chdir");
		}
		free(initial_path);
	}
	ch_pwd(&env_list);
}

void ft_exit(t_env *env_list, char *input)
{
	ft_free_env(&env_list);
	free(input);
	exit(0);
}

int main(int argc, char *argv[], char **env)
{
    (void)argc;
    (void)argv;
    char *input;
    char **split_input;
    t_env *env_list = env_import(env);
    input = NULL;
	signal(SIGINT, ft_sig_handler);
    
    while (1)
    {
        input = readline("$> ");
        if (word_count(input) == 1)
        {
			if (ft_strcmp(skip_spaces_input(input), "cd") == 0)
				ft_cd(env_list, NULL);
        	if (ft_strcmp(input, "pwd") == 0)
        	    ft_pwd(NULL);
			if (ft_strcmp(input, "env") == 0)
        	    print_env(env_list);
			if (ft_strcmp(input, "export") == 0)
				ft_export(env_list, NULL);
			if (ft_strcmp(input, "exit") == 0)
				ft_exit(env_list, input);
			free(input);
        }
        else
        {
            split_input = ft_split(input, ' ');
			if (ft_strcmp(split_input[0], "cd") == 0 && word_count(input) > 2)
			{
				printf("bash: cd: too many arguments\n");
				free_tabtab(split_input);
				free(input);
				continue;
			}
			if (ft_strcmp(split_input[0], "unset") == 0)
				ft_unset(&env_list, split_input[1]);
            if (ft_strcmp(split_input[0], "cd") == 0)
				ft_cd(env_list, split_input[1]);
			if (ft_strcmp(split_input[0], "export") == 0)
				ft_export(env_list, split_input[1]);
			if (ft_strcmp(split_input[0], "pwd") == 0)
				ft_pwd(split_input[1]);
			free_tabtab(split_input);
        	free(input);
        }
    }
	ft_free_env(&env_list);
    return 0;
}

//! TOKENISE PAR RAPPORT AU : QUAND CD $PATH !!!!!!