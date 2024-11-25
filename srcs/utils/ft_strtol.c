/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:36:56 by ylouvel           #+#    #+#             */
/*   Updated: 2024/11/22 18:41:01 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int base_for_strtol(const char **nptr, int base)
{
    while (**nptr && (**nptr == ' ' || **nptr == '\t' || **nptr == '\n'))
        (*nptr)++;
    if ((base != 0 && base < 2) || base > 36) 
        return 0;

    if (base == 0)
    {
        if (**nptr == '0')
        {
            (*nptr)++;
            if (**nptr == 'x' || **nptr == 'X')
            {
                (*nptr)++;
                return 16;
            }
            return 8;
        }
        return 10;
    }
    return base;
}

int handle_sign(const char **nptr)
{
    int sign = 1;
    if (**nptr == '-')
    {
        sign = -1;
        (*nptr)++;
    }
    else if (**nptr == '+')
        (*nptr)++;
    return sign;
}

int char_to_digit(char c)
{
    if (c >= '0' && c <= '9')
        return c - '0';
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 10;
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 10;
    return -1;
}

long int ft_strtol(const char *nptr, char **endptr, int base)
{
    long int result;
    int sign;
    int digit;
    result = 0;
    sign = 0;
    digit = 0;
    base = base_for_strtol(&nptr, base);
    if (base == 0)
    {
        if (endptr)
            *endptr = (char *)nptr;
        return 0;
    }
    sign = handle_sign(&nptr);
    while (*nptr)
    {
        digit = char_to_digit(*nptr);
        if (digit < 0 || digit >= base)
            break;
        result = result * base + digit;
        nptr++;
    }
    if (endptr)
        *endptr = (char *)nptr;
    return sign * result;
}
