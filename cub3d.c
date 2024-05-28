/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/28 18:31:56 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub3d.h"

void	f()
{
	logger("====================leaks===========================");
	system("leaks cub3d | grep bytes");
	logger("====================lsof===========================");
	system("lsof -c cub3d");
	logger("=====================================================");
}

int	main(int ac, char **av)
{
	t_data	data;
	// atexit(f);

	data_init(&data, ac, av);
	// int i = 0;
	// while (data.maps[i])
	// {
	// 	printf("%s\n", data.maps[i]);
	// 	i++;
	// }
	
	safe_exit(0);
}
