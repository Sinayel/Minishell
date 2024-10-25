/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/25 21:46:15 by ylouvel          ###   ########.fr       */
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

typedef struct s_data
{
	int				i;
	int				j;
	int				k;
	char			*value;
	char			**first_split;
	char			*input;
	int				type;
	char			**env;
	struct s_data	*next;
}					t_data;

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
int					check_cmd(t_data *list);

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
void				print_list(t_data *head);
void				ft_lstclear(t_data **lst);
t_data				*add_last(t_data *list, char *value);
t_data				*init_list(t_data *list);

//* ------------------------  Error  ------------------------

//? ------------------------  Utils  ------------------------
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strncpy(char *s1, char *s2, int n);
char				**ft_split(char *str);
int					word_count(char *str);
t_data				*get_data(void);

// Split_pipe (26 lignes sur le ft_split_pipe)
void				init_var();
char				**ft_split_pipe(char *str);
int					word_count_pipe(char *str);
char 				**for_pipe(char **out, int k);