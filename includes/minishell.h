/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/26 21:23:14 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INPUT 1   // 3 "<"
#define HEREDOC 2 // 3 "<<"
#define TRUNC 3   // 3 ">"
#define APPEND 4  // 3 ">>"
#define PIPE 5    // 1 "|"
#define CMD 6     // 1 "|"
#define ARG 7     // 1 "|"

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_split
{
	int				i;
	int				j;
	int				k;
}				t_split;

typedef struct s_data
{
	char			*token;
	char			*input;
	char			**env;
}				t_data;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}				t_token;

// typedef struct s_data
// {
// 	char			**env;
// 	char			*input;
// 	char			*inter;
// 	int exec_value;      // Valleur de retour pour "$?"
// 	char *before;        //? dollar_check
// 	char **str;          // Input en double tableau
// 	char *var_end;       //? print_with_vars
// 	char *var_name;      //? print_with_vars
// 	size_t len;          //? print_with_vars
// 	char *dollar_pos;    //? print_with_vars
// 	char *env_value;     //? print_with_vars
// 	char *inside_quotes; //* print_string
// 	char *current_str;   //* print_string
// 	struct s_data	*next;
// }					t_data;

// TODO ------------------  Parsing  ----------------------
int					args(char *str);
int					check_cmd(t_token *list);

//! ------------------------  CMD  ------------------------

//* ------------------------  Env  ------------------------
void				print_env(void);
char				*get_env(const char *var, char **env);

//* -----------------------  Echo  ------------------------
// int					echo(char *str[]);
// int					print_string(char *str[]);
// void				write_env_var(char **str, char **env);
// void				print_with_vars(char *str, char **env);
// void				print_string_with_option(char *str[]);
// int					echo_for_one_caractere(char *input);

//! --------------------------------------------------------

// 3 --------------------  Liste Chainee  --------------------
void				print_list(t_token *list);
void				ft_lstclear(t_token **lst);
t_token				*add_last(t_token *list, char *token);
t_token *tokenization(char *str);

//* ------------------------  Error  ------------------------

//? ------------------------  Utils  ------------------------
// int					ft_strcmp(const char *s1, const char *s2);
// char				*ft_strncpy(char *s1, char *s2, int n);
// char				**ft_split(char *str);
// int					word_count(char *str);
t_data				*get_data(void);
t_split 			*get_data_split(void);

// create_token (26 lignes sur le ft_split_pipe)
void				init_var();
int					word_count_pipe(char *str);
char 				**for_pipe(char **out, int k, char str);