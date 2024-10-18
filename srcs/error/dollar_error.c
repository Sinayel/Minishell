/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:54:55 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/18 20:20:42 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*get_before_dollar(char *str)
{
    t_data *data = get_data();
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	
	if (str[i] != '$')
		return NULL;

	data->before = (char *)malloc(sizeof(char) * (i + 1));
	if (!data->before)
		return NULL;

	strncpy(data->before, str, i);
	data->before[i] = '\0';
    return NULL;
}

void dollar_check_subj()
{
    t_data *data = get_data();
    printf("data->before dollar check = %s\n", data->before);
    data->env_value = get_env(data->before, data->env);
    printf("env_value = %s\n", data->env_value);
    // while (data->before == data->env)
    // {
    //     /* code */
    // }
    
}

//! Il faut que je retourne le mot avant le $ si je fais "ech$e" il doit me retourne "ech"
void	dollar_error(void)
{
	t_data *data = get_data();
    char *var_name;
    char *env_value;
	int i;
	i = 0;
    get_before_dollar(data->str[0]);
	if (data->str[0][0] == '$' && data->str[0][1] == '\0')
    {
		printf("minshell : $: Command not found\n");
        return ;
    }
    while (data->str[0][i])
    {
        if (data->str[0][i] == '$' && data->str[0][i + 1] != '\0')
        {
            var_name = strdup(data->str[0] + i + 1);
            env_value = get_env(var_name, data->env);
            if (env_value != NULL)
            {
                printf("minishell: %s: Command not found\n", env_value);
                free(var_name);
                return ;
            }
            else
            {
                printf("Il faut que je retourne le mot avant le $ si je fais ech$e il doit me retourne ech");
                free(var_name);
                return ;
            }
        }
        i++;
    }
    i--;
    if(data->str[0][i] == '$')
        printf("minshell : %s: Command not found\n", data->str[0]);
    else
        printf("PITIER");
}
