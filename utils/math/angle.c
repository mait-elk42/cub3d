/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:48 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/13 13:46:49 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	normalize_angle(float angle)
{
	// this function makes the angle between 0 and 360°
	// (2.0 * M_PI) means 360°
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
