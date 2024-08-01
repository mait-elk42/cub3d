/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:55:25 by aabouqas          #+#    #+#             */
/*   Updated: 2024/08/01 11:24:46 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	str_equal(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	strn_equal(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*str_skip(char *str, char *chars_to_skip)
{
	while (str != NULL && *str != '\0' && safe_strchr(chars_to_skip, *str))
		str++;
	return (str);
}

char	*str_skip_wsp(char *str)
{
	while (str && ft_iswhite(*str))
		str++;
	return (str);
}
