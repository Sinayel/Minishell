/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:43:37 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/25 19:35:08 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	cmb_word(char *str)
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
	t_export *export;
	char cwd[4096];
	char *join_value;

	export = get_export();
	getcwd(cwd, sizeof(cwd));
	join_value = ft_strjoin("PWD=", cwd);
	replace_env_value_ez(env_list, "PWD", cwd);
	replace_one_in_export(export->content, join_value);
	free(join_value);
}

void ch_oldpwd(t_env **env_list) //! LE PROBLEME EST LA !!!!!
{
	t_env *temp;
	t_export *export;
	char *oldpwd;
	char *oldpwd_join;
	char cwd[4096];

	export = get_export();
	getcwd(cwd, sizeof(cwd));
	temp = *env_list;
	oldpwd = return_env_value(temp, "OLDPWD");
	oldpwd_join = ft_strjoin("OLDPWD=", cwd);
	
	if (oldpwd == NULL)
	{
		ft_export(*env_list, oldpwd_join);
		append_to_export(export->content, oldpwd_join);
		free(oldpwd_join);
		return;
	}
	else
	{
		if (verif_if_in_export(export->content, oldpwd_join) == 0)
			export->content = append_to_export(export->content, oldpwd_join);
		else
			export->content = replace_one_in_export(export->content, oldpwd_join);
		replace_env_value_ez(env_list, "OLDPWD", cwd);
	}
	free(oldpwd_join);
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

int ft_cd(t_env *env_list, char *input)
{
	char *path;
	char *initial_path;
	t_data *data;

	data = get_data();
	path = NULL;
	initial_path = NULL;
	if (input == NULL || input[0] == '~' || (input[0] == '-' && input[1] == '-'))
	{
		path = return_env_value(env_list, "HOME");
		if (!path)
		{
			printf("bash: cd: HOME not set\n");
			data->error = 1;
			return 0;
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
			data->error = 1;
		}
		free(initial_path);
	}
	else
	{
		if (input[0] == '-')
		{
			path = return_env_value(env_list, "OLDPWD");
			if (!path)
			{
				printf("bash: cd: OLDPWD not set\n");
				data->error = 1;
				return 0;
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
			data->error = 1;
		}
		free(initial_path);
	}
	ch_pwd(&env_list);
	return 0;
}

void free_export(t_export *export)
{
	if (export->content)
		free_tabtab(export->content);
	free(export);
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

int ft_arg_cd(t_env *env, t_token *list)
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
	printf("arg cd = %s\n", value_for_cd);
	ft_cd(env, value_for_cd);
	free(value_for_cd);
	return (0);
}
