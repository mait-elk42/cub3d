/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:07:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 10:20:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <math.h>

/**
 * ERRORS HANDLING
*/
void	check_args(int ac, char **av);

/**
 * IO OPERATORS
*/
void	print(int fd, char *msg, int endl);
