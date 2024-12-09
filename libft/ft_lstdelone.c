/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylouvel <ylouvel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:01:52 by ylouvel           #+#    #+#             */
/*   Updated: 2023/12/04 13:04:53 by ylouvel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Supprime un seul element d'une liste chainer en utilisant une fonction del

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && (*del))
	{
		(*del)(lst->content);
		free(lst);
	}
}
