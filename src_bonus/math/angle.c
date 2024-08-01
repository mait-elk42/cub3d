/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:48 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/22 18:19:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

float	normalize_angle(float angle)
{
	if (angle > (2.0 * M_PI))
		angle -= (2.0 * M_PI);
	else if (angle < 0)
		angle += (2.0 * M_PI);
	return (angle);
}

float	deg_to_rad(float angle)
{
	return (normalize_angle((angle * M_PI) / 180.0));
}
