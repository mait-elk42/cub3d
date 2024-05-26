/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:22:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 09:49:29 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	check_args(int ac, char **av)
{
	(void)av;
	if (ac != 2)
	{
		put_error_custom("too many args");
		exit (1);
	}
}
