/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:48 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/20 14:52:30 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	normalize_angle_d(float angle_deg)
{
	if (angle_deg > 360)
		angle_deg -= 360;
	else if (angle_deg < 0)
		angle_deg += 360;
	return (angle_deg);
}

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
