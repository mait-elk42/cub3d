/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 15:24:58 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	check_leaks(int i)
{
	if (i == 1)
		atexit((void (*)(void))check_leaks);
	else
	{
		logger("====================leaks===========================");
		system("leaks cub3d | grep bytes");
		logger("====================lsof===========================");
		system("lsof -c cub3d");
		logger("=====================================================");
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	// check_leaks(1);`	
	data_init(&data, ac, av);
	safe_exit(0);
}
