/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:22:34 by ylouvel           #+#    #+#             */
/*   Updated: 2023/12/04 13:31:49 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*desttemp;
	unsigned char	*srctemp;

	desttemp = (unsigned char *)dest;
	srctemp = (unsigned char *)src;
	if ((!src) && (!dest))
		return (dest);
	while (n > 0)
	{
		*(desttemp++) = *(srctemp++);
		n--;
	}
	return (dest);
}
