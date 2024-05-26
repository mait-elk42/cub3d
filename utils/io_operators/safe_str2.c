/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:21:53 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 15:22:34 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*safe_strdup(char *s)
{
	size_t	i;
	char	*res;

	i = 0;
	res = malloc(ft_strlen(s) + 1);
	if (!res)
		safe_exit(1);
	while (*s)
	{
		res[i] = *s;
		s++;
		i++;
	}
	res[i] = '\0';
	return (res);
}