/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:31:18 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/25 15:52:11 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	msg_error(int value)
{
	if (value == 1)
		printf("minishell: syntax error near unexpected token `newline'\n");
	if (value == 2)
		printf("minishell: syntax error unexpected token `|'\n");
	if (value == 3)
		printf("open quote\n");
	if (value == 4)
		printf("minishell: first pipe not allowed !\n");
	return (1);
}
