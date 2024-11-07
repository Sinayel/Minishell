/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:26:28 by judenis           #+#    #+#             */
/*   Updated: 2024/11/07 19:00:46 by judenis          ###   ########.fr       */
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
# include <errno.h>

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}               t_env;

char	*ft_strdup(const char *src);
void print_env_vars(t_env *head, char *name);
char *return_env_value(t_env *head, char *name);
void print_env(t_env *head);
t_env *env_import(char **envp);
size_t	ft_strlen(const char *str);
int	ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);
int	ft_strncmp(char *s1, char *s2, unsigned int n);
void env_create_pwd(t_env **env_list);
void env_create_oldpwd(t_env **env_list);

void ft_free_env(t_env **lst);

#endif