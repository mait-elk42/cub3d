/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:21:53 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 11:26:12 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

char	*safe_strdup(char *s)
{
	size_t	i;
	char	*res;

	i = 0;
	if (s == NULL)
		return (NULL);
	res = malloc(ft_strlen(s) + 1);
	if (res == NULL)
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
