/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/18 19:49:07 by ylouvel          ###   ########.fr       */
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
#include <sys/types.h>
#include "../libft/libft.h"
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_dollar
{
	int i;
	int j;
	int y;
	int x;
	int tmp_y;
	int len_tmp;
	int len_finale;
	char *finale;
	char *return_value;
	bool in_single_quotes;
}					t_dollar;

typedef struct s_dollar_len
{
	int i;
	int j;
	int y;
	int x;
	int len_tmp;
	bool in_single_quotes;
	char *return_value;
}					t_dollar_len;

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

typedef struct s_token
{
	char			*token;
	int				type;
	int				first;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char			*input;
	int				pid;
	int				error;
}					t_data;

// 5 -------------------  Tokenization  -------------------
t_token				*id_token(t_token *list);
t_token				*tokenization(char *str, t_env *env);
int					openquote(char *line);

// TODO -------------------  Parsing  ----------------------
int					parsing(t_token *list, t_env *env, t_data *data);

// Check dollar
char 				*proccess_dollar_value(char *str, t_env *env);
int 				len_for_dollar(char *str, t_env *env, t_dollar_len *var);
bool 				verif_token(char c);
int 				len_for_tmp(char *str);

// Pid
char				*pid_len(int len, char *pid, char *str);
char				*get_pid(int len, char *str, char *pid);
char				*proccess_pid(char *str, t_data *data);

// Check pipe,quote,redir
int					check_pipe(t_token *list);
int					check_type(t_token *list);
bool				check_unclosed_pipe(t_token *token_list);
char				*check_quote(t_token *tmp, int *i, int *j);
int					check_redirection(t_token *list);
t_token				*remove_quote(t_token *list);

//	Path
int					double_check(t_path *path, t_token *tmp);
t_path				*return_path(t_env *env);
void 				ft_free_path(t_path *path);

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
void 				echo(t_token *list);

//* -----------------------  Unset  -----------------------

//* -----------------------  Export  ----------------------

//! --------------------------------------------------------

// 3 --------------------  Liste Chainee  --------------------
void				print_list(t_token *list);
void				ft_token_lstclear(t_token **lst);
void				ft_env_lstclear(t_env **lst);
t_token				*add_last(t_token *list, char *token);
t_path				*add_env(t_path *list, char *value);

// 2 ------------------------  Error  ------------------------
int					msg_error(int value);

// 4 ------------------------  Utils  ------------------------
t_data				*get_data(void);
bool				is_separator(char c);
bool				is_redirection(char *c);
void				skip_spaces(char *str, int *i);
int					ft_strcmp(char *s1, char *s2);
bool				is_quote(char c);
int					ft_isspace(int c);
void				ft_exit(t_token *list, t_data *data, t_env *env, t_path *path);
// Dollar
char  				*free_dollar(t_dollar *var, char *tmp);
void 				return_quote(char *str, t_dollar *var);
void 				env_return_value(char *str, t_dollar *var, t_env *env, char *tmp);
void 				init_dollar_var(t_dollar *var, t_env *env, char *str);
char 				*proccess_dollar_1_on_2(t_dollar *var, char *tmp);