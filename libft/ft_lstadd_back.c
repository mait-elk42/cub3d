/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:54:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/03/14 13:45:27 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *_new)
{
	t_list	*i;

	if (!lst || !_new)
		return ;
	if (!*lst)
	{
		*lst = _new;
		return ;
	}
	i = *lst;
	while (i->next)
		i = i->next;
	i->next = _new;
}
