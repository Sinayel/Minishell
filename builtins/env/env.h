/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:26:28 by judenis           #+#    #+#             */
/*   Updated: 2024/11/06 13:47:01 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}               t_env;

char	*ft_strdup(const char *src);
void print_env_vars(t_env *head, char *name);
char *return_env_value(t_env *head, char *name);
t_env *env_import(char **envp);
size_t	ft_strlen(const char *str);
int	ft_strcmp(char *s1, char *s2);

#endif