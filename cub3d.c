/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 17:58:58 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_leaks(int i)
{
	if (i == 1)
		atexit((void (*)(void))check_leaks);
	else
	{
		printf("====================leaks===========================\n");
		system("leaks cub3d");
		printf("====================lsof===========================\n");
		system("lsof -c cub3d");
		printf("=====================================================\n");
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	check_leaks(1);
	data_init(&data, ac, av);
	run_game(&data);
	safe_exit(0);
}
