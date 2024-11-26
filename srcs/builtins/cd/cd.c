/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:43:37 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/26 19:53:56 by ylouvel          ###   ########.fr       */
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

void	ch_pwd(t_env **env_list)
{
	t_export	*export;
	char		cwd[4096];
	char		*join_value;

	export = get_export();
	getcwd(cwd, sizeof(cwd));
	join_value = ft_strjoin("PWD=", cwd);
	replace_env_value_ez(env_list, "PWD", cwd);
	replace_one_in_export(export->content, join_value);
	free(join_value);
}

void	utils_ch_oldpwd(t_export *export, char *oldpwd_join, char *cwd, t_env **env_list)
{
	if (verif_if_in_export(export->content, oldpwd_join) == 0)
		export->content = append_to_export(export->content, oldpwd_join);
	else
		export->content = replace_one_in_export(export->content, oldpwd_join);
	replace_env_value_ez(env_list, "OLDPWD", cwd);
}

void	ch_oldpwd(t_env **env_list)
{
	t_env		*temp;
	t_export	*export;
	char		*oldpwd;
	char		*oldpwd_join;
	char		cwd[4096];

	export = get_export();
	getcwd(cwd, sizeof(cwd));
	temp = *env_list;
	oldpwd = return_env_value(temp, "OLDPWD");
	oldpwd_join = ft_strjoin("OLDPWD=", cwd);
	if (oldpwd == NULL)
	{
		append_env_var(env_list, "OLDPWD", cwd);
		export->content = append_to_export(export->content, oldpwd_join);
		free(oldpwd_join);
		return ;
	}
	else
		utils_ch_oldpwd(export, oldpwd_join, cwd, env_list);
	free(oldpwd_join);
}

char	*skip_spaces_input(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	return (input + i);
}

char	*cd_handle_dollar(t_env *env_list, char *input)
{
	char	*name;
	char	*path;

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

void	invalid_option(char *path, t_env *env_list, t_data *data, char *initial_path)
{
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
}

int no_home_set(char *path, t_data *data)
{
	if (!path)
	{
		printf("bash: cd: HOME not set\n");
		data->error = 1;
		return (0);
	}
	return 1;
}

void mouv_cd(char *path, t_env *env_list, t_data *data)
{
	char *initial_path;

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
	ch_pwd(&env_list);
}

int bad_option(char *input, t_data *data, t_env *env_list, char *path)
{
	if (input[0] == '-' && input[1] == '-')
	{
		printf("bash: cd: --: invalid option\n");
		data->error = 2;
		return (0);
	}
	if (input[0] == '-' && input[1] != '-' && input[1] != '\0')
	{
		printf("bash: cd: -%c: invalid option\n", input[1]);
		data->error = 2;
		return (0);
	}
	if (input[0] == '-' && input[1] == '\0')
	{
		path = return_env_value(env_list, "OLDPWD");
		if (!path)
		{
			printf("bash: cd: OLDPWD not set\n");
			data->error = 1;
			return (0);
		}
		mouv_cd(path, env_list, data);
		printf("%s\n", path);
	}
	return 1;
}

int	ft_cd(t_env *env_list, char *input)
{
	char	*path;
	t_data	*data;

	data = get_data();
	path = NULL;
	if (input == NULL || input[0] == '~' || (input[0] == '-' && input[1] == '-'
			&& input[2] == '\0'))
	{
		path = return_env_value(env_list, "HOME");
		if(no_home_set(path, data) == 0)
			return 0;
		mouv_cd(path, env_list, data);
	}
	else
	{
		path = NULL;
		if(bad_option(input, data, env_list, path) == 0)
			return 0;
		else
			path = input;
		mouv_cd(path, env_list, data);
	}
	return (0);
}

void	free_export(t_export *export)
{
	if (export->content)
		free_tabtab(export->content);
	free(export);
}

int	len_for_cd(t_token *list)
{
	t_token	*tmp;
	int		i;
	int		j;

	tmp = list;
	tmp = tmp->next;
	i = 0;
	j = 0;
	while (tmp)
	{
		while (tmp->token[j])
		{
			i++;
			j++;
		}
		i++;
		j = 0;
		tmp = tmp->next;
	}
	return (i);
}

int	ft_arg_cd(t_env *env, t_token *list)
{
	int		len;
	t_token	*tmp;
	char	*value_for_cd;
	int		i;
	int		j;

	len = len_for_cd(list);
	tmp = list->next;
	if (len == 0)
		return (ft_cd(env, NULL));
	value_for_cd = (char *)malloc(sizeof(char) * (len + 1));
	init_var_i(&i, &j);
	while (tmp)
	{
		while (tmp->token[j])
			value_for_cd[i++] = tmp->token[j++];
		if (tmp->next)
			value_for_cd[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_cd[i] = '\0';
	ft_cd(env, value_for_cd);
	free(value_for_cd);
	return (0);
}
