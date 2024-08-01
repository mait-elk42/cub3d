/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_str1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:00:44 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 11:25:41 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

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

size_t	safe_strlen(char *str)
{
	size_t	size;

	size = 0;
	while (str && str[size])
		size++;
	return (size);
}

char	*safe_strjoin(char *str1, char *str2)
{
	char	*str;
	int		len;
	int		i;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	len = safe_strlen(str1) + safe_strlen(str2);
	str = malloc(len + 1);
	if (str == NULL)
		return (free (str1), safe_exit(1), NULL);
	i = 0;
	while (str1 && str1[i])
	{
		str[i] = str1[i];
		i++;
	}
	while (str2 && *str2)
	{
		str[i] = *str2;
		i++;
		str2++;
	}
	str[i] = '\0';
	return (free (str1), str);
}

char	*safe_strchr(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (s && *s == '\0' && c == '\0')
		return (s);
	return (NULL);
}

char	*safe_strrchr(char *s, char c)
{
	char	*save;

	save = NULL;
	while (s && *s)
	{
		if (*s == c)
			save = s;
		s++;
	}
	if (s && *s == '\0' && c == '\0')
		save = s;
	return (save);
}
