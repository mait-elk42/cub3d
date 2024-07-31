/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/31 17:06:01 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_leaks(int i)
{
	if (i == 1)
		atexit((void (*)(void))check_leaks);
	else
	{
		printf("====================leaks===========================");
		system("leaks cub3d | grep bytes");
		printf("====================lsof===========================");
		system("lsof -c cub3d");
		printf("=====================================================");
	}
}

//norm error :) v
# error mandatory needs fix double free :: [not yet]

int	main(int ac, char **av)
{
	t_data	data;

	data_init(&data, ac, av);
	run_game(&data);
	safe_exit(0);
}
