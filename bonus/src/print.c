/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:23:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/22 18:19:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	print(int fd, char *msg, int endl)
{
	size_t	len;

	len = 0;
	while (msg && msg[len])
		len++;
	write (fd, msg, len);
	if (endl)
		write (fd, "\n", 1);
}

void	print_2d(char **arr)
{
	while (*arr)
	{
		print(1, "[", 0);
		print(1, *arr, 0);
		print(1, "]", 1);
		arr++;
	}
}
