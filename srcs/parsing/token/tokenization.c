/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:29:09 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/12 19:56:03 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int	openquote(char *line)
{
	int		i;
	bool	squote_open;
	bool	dquote_open;

	i = 0;
	squote_open = false;
	dquote_open = false;
	while (line[i])
	{
		if (line[i] == 34 && !squote_open)
			dquote_open = !dquote_open;
		if (line[i] == 39 && !dquote_open)
			squote_open = !squote_open;
		i++;
	}
	if (squote_open || dquote_open)
		return (true);
	return (false);
}

char	*get_pid(char *str, t_data *data)
{
	int		len;
	char	*pid;
	int		pid_len;
	int		j;
	int		extra_len;
	char	*tmp;
	int i = 0;

	len = ft_strlen(str);
	pid = ft_itoa(data->pid);
	pid_len = ft_strlen(pid);
	j = 0;
	extra_len = 0;
	int k = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			extra_len += pid_len;
			i++;
		}
		i++;
	}
	printf("extra len = %d\nlen = %d\n", extra_len, len);
	tmp = malloc(sizeof(char) * (extra_len + 1));
	if (!tmp)
	{
		free(pid);
		return (NULL);
	}
	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '$' && str[i + 1] == '$')
		{
			k = 0;
			while (k < pid_len)
			{
				tmp[j++] = pid[k];
				k++;
			}
			i += 2;
		}
		else
			i++;
	}
	tmp[j] = '\0';
	free(pid);
	return (tmp);
}

// char *get_pid(char *str, t_data *data)
// {
// 	int len = ft_strlen(str);
// 	char *pid = ft_itoa(data->pid);
// 	int pid_len = ft_strlen(pid);
//     char *tmp = malloc(sizeof(char) * len + pid_len + 1);
//     int i = 0;
//     int j = 0;
//     while(i < len)
//     {
//         if(str[i] == '$' && str[i + 1] == '$')
//         {
//             int k = 0;
//             while(k < pid_len)
//             {
//                 tmp[j] = pid[k];
//                 k++;
//                 j++;
//             }
//             i += 2;
//         }
//         else
//             tmp[j++] = str[i++];
//     }
//     tmp[i] = '\0';
// 	free(pid);
//     return (tmp);
// }

static char	*extract_token(char *str, int *i)
{
	int		start;
	char	quote_type;

	start = *i;
	quote_type = '\0';
	while (str[*i] && (!ft_isspace(str[*i]) || quote_type != '\0')
		&& !is_separator(str[*i]))
	{
		if (is_quote(str[*i]))
		{
			if (quote_type == '\0')
				quote_type = str[*i];
			else if (str[*i] == quote_type)
				quote_type = '\0';
		}
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

static char	*extract_separator_token(char *str, int *i)
{
	int	start;

	start = *i;
	if ((str[*i] == '<' || str[*i] == '>') && str[*i + 1] == str[*i])
	{
		(*i) += 2;
		return (ft_substr(str, start, 2));
	}
	(*i)++;
	return (ft_substr(str, start, 1));
}

t_token	*proccess_token(t_token *list, char *str)
{
	int		i;
	char	*token;
	t_data	*data;

	i = 0;
	data = get_data();
	while (str[i])
	{
		skip_spaces(str, &i);
		if (!str[i])
			break ;
		if (is_separator(str[i]))
			token = extract_separator_token(str, &i);
		else if (str[i] == '$' && str[i + 1] == '$')
		{
			token = get_pid(str + i, data);
			i+= 2;
		}
		else
			token = extract_token(str, &i);
		if (token)
		{
			printf("token : %s\n", token);
			list = add_last(list, token);
		}
	}
	list = id_token(list);
	return (list);
}

t_token	*tokenization(char *str)
{
	t_token	*list;
	int		i;

	i = 0;
	list = NULL;
	while (str[i] == ' ')
		i++;
	if (str[i] && !openquote(str))
		list = proccess_token(list, str);
	else if (openquote(str))
		printf("open quote\n");
	return (list);
}
