/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
<<<<<<< HEAD:bonus/cub3d_bonus.c
/*   Updated: 2024/08/01 15:32:15 by aabouqas         ###   ########.fr       */
=======
/*   Updated: 2024/08/01 16:12:32 by mait-elk         ###   ########.fr       */
>>>>>>> b99abdca85ed5e0178530524ee7e32ec6f8122e3:cub3d_bonus.c
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	check_leaks(int i)
{
	if (i == 1)
		atexit((void (*)(void))check_leaks);
	else
	{
		printf("====================leaks===========================\n");
		system("leaks cub3d_bonus");
		// printf("==================================================\n");
		// printf("====================lsof===========================\n");
		// system("lsof -c cub3d");
		// printf("=====================================================\n");
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	check_leaks(1);
	data_init(&data, ac, av);
	data.game_started = false;
	run_game(&data);
	safe_exit(0);
}