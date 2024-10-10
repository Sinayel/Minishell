/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/10 19:42:17 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_data
{
	char   *source;
	char	**env;
	char	**str;
	char	*input;
	char	**cmd;
	int		status;
}			t_data;

// ------------  Parsing  ------------
void		for_one_word(char *str);
int			verif_word(char *str[]);
int			parsing(char *str[]);
void check_arg();

// ------------  Env  --------------
void		print_env(void);
char		*get_env(const char *var, char **env);

//--- ---------  Echo  -------------
int			echo(char *str[]);
void		print_string(char *str[], char **env);
void		print_string_with_option(char *str[]);
int			echo_for_one_caractere(char *input);

//? ------------  Utils  ------------
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncpy(char *s1, char *s2, int n);
char		**ft_split(char *str);
int			word_count(char *str);
int			ft_free(char **str);
t_data		*get_data(void);
int			ft_exit(void);
