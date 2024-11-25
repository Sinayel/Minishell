/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 20:46:28 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/25 20:51:23 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_export *unset_export(t_export *export, char *arg)
{
    int i;
    int j;
    char **dest;

    i = 0;
    j = 0;
    while (export->content[i])
        i++;
    dest = (char **)malloc(sizeof(char *) * (i + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (export->content[i])
    {
        if (ft_strncmp(export->content[i], arg, ft_strlen(arg)) != 0)
            dest[j++] = ft_strdup(export->content[i]);
        i++;
    }
    free_tabtab(export->content);
    dest[j] = NULL;
    export->content = dest;
    return (export);
}

int ft_unset(t_env **env_list, char *arg)
{
    t_env *temp;
    t_env *prev;
    t_export *export = get_export();
    char **arg_split;
    int i;

    i = 0;
    if (cmb_word(arg) > 1)
        arg_split = ft_split(arg, ' ');
    else
    {
        arg_split = (char **)malloc(sizeof(char *) * 2);
        arg_split[0] = ft_strdup(arg);
        arg_split[1] = NULL;
    }
    while (arg_split[i])
    {
        export = unset_export(export, arg_split[i]);
        i++;
    }
    i = 0;
    while (arg_split[i]) //! A REVOIR
    {
        temp = *env_list;
        if (!temp)
        {
            free_tabtab(arg_split);
            return 0;
        }
        prev = NULL;
        while (temp)
        {
            if (ft_strcmp(temp->name, arg_split[i]) == 0)
            {
                if (prev == NULL)
                    *env_list = temp->next;
                else
                    prev->next = temp->next;
                free(temp->name);
                free(temp->value);
                free(temp);
                free_tabtab(arg_split);
                return 0;
            }
            prev = temp;
            temp = temp->next;
        }
        i++;
    }
    free_tabtab(arg_split);
    return 0;
}

int ft_arg_unset(t_env *env, t_token *list)
{
	t_token *tmp = list;
	tmp = tmp->next;
	int len = len_for_cd(list);
	if(len == 0)
		return 0;
	char *value_for_unset = (char *)malloc(sizeof(char) * (len + 1));
	int i = 0;
	int j = 0;
	while(tmp)
	{
		while(tmp->token[j])
		{
			value_for_unset[i] = tmp->token[j];
			i++;
			j++;
		}
		if(tmp->next)
			value_for_unset[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_unset[i] = '\0';
	printf("arg cd = %s\nlen du export = %d\n", value_for_unset, len);
	ft_unset(&env, value_for_unset);
	free(value_for_unset);
	return (0);
}
