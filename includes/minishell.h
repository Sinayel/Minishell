/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/12/14 01:04:12 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INPUT 1   // 1  "<"
#define HEREDOC 2 // 2  "<<"
#define TRUNC 3   // 3  ">"
#define APPEND 4  // 4  ">>"
#define PIPE 5    // 5  "|"
#define CMD 6     // 6  "CMD"
#define ARG 7     // 7  "ARG"
#define INT_MIN -2147483648
#define INT_MAX 2147483647

#include "../libft/libft.h"
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_dollar
{
	int				i;
	int				j;
	int				y;
	int				x;
	int				tmp_y;
	int				len_tmp;
	int				len_finale;
	char			*finale;
	char			*return_value;
	bool			in_single_quotes;
}					t_dollar;

typedef struct s_dollar_len
{
	int				i;
	int				j;
	int				y;
	int				x;
	int				len_tmp;
	bool			in_single_quotes;
	char			*return_value;
}					t_dollar_len;

typedef struct s_export
{
	char			**content;
}					t_export;

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
	struct s_token	*prev;
}					t_token;

typedef struct s_cmd
{
	char			**cmd_arg;
	int				infile;
	int				outfile;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			*input;
	int				pid;
	int				error;
	struct s_cmd	*cmd;
}					t_data;

// 5 -------------------  Tokenization  -------------------
t_token				*tokenization(char *str, t_env *env);
t_token				*id_token(t_token *list);

// Utils token
int					openquote(char *line);
char				*extract_token(char *str, int *i);
char				*extract_separator_token(char *str, int *i);
int					while_str(char *str, int i);
int					len_for_quoted_token(char *str, int i);
char				*return_quoted_value_for_token(char *str, int *i);
void				extract_quoted_content(char *tmp, char *str, int *i,
						char quote);
void				skip_and_initialize_tmp(char **tmp, char *str, int *i,
						int len);

// TODO -------------------  Parsing  ----------------------
int					parsing_exec(t_token *list, t_env *env, t_data *data);

// Cmd
int					cmd(char **str, t_token *list, t_env *env, t_path *path);
int					check_cmd(t_token *list, t_env *env);

// Check dollar
char				*proccess_dollar_value(char *str, t_env *env);
int					len_for_dollar(char *str, t_env *env, t_dollar_len *var);
bool				verif_token(char c);
int					len_for_tmp(char *str);

// Pid
char				*pid_len(int len, char *pid, char *str);
char				*get_pid(int len, char *str, char *pid);
char				*proccess_pid(char *str);

// Check pipe,quote,redir
int					check_pipe(t_token *list);
char				*check_quote(t_token *tmp, int *i, int *j);
int					check_redirection(t_token *list);
int					for_trunc_and_heredoc(t_token *tmp);
int					return_next_next(t_token *tmp);

//	Path
int					double_check(t_path *path, char *input);
t_path				*return_path(t_env *env);
void				ft_free_path(t_path *path);

//! ------------------------  CMD  -------------------------

//* -----------------------  Env  -------------------------
int					print_env(t_env *head);
char				*return_env_value(t_env *head, char *name);
t_env				*env_import(char **envp);
void				append_env_var(t_env **head, char *name, char *value);
t_env				*create_env_var(char *name, char *value);

//* -----------------------  Pwd  -------------------------		// (JULIO)
int					ft_pwd(char *arg);
int					ft_arg_pwd(t_token *list);

//* -----------------------  Cd  --------------------------		// (JULIO)
int					ft_cd(t_env *env_list, char *input);
char				*cd_handle_dollar(t_env *env_list, char *input);
int					no_home_set(char *path, t_data *data);
void				mouv_cd(char *path, t_env *env_list, t_data *data);
int					bad_option(char *input, t_data *data);
int					option_for_cd_(char *input, t_data *data, t_env *env_list,
						char *path);
void				ch_pwd(t_env **env_list);

//* -----------------------  Exit  ------------------------		// (YANS)
int					ft_exit(t_token *list, t_env *env, t_path *path,
						char **args);
bool				is_valid_number(const char *str);
int					for_check_exit(char *str, t_token *list, t_env *env,
						t_path *path);
int					check_if_exit(t_token *list, t_env *env);
int					feat_arg_exit(t_token *list, t_env *env, t_path *path);

//* -----------------------  Echo  ------------------------		// (YANS)
int					echo(t_token *list);

//* -----------------------  Unset  -----------------------		// (JULIO)
int					ft_arg_unset(t_env *env, t_token *list);
int					len_before_space(char *arg);
void				init_var_i(int *i, int *j);
void				free_name_and_value(t_env *temp);
char				**return_dest(char **dest, t_export *export, int j);
char				**malloc_dest(t_export *export, char **dest);
void				unset_export(char *arg);
void				while_arg_split(int *i, t_env **env_list, char **arg_split);

//* -----------------------  Export  ----------------------		// (JULIO)
int					ft_arg_export(t_env *env, t_token *list);
int					ft_export(t_env *env_list, char *arg);
char				**sort_env_export(char **env_export);
t_export			*get_export(void);
char				*ft_magouilles(char *str1, char *str2, char *str3);
int					is_env_name_valid(char *name);
void				replace_env_value_ez(t_env **env_list, char *name,
						char *arg);
void				replace_env_value(t_env **env_list, char **arg);
char				**replace_one_in_export(char **export, char *arg);
char				**append_to_export(char **env_export, char *arg);
int					verif_if_in_export(char **export, char *arg);
void				export_to_env(t_env **env_list, char **arg);
void				init_export(t_export *export_list, t_env *envlist);
void				handle_valid_argument(t_env *env_list, t_export *export,
						char *arg, char *env_value);
void				handle_invalid_identifier(t_data *data, char *arg);
void				process_arguments(t_env *env_list, t_export *export,
						t_data *data, char **arg_tabtab);
char				**split_arguments(char *arg);
int					should_append_to_export(t_export *export, char *arg,
						char *env_value);
void				process_existing_export(t_env *env_list, t_export *export,
						char *env_value, char **split_arg);
void				process_new_export(t_env *env_list, t_export *export,
						char *arg, char **split_arg);
int					check_export(char **export, char **split_arg, char *arg);
int					compare_export(char *sous_str, char **split_arg, char *arg);
char				*extract_prefix(char *export_line);
int					contains_equal(char *arg);
char				*pipeline_to_env_value(t_env *envlist, char *name);
void				printf_export(char **env_export);
void				print_all_exports(char **env_export);
char				**copy_env_export(char **env_export, int new_size);
char				**add_to_env(char **temp, char *arg, int current_size);
void				print_export_line(char *env_entry);
char				**env_to_export(t_env *env_list);
int					check_equal_arg(char *arg);
char				**replace_export(char **env_export, char *split_arg);
int					get_tab_size(char **tab);
int					cmb_env(t_env *envlist);
char				*ft_magouilles_v2(char *str1, char *str2, char *str3);
int					copy_string(char *dest, char *src, int v);
int					ft_strlen_tabtab_gpt(char **split_arg);

//* -------------------------- EXEC ------------------------
t_cmd				*token_to_cmd(t_token *list);
void				print_cmd(t_cmd *list);
int					ft_exec(t_token *list, t_env *envlist, t_path *pathlist);
void	free_cmd(void);
int					len_cmd(t_cmd *list);
bool				is_builtin(char *str);

void	free_export_exec(void);

//! --------------------------------------------------------

// 3 --------------------  Liste Chainee  --------------------
void				print_list(t_token *list);
void				ft_token_lstclear(t_token **lst);
void				ft_env_lstclear(t_env **lst);
t_token				*add_last(t_token *list, char *token);
t_path				*add_env(t_path *list, char *value);

// 2 ------------------------  Error  ------------------------
int					msg_error(int value);
char				*proccess_error(char *str);

// 4 ------------------------  Utils  ------------------------
t_data				*get_data(void);
void				skip_spaces(char *str, int *i);
int					ft_strcmp(char *s1, char *s2);
void				free_all(t_token *list, t_env *env, t_path *path);

// Is ...
bool				is_separator(char c);
bool				is_redirection(char *c);
bool				is_quote(char c);
int					ft_isspace(int c);

// Ft_strtol
int					char_to_digit(char c);
int					initialize_base(const char **nptr, int base);
int					compute_sign_and_base(const char **nptr, int base,
						int *sign);
int					handle_sign(const char **nptr);
int					base_for_strtol(const char **nptr, int base);

// Dollar
char				*free_dollar(t_dollar *var, char *tmp);
void				return_quote(char *str, t_dollar *var);
char				*return_quoted_value(char *str, char *tmp, int *j, int *i);
void				env_return_value(char *str, t_dollar *var, t_env *env,
						char *tmp);
void				init_dollar_var(t_dollar *var, t_env *env, char *str);
void				free_tabtab(char **tab);
char				**ft_split_for_path(char const *s, char c);
long int			ft_strtol(const char *nptr, char **endptr, int base);

// Cd
int					ft_arg_cd(t_env *env, t_token *list);
int					cmb_word(char *str);
int					len_for_cd(t_token *list);
void				ch_oldpwd(t_env **env_list);
void				utils_ch_oldpwd(t_export *export, char *oldpwd_join,
						char *cwd, t_env **env_list);
int					cmb_word(char *str);
void				signals(void);
void				signals2(void);
void				handle_sigabrt(int code);
void				handle_sigsegv(int code);
void				signal_handler(int signum);