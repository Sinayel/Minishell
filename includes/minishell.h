/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/06 21:15:19 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INPUT 1   // 1  "<"
#define HEREDOC 2 // 2  "<<"
#define TRUNC 3   // 3  ">"
#define APPEND 4  // 4  ">>"
#define PIPE 5    // 5  "|"
#define CMD 6     // 6  "CMD"
#define ARG 7     // 7  "ARG"

#include <stdio.h>
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_path
{
	char			*name;
	struct s_path	*next;
}					t_path;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			*token;
	char			*input;
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

// 5 -------------------  Tokenization  -------------------
t_token				*id_token(t_token *list);
t_token				*tokenization(char *str);
int					openquote(char *line);

// TODO -------------------  Parsing  ----------------------
int					parsing(t_token *list, t_env *env);

// Check pipe,quote,redir
int					check_pipe(t_token *list);
char				*check_quote(t_token *tmp, int *i, int *j);
int					check_redirection(t_token *list);
t_token				*remove_quote(t_token *list);

//	Path
int					double_check(t_path *path, t_token *tmp);
t_path				*return_path(t_env *env);

//! ------------------------  CMD  ------------------------

//* -----------------------  Env  -------------------------
void				print_env_vars(t_env *head, char *name);
char				*return_env_value(t_env *head, char *name);
t_env				*env_import(char **envp);
void				append_env_var(t_env **head, char *name, char *value);
t_env				*create_env_var(char *name, char *value);

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
void				ft_env_lstclear(t_env *lst);
t_token				*add_last(t_token *list, char *token);
t_path				*add_env(t_path *list, char *value);

// 2 ------------------------  Error  ------------------------
int					msg_error(int value);

// 4 ------------------------  Utils  ------------------------
t_data				*get_data(void);
bool				is_separator(char c);
void				skip_spaces(char *str, int *i);
void				ft_del_one_token(t_token *lst);
int					ft_strcmp(char *s1, char *s2);
