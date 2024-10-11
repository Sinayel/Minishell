/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judenis <judenis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:53:06 by judenis           #+#    #+#             */
/*   Updated: 2024/10/09 12:08:38 by judenis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <string.h>

typedef struct s_data
{
    char *input;
    char **str;

    int word_count;
}              t_data;

char	**ft_split(char *str);
int	    word_count(char *str);
int	    ft_strcmp(const char *s1, const char *s2);
char	*ft_strncpy(char *s1, char *s2, int n);
int	    parsing(void);
int     ft_pwd(void);
int     ft_exit(void);
int     ft_free(char **str);
t_data *get_data(void);

#endif