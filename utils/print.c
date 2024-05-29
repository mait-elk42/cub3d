/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:23:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 10:35:10 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
