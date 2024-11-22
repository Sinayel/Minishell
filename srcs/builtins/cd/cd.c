/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:43:37 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/22 16:41:40 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void ch_oldpwd(t_env **env_list)
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
		free(oldpwd_join);
		return;
	}
	free(oldpwd_join);
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, "OLDPWD") == 0)
			break;
		temp = temp->next;
	}
    free(temp->value);
    temp->value = ft_strdup(cwd);
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
    free(temp->value);
    temp->value = ft_strdup(cwd);
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
		if (input[0] == '-' && input[1] == '-')
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
			{
				printf("POURQUOII ??\n");
				printf("bash: cd: %s: No such file or directory\n", path);
			}
			else
				perror("chdir");
		}
		free(initial_path);
	}
	ch_pwd(&env_list);
}

int len_for_cd(t_token *list)
{
	t_token *tmp = list;
	tmp = tmp->next;
	int i = 0;
	int j = 0;
	while(tmp)
	{
		while(tmp->token[j])
		{
			i++;
			j++;
		}
		i++;
		j = 0;
		tmp = tmp->next;
	}
	return i;
}

void	ft_arg_cd(t_env *env, t_token *list)
{
	t_token *tmp = list;
	tmp = tmp->next;
	int len = len_for_cd(list);
	if(len == 0)
		return ft_cd(env, NULL);
	char *value_for_cd = (char *)malloc(sizeof(char) * (len + 1));
	int i = 0;
	int j = 0;
	while(tmp)
	{
		while(tmp->token[j])
		{
			value_for_cd[i] = tmp->token[j];
			i++;
			j++;
		}
		if(tmp->next)
			value_for_cd[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_cd[i] = '\0';
	ft_cd(env, value_for_cd);
	free(value_for_cd);
}
