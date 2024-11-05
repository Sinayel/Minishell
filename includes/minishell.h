/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/05 20:05:39 by ylouvel          ###   ########.fr       */
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
#include <readline/history.h>
#include <readline/readline.h>
#include "../libft/libft.h"
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
t_token 			*tokenization(char *str);
int					openquote(char *line);


//TODO -------------------  Parsing  ----------------------
int 	   			parsing(t_token *list);
int	    			check_pipe(t_token *list);
t_token 			*remove_quote(t_token *list);


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
bool				is_separator(char c);
void				skip_spaces(char *str, int *i);
void				ft_del_one_token(t_token *lst);
