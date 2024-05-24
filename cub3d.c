/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/24 19:17:54 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	check_args(int ac, char **av)
{
	ac += (int)av * 0;
	if (ac != 2)
	{
		print(2, "cub3d: bad arguments", 1);
		exit (1);
	}
}

int	main(int ac, char **av)
{
	check_args(ac, av);
	write(1, "hello world\n", 12);
}