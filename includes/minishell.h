/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/29 19:58:45 by ylouvel          ###   ########.fr       */
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
#include "../libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_quote_state
{
	bool			squote_open;
	bool			dquote_open;
	bool			in_squote;
	bool			in_dquote;
	bool should_break ;
	int				quote_type;
}					t_quote_state;

typedef struct s_data
{
	char			*token;
	char			*input;
	char			**env;
	int				error;
}					t_data;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// TODO ------------------  Parsing  ----------------------
void				handle_quoted_content(const char *str, int *i,
						bool *in_squote, bool *in_dquote);
bool				is_separator(char c);
void				process_token_char(const char *str, int *i, bool has_quotes,
						t_quote_state *state);
void				handle_quotes(const char *str, int *i, int quote_type,
						t_quote_state *state);
bool				should_break_token(const char *str, int i, bool has_quotes,
						bool in_squote, bool in_dquote);
bool				is_quoted(const char *str, int pos);
void				update_quote_state(char c, bool *in_squote,
						bool *in_dquote);
bool				has_unclosed_quotes(const char *line);
void				skip_spaces(const char *str, int *i);
t_token				*id_token(t_token *list);
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
