/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 18:39:51 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/14 17:58:55 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	ft_strlen_dollar(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] == '$')
		i++;
	while (str[i])
	{
		i++;
		j++;
	}
	return (j);
}

bool	verif_token(char c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 95);
}

char	*dollar_value(t_env *env, char *token)
{
	int		i = 0, j;
	int		len;
	char	*tmp;
	char	*value;

	i = 0, j = 0;
	len = ft_strlen_dollar(token);
	tmp = malloc(sizeof(char) * (len + 1));
	value = NULL;
	while (token[i] && verif_token(token[i]))
		tmp[j++] = token[i++];
	tmp[j] = '\0';
	value = return_env_value(env, tmp);
	printf("value = %s\n", value);
	free(tmp);
	return (value);
}

// // char *get_dollar(char *value, char *token)
// // {
// //     int i = 0;
// //     int j = 0;
// //     int v = 0;
// //     char *tmp = malloc(sizeof(char) * 1000);
// //     int len = ft_strlen(token);
// //     while(i < len)
// //     {
// //         while(value && value[i] != token[i])
// //         {
// //             tmp[j] = value[i];
// //             j++;
// //             i++;
// //             v = 1;
// //         }
// //         if(v == 1)
// //             len += ft_strlen(value);
// //         printf("here !!!\n");
// //         tmp[j] = token[i];
// //         j++;
// //         i++;
// //     }
// //     tmp[j] = '\0';
// //     printf("tmp = %s\n", tmp);
// //     return (tmp);
// // }

// int	len_dollar(t_env *env, char **wd_split)
// {
// 	char	*value;
// 	int		i;
// 	int		v;
// 	int		j;

// 	v = 0;
// 	i = 0;
// 	j = 0;
// 	while (wd_split[i])
// 	{
// 		v = 0;
// 		value = dollar_value(env, wd_split[i]);
// 		if (value)
// 		{
// 			while (value[v])
// 			{
// 				j++;
// 				v++;
// 			}
// 		}
// 		else
// 		{
// 			while (wd_split[i][v])
// 			{
// 				j++;
// 				v++;
// 			}
// 		}
// 		i++;
// 	}
// 	free(value);
// 	return (j);
// }

// void	proccess_dollar(t_env *env, t_token *list)
// {
// 	t_token	*tmp;
// 	int		i;
// 	int		j;
// 	int		v;
// 	// int		x;
// 	int		len;
// 	char	*value;
// 	char	*return_value;
// 	char	**wd_split;

// 	tmp = list;
// 	i = 0;
// 	j = 0;
// 	v = 0;
// 	// x = 0;
// 	while (tmp)
// 	{
// 		wd_split = ft_split(tmp->token, '$');
// 		len = len_dollar(env, wd_split);
// 		return_value = malloc(sizeof(char) * (len + 1));
// 		if (return_value)
// 			memset(return_value, 0, len + 1);
// 		while (wd_split[i])
// 		{
// 			v = 0;
// 			value = dollar_value(env, wd_split[i]);
// 			if (value)
// 			{
// 				while (value[v])
// 				{
// 					return_value[j] = value[v];
// 					j++;
// 					v++;
// 				}
// 			}
// 			else
// 			{
// 				while (wd_split[i][v])
// 				{
// 					return_value[j] = wd_split[i][v];
// 					j++;
// 					v++;
// 				}
// 			}
// 			// return_value[j] = '\0';
//             free(value);
//             printf("token = %s\n", tmp->token);
//             // while(tmp->token[x])
//             // {
//             //     if(tmp->token[x] == '')
//             // }
// 			tmp->token = return_value;
// 			i++;
// 		}
// 		i = 0;
// 		j = 0;
// 		tmp = tmp->next;
// 	}
// 	int k = 0;
// 	while (wd_split[k])
// 		free(wd_split[k++]);
// 	free(wd_split);
// }

// int	check(t_env *env, t_token *list)
// {
// 	proccess_dollar(env, list);
// 	// printf("check_dolar = %s\n", tmp);
// 	return (0);
// }

void if_is_quoted(char *str, int *j, int *i)
{
	(*i)++;
	(*j)++;

	while (str[*i] != '\'' && str[*i] != '\0')
	{
		(*i)++;
		(*j)++;
	}

	if (str[*i] == '\'')
	{
		(*i)++;
		(*j)++;
	}
}

char *proccess_dollar_value(char *str, t_env *env)
{
	char *tmp = malloc(sizeof(char) * 1000);
	char *return_value;
	char *finale = malloc(sizeof(char) * 1000);
	int i;
	int j;
	int y;
	int x;

	i = 0;
	j = 0;
	y = 0;
	x = 0;
	while(str[i])
	{
		while(str[i] && str[i] != '$')
		{
			finale[y] = str[i];
			i++;
			y++;
		}
		if(str[i] == '$')
		{
			i++;
			while(str[i] && str[i] != '$' && verif_token(str[i]))
			{
				tmp[j] = str[i];
				i++;
				j++;
			}
			if(str[i+1])
				return_value = dollar_value(env, tmp);
			if(return_value)
			{
				while(return_value[x])
				{
					finale[y] = return_value[x];
					y++;
					x++;
				}
			}
			tmp = NULL;
			return_value = NULL;
			j = 0;
			x = 0;
		}
		if(str[i] == '$')
		{
			finale[y++] = str[i++];
		}
	}
	printf("finale = %s\n", finale);
	return str;
}
