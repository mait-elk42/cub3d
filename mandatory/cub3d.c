/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/07/31 17:16:04 by aabouqas         ###   ########.fr       */
=======
/*   Updated: 2024/07/31 17:06:01 by mait-elk         ###   ########.fr       */
>>>>>>> b309e4c49cdc0c4e4041fa5966641e16be69123f
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_leaks()
{
	// if (i == 1)

		system("leaks cub3d | grep bytes");
		// atexit((void (*)(void))check_leaks);
	// else
	// {
	// 	printf("====================leaks===========================");
	// 	system("leaks cub3d | grep bytes");
	// 	printf("====================lsof===========================");
	// 	system("lsof -c cub3d");
	// 	printf("=====================================================");
	// }
}

//norm error :) v
// # error mandatory needs fix double free :: [not yet]

int	main(int ac, char **av)
{
	t_data	data;

	atexit(check_leaks);
	data_init(&data, ac, av);
	run_game(&data);
	safe_exit(0);
}
