/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:38:30 by aabouqas          #+#    #+#             */
/*   Updated: 2024/05/25 11:27:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

const char	*skip_whitespaces(const char *str)
{
	while (str && *str && ((*str >= 9 && *str <= 13) || (*str == 32)))
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int		s;
	long	r;

	s = 1;
	r = 0;
	str = skip_whitespaces(str);
	if (str && *str == '-')
		s = -1;
	str += (*str == '-' || *str == '+');
	while (*str && ft_isdigit(*str))
	{
		r = r * 10 + (*str - 48);
		if((s == 1 && r < 0) || (s == -1 && (r * (-1)) > 0))
		{
			if(s == 1)
				return -1;
			return 0;
		}
		str++;
	}
	return (r * s);
}

