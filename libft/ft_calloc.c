/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 17:27:08 by ylouvel           #+#    #+#             */
/*   Updated: 2023/12/04 12:56:24 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Sert a initialiser un tableau de taille "size" et de type "count".
Par exemple si je veux initialiser mon tableau de taille 5 et de type char,
j'ai juste a appeler ma fonction calloc qui l'initialisera,
a 0 pour un type char avec la fonction bzero
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*element;

	if (size != 0 && count > (size_t)-1 / size)
		return (NULL);
	element = malloc(count * size);
	if (!element)
		return (NULL);
	ft_bzero(element, (count * size));
	return (element);
}
