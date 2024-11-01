/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/31 17:31:16 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INPUT 1   //1  "<"
#define HEREDOC 2 //2  "<<"
#define TRUNC 3   //3  ">"
#define APPEND 4  //4  ">>"
#define PIPE 5    //5  "|"
#define CMD 6     //6  "CMD"
#define ARG 7     //7  "ARG"

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
	bool 			should_break;
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
	int				first;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

//5 -------------------  Tokenization  -------------------
t_token				*id_token(t_token *list);
t_token				*tokenization(char *str);


//TODO -------------------  Parsing  ----------------------
int 	   			parsing(t_token *list);
int	    			check_pipe(t_token *list);


//! ------------------------  CMD  ------------------------

//* -----------------------  Env  -------------------------
void				print_env(void);
char				*get_env(const char *var, char **env);

//* -----------------------  Pwd  -------------------------		// (JULIO)

//* -----------------------  Cd  --------------------------		// (JULIO)

//* -----------------------  Exit  ------------------------

//* -----------------------  Echo  ------------------------

//* -----------------------  Unset  -----------------------

//* -----------------------  Export  ----------------------

//! --------------------------------------------------------


// 3 --------------------  Liste Chainee  --------------------
void				print_list(t_token *list);
void				ft_token_lstclear(t_token **lst);
t_token				*add_last(t_token *list, char *token);


//2 ------------------------  Error  ------------------------


//4 ------------------------  Utils  ------------------------
t_data				*get_data(void);
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
