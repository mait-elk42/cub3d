/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_effect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:29:57 by aabouqas          #+#    #+#             */
/*   Updated: 2024/07/24 20:19:14 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	play_effect(char *file_name)
{
	int		child;
	char	*prog_path;

	child = fork();
	if (child == 0)
	{
		prog_path = "afplay";
		execvp(prog_path, (char *[]){"afplay", file_name, NULL});
		exit(1);
	}
}
