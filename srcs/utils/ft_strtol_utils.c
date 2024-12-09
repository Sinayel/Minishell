/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 16:33:45 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 16:34:07 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	char_to_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

int	initialize_base(const char **nptr, int base)
{
	base = base_for_strtol(nptr, base);
	return (base);
}

int	compute_sign_and_base(const char **nptr, int base, int *sign)
{
	base = initialize_base(nptr, base);
	if (base == 0)
		return (0);
	*sign = handle_sign(nptr);
	return (base);
}
