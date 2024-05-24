/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:23:21 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/24 17:24:11 by mait-elk         ###   ########.fr       */
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
