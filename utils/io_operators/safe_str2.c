/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:21:53 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 10:47:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

void	free_tab(char **array)
{
	size_t	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
