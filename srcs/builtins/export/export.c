/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:48:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/26 17:37:41 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void export_to_env(t_env **env_list, char **arg)
{
    t_env *new;
    t_env **tmp;
    char *temp;
    int i;

    temp = NULL;
    i = 1;
    new = (t_env *)malloc(sizeof(t_env));
    if (!new)
        return;
    new->name = ft_strdup(arg[0]);
    new->value = ft_strdup("");
    while (arg[i])
    {
        if (i > 1)
            temp = ft_magouilles(new->value, "=", arg[i]);
        else
            temp = ft_strjoin(new->value, arg[i]);
        free(new->value);
        new->value = temp;
        i++;
    }
    new->next = NULL;
    if (*env_list == NULL)
    {
        *env_list = new;
        return;
    }
    tmp = env_list;
    while ((*tmp)->next)
        *tmp = (*tmp)->next;
    (*tmp)->next = new;
    env_list = tmp;
}

int is_env_name_valid(char *name)
{
    int i;

    i = 0;
    if (name[0] >= '0' && name[0] <= '9')
        return 1;
    while (name[i])
    {
        if ((name[i] >= 32 && name[i] < 47) || (name[i] >= 58 && name[i] < 61) || (name[i] >= 62 && name[i] < 65) || (name[i] >= 91 && name[i] < 95) || name[i] == 96 || name[i] >= 123)
            return 1;
        i++;
    }
    return 0;
}

void replace_env_value_ez(t_env **env_list,char *name, char *arg)
{
    t_env **temp;

    if (*env_list == NULL || env_list == NULL)
        return;
    temp = env_list;
    while (*temp)
	{
		if (ft_strcmp((*temp)->name, name) == 0)
		{
            free((*temp)->value);
            (*temp)->value = ft_strdup(arg);
            return;
		}
		*temp = (*temp)->next;
	}
}

void replace_env_value(t_env **env_list, char **arg)
{
    t_env **temp;

    if (*env_list == NULL || env_list == NULL)
        return;
    temp = env_list;
    while (*temp)
	{
		if (ft_strcmp((*temp)->name, arg[0]) == 0)
		{
            free((*temp)->value);
            (*temp)->value = ft_strdup(arg[1]);
            return;
		}
		*temp = (*temp)->next;
	}
}

int cmb_env(t_env *envlist)
{
    t_env *temp;
    int len;
    
    len = 0;
    temp = envlist;
    while (temp)
    {
        if (temp->name)
            len++;
        temp = temp->next;
    }
    return (len);
}

char *ft_magouilles(char *str1, char *str2, char *str3)
{
    char *dest;
    int i;
    int j;

    i = 0;
    j = 0;
    dest = (char *)malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3) + 1));
    while (str1[i])
    {
        dest[i] = str1[i];
        i++;
    }
    j = 0;
    while (str2[j])
    {
        dest[i] = str2[j];
        i++;
        j++;
    }
    j = 0;
    while (str3[j])
    {
        dest[i] = str3[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return (dest);
}

char **env_to_export(t_env *env_list)
{
    char **env_export;
    int len;
    int i;
    t_env *temp;

    temp = env_list;
    i = 0;
    len = cmb_env(temp);
    env_export = (char **)malloc(sizeof(char *) * (len + 1));
    if (!env_export)
        return (NULL);
    while (temp)
    {
        env_export[i] = ft_magouilles(temp->name, "=", temp->value);
        temp = temp->next;
        i++;
    }
    env_export[i] = NULL;
    env_export = sort_env_export(env_export);
    return (env_export);
}
// return 1 ou 2 lorsqu'un espace est trouve
int check_equal_arg(char *arg)
{
    int i;

    i = 0;
    if (!arg)
        return 1;
    while (arg[i])
    {
        if (arg[i] == '=' && !arg[i + 1])
            return 2;
        if (arg[i] == '=' && arg[i + 1] != '\0')
            return 1;
        i++;
    }
    return 0;
}

char **replace_export(char **env_export, char **split_arg)
{
    int i = 0;
    
    while (env_export[i])
    {
        if (ft_strncmp(env_export[i], split_arg[0], ft_strlen(split_arg[0])) == 0)
        {
            free(env_export[i]);
            env_export[i] = ft_magouilles(split_arg[0], "=", split_arg[1]);
            return (env_export);
        }
        i++;
    }
    return (env_export);
}

char **append_to_export(char **env_export, char *arg)
{
    char **temp;
    char **sorted;
    int i;

    sorted = NULL;
    i = 0;
    printf("EST CE QUE JE PASSE LA ?????\n");
    while (env_export && env_export[i])
        i++;
    temp = (char **)malloc(sizeof(char *) * (i + 2));
    if (!temp)
        return (NULL);
    i = 0;
    while (env_export[i])
    {
        temp[i] = ft_strdup(env_export[i]);
        if (!temp[i]) // Gestion d'erreur en cas d'échec de ft_strdup
        {
            free_tabtab(temp);
            return (NULL);
        }
        i++;
    }
    printf("arg = %s\n, env_export = %s\n", arg, env_export[i - 1]);
    temp[i] = ft_strdup(arg);
    temp[i + 1] = NULL;
    sorted = sort_env_export(temp);
    free_tabtab(env_export);
    return (sorted);
}

char **sort_env_export(char **env_export)
{
    int i;
    char *temp;
    char **env_export_sorted;
    i = 0;
    temp = NULL;
    if (env_export == NULL)
        return NULL;
    env_export_sorted = env_export;
    while (env_export_sorted[i] && env_export_sorted[i+1])
    {
        if (ft_strcmp(env_export_sorted[i], env_export_sorted[i+1]) > 0)
        {
            temp = env_export_sorted[i];
            env_export_sorted[i] = env_export_sorted[i+1];
            env_export_sorted[i+1] = temp;
            i = 0;
        }
        else
            i++;
    }
    return env_export_sorted;
}

void printf_export(char **env_export)
{
    int is_open_quote;
    int i;
    int j;

    i = 0;
    j = 0;
    is_open_quote = 0;
    if (!env_export || !env_export[0])
        return;
    while (env_export[i])
    {
        is_open_quote = 0;
        j = 0;
        if (env_export[i][0])
            printf("export ");
        while (env_export[i][j])
        {
            printf("%c", env_export[i][j]);
            if (env_export[i][j] == '=' && is_open_quote == 0)
            {
                printf("\"");
                is_open_quote = 1;
            }
            if (!env_export[i][j+1] && is_open_quote == 1)
                printf("\"");
            j++;
        }
        printf("\n");
        i++;
    }
}

char *pipeline_to_env_value(t_env *envlist, char *name)
{
    char *value = NULL;
    char **split_name = NULL;
    t_env *temp;

    if (!name || !envlist)
        return NULL; // Protection contre les entrées nulles
    if (check_equal_arg(name) == 1)
        split_name = ft_split(name, '=');
    else
        split_name = ft_split(name, ' ');
    if (!split_name || !split_name[0])
        return NULL;
    temp = envlist;
    value = return_env_value(temp, split_name[0]);
    free_tabtab(split_name);
    return value;
}

t_export *get_export(void)
{
    static t_export export;
    return (&export);
}

//return 1 si arg est deja dans export
int verif_if_in_export(char **export, char *arg)
{
    int i;
    char **split_arg;
    int is_equal;
    char *sous_str;

    sous_str = NULL;
    i = 0;
    is_equal = 0;
    split_arg = NULL;
    if (!export)
        return 0;
    while (arg[i])
    {
        if (arg[i] == '=')
            is_equal = 1;
        i++;
    }
    if (is_equal == 1)
        split_arg = ft_split(arg, '=');
    i = 0;
    while (export[i])
    {
        sous_str = ft_substr(export[i], 0, len_before_space(export[i]));
        if (split_arg != NULL)
        {
            if (ft_strcmp(sous_str, split_arg[0]) == 0)
            {
                free(sous_str);
                free_tabtab(split_arg);
                return 1;
            }
        }
        else if (ft_strcmp(sous_str, arg) == 0)
        {
            free(sous_str);
            free_tabtab(split_arg);
            return (1);
        }
        free(sous_str);
        i++;
    }
    free_tabtab(split_arg);
    return 0;
}

char **replace_one_in_export(char **export, char *arg)
{
    int i;
    char **split_arg;
    char *sous_str;

    i = 0;
    sous_str = NULL;
    split_arg = ft_split(arg, '=');
    while (export[i])
    {
        sous_str = ft_substr(export[i], 0, len_before_space(export[i]));
        if (ft_strcmp(sous_str, split_arg[0]) == 0)
        {
            free(export[i]);
            export[i] = ft_strdup(arg);
        }
        free(sous_str);
        i++;
    }
    free_tabtab(split_arg);
    return export;
}

void init_export(t_export *export_list, t_env *envlist)
{
    if (!export_list->content)
        export_list->content = env_to_export(envlist);
}

int ft_export(t_env *env_list, char *arg)
{
    t_export *export = get_export();
    t_data *data = get_data();
    char **split_arg;
    char *env_value = NULL;
    char **arg_tabtab;
    int i;

    i = 0;
    init_export(export, env_list);
    if (!export->content)
        return 0;
    env_value = NULL;
    split_arg = NULL;
    arg_tabtab = NULL;
    if (!arg)
    {
        printf_export(export->content);
        return 0;
    }
    else if (cmb_word(arg) > 1)
        arg_tabtab = ft_split(arg, ' ');
    else
    {
        arg_tabtab = (char **)malloc(sizeof(char *) * 2);
        arg_tabtab[0] = ft_strdup(arg);
        arg_tabtab[1] = NULL;
    }
    while (arg_tabtab[i])
    {
        printf("arg tab = %s\n", arg_tabtab[i]);
        env_value = pipeline_to_env_value(env_list, arg_tabtab[i]);
        printf("JE PPASSE CMB DE FOIS ICI ?????\ni = %d\n", i);
        if (is_env_name_valid(arg_tabtab[i]) == 1)
        {
            printf("bash: export: `%s': not a valid identifier\n", arg_tabtab[i]);
            data->error = 1;
        }
        else if (check_equal_arg(arg_tabtab[i]) == 1)
        {
            split_arg = ft_split(arg_tabtab[i], '='); //!
            if (env_value == NULL)
            {
                if (verif_if_in_export(export->content, arg_tabtab[i]) == 1)
                    export->content = replace_one_in_export(export->content, arg_tabtab[i]);
                else
                    export->content = append_to_export(export->content, arg_tabtab[i]);
                export_to_env(&env_list, split_arg); //! SPLIT PAR RAPPOR A L'EGAL
            }
            else
            {
                export->content = replace_export(export->content, split_arg);
                if (strcmp(env_value, split_arg[0]) != 0)
                    replace_env_value(&env_list, split_arg);
            }
            free_tabtab(split_arg);
        }
        else if ((check_equal_arg(arg_tabtab[i]) == 0 || check_equal_arg(arg_tabtab[i]) == 2) && env_value == NULL && verif_if_in_export(export->content, arg_tabtab[i]) == 0)
            export->content = append_to_export(export->content, arg_tabtab[i]);
        i++;
    }
    free_tabtab(arg_tabtab);
    return 0;
}

int ft_arg_export(t_env *env, t_token *list)
{
	t_token *tmp = list;
	tmp = tmp->next;
	int len = len_for_cd(list);
	if(len == 0)
		return ft_export(env, NULL);
	char *value_for_export = (char *)malloc(sizeof(char) * (len + 1));
	int i = 0;
	int j = 0;
	while(tmp)
	{
		while(tmp->token[j])
		{
			value_for_export[i] = tmp->token[j];
			i++;
			j++;
		}
		if(tmp->next)
			value_for_export[i++] = ' ';
		j = 0;
		tmp = tmp->next;
	}
	value_for_export[i] = '\0';
	printf("arg cd = %s\nlen du export = %d\n", value_for_export, len);
	ft_export(env, value_for_export);
	free(value_for_export);
	return (0);
}
