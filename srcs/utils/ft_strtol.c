/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:36:56 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/28 16:34:00 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	base_for_strtol(const char **nptr, int base)
{
	while (**nptr && (**nptr == ' ' || **nptr == '\t' || **nptr == '\n'))
		(*nptr)++;
	if ((base != 0 && base < 2) || base > 36)
		return (0);
	if (base == 0)
	{
		if (**nptr == '0')
		{
			(*nptr)++;
			if (**nptr == 'x' || **nptr == 'X')
			{
				(*nptr)++;
				return (16);
			}
			return (8);
		}
		return (10);
	}
	return (base);
}

int	handle_sign(const char **nptr)
{
	int	sign;

	sign = 1;
	if (**nptr == '-')
	{
		sign = -1;
		(*nptr)++;
	}
	else if (**nptr == '+')
		(*nptr)++;
	return (sign);
}

long int	parse_number(const char **nptr, int base)
{
	long int	result;
	int			digit;

	result = 0;
	while (**nptr)
	{
		digit = char_to_digit(**nptr);
		if (digit < 0 || digit >= base)
			break ;
		result = result * base + digit;
		(*nptr)++;
	}
	return (result);
}

long int	ft_strtol(const char *nptr, char **endptr, int base)
{
	long int	result;
	int			sign;

	base = compute_sign_and_base(&nptr, base, &sign);
	if (base == 0)
	{
		if (endptr)
			*endptr = (char *)nptr;
		return (0);
	}
	result = parse_number(&nptr, base);
	if (endptr)
		*endptr = (char *)nptr;
	return (sign * result);
}
