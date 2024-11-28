/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:58:53 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 13:35:18 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool is_valid_number(const char *str)
{
    int i;

	i = 0;
    if (str[i] == '+' || str[i] == '-')
        i++;
    while (str[i])
    {
        if (!isdigit(str[i]))
            return false;
        i++;
    }
    return true;
}

void	free_all(t_token *list, t_env *env, t_data *data, t_path *path)
{
	t_export *export;
	export = get_export();
	if (export && export->content)
		free_tabtab(export->content);
	ft_env_lstclear(&env);
	ft_token_lstclear(&list);
	ft_free_path(path);
	if (data && data->input)
		free(data->input);
}

int ft_exit(t_token *list, t_env *env, t_path *path)
{
    long exit_code = 0;
    char *arg;
    t_data *data;

    data = get_data();
	if (list && list->next && list->next->next)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		data->error = 2;
		return (2);
	}
    if (list && list->next)
    {
        arg = list->next->token;
        if (!is_valid_number(arg))
        {
            printf("exit: %s: ", arg);
		    ft_putstr_fd("numeric argument required\n", 2);
			free_all(list, env, data, path);
            exit(2);
        }
        exit_code = ft_strtol(arg, NULL, 10);
        if (exit_code < INT_MIN || exit_code > INT_MAX)
        {
            printf("exit: %s: ", arg);
		    ft_putstr_fd("numeric argument required\n", 2);
			free_all(list, env, data, path);
            exit(2);
        }
        exit_code = (unsigned char)exit_code;
    }
	free_all(list, env, data, path);
    exit(exit_code);
	return (2);
}

void	free_token(t_token **token)
{
	t_token	*current;
	t_token	*next;

	current = *token;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*token = NULL;
}

void ft_free_path(t_path *path)
{
    t_path *temp;
    if(!path)
        return ;

    while (path)
    {
        temp = path->next;
        free(path->name);
        free(path);
        path = temp;
    }
    path = NULL;
}
