/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/11 20:31:13 by ylouvel          ###   ########.fr       */
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
	char	**env;
	char	*input;
	char	**str; // Input en double tableau
	char	*var_end; //? print_with_vars
	char	*var_name; //? print_with_vars
	size_t	len; //? print_with_vars
	char	*dollar_pos; //? print_with_vars
	char	*env_value; //? print_with_vars
	int		inside_quotes; //* print_string
	char	*current_str; //* print_string
}			t_data;

//TODO --------------------  Parsing  --------------------
void		for_one_word(char *str);
int			verif_word(char *str[]);
int			parsing(char *str[]);
void		msg_dollar(const char *before, const char *env_var);
char		*dollar_check(char **before, char **env_var);

//! -----------------------  Cmd  ----------------------------

//* --------------------  Env  --------------------
void		print_env(void);
char		*get_env(const char *var, char **env);

//* --------------------  Echo  --------------------
int			echo(char *str[]);
int			print_string(char *str[]);
void		write_env_var(char **str, char **env);
void		print_with_vars(char *str, char **env);
void		print_string_with_option(char *str[]);
int			echo_for_one_caractere(char *input);

//! ----------------------------------------------------------


//? --------------------  Utils  --------------------
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strncpy(char *s1, char *s2, int n);
char		**ft_split(char *str);
int			word_count(char *str);
int			ft_free(char **str);
t_data		*get_data(void);
int			ft_exit(void);
