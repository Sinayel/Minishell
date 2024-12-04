/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_option.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:59:05 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/04 18:48:12 by ylouvel          ###   ########.fr       */
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

void	utils_ch_oldpwd(t_export *export, char *oldpwd_join, char *cwd,
		t_env **env_list)
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
