/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/28 18:31:33 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INPUT 1   // 3 "<"
#define HEREDOC 2 // 3 "<<"
#define TRUNC 3   // 3 ">"
#define APPEND 4  // 3 ">>"
#define PIPE 5    // 1 "|"
#define CMD 6     // 1 "|"
#define ARG 7     // 1 "|"

#include "../../libft/libft.h"
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
}					t_split;

typedef struct s_data
{
	char			*token;
	char			*input;
	char			**env;
}					t_data;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}					t_token;

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
t_token 			*id_token(t_token *list);
t_token				*tokenization(char *str);

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
void				ft_token_lstclear(t_token **lst);
t_token				*add_last(t_token *list, char *token);

//* ------------------------  Error  ------------------------

//? ------------------------  Utils  ------------------------
t_data				*get_data(void);
t_split				*get_data_split(void);
void				skip_spaces(int *i, char *str);
char				*extract_token(char *str, int *i, int j);
void				handle_separator(char **str, int *i, t_token **list);
