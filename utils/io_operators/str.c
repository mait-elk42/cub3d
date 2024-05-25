/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:00:44 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 11:13:54 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	*safe_calloc(size_t size)
{
	char	*res;

	res = malloc(size);
	if (res == NULL)
		safe_exit(1);
	while (size--)
		res[size] = '\0';
	return ((void *)res);
}
