/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:09:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 10:56:15 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void ch()
{
	printf("====================leaks===========================\n");
	system("leaks cub3d");
	printf("====================lsof===========================\n");
	system("lsof -c cub3d");
	printf("=====================================================\n");
}


int	main(int ac, char **av)
{
	t_data	data;

	atexit(ch);
	data_init(&data, ac, av);
	data.game_started = false;
	// play_music();
	run_game(&data);
	safe_exit(0);
	exit (0);
}
