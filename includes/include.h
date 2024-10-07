/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:16:23 by ylouvel           #+#    #+#             */
/*   Updated: 2024/10/07 19:55:14 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// TODO -----------  Echo  -----------
int		echo(char *str[]);
void	print_string(char *str[]);
void	print_string_with_option(char *str[]);
int		echo_for_one_caractere(char *input);

//? ------------  Utils  ------------
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char *str);
int		word_count(char *str);
