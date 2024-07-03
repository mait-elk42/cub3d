/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:48 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/02 19:11:10 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	periodic(float angle)
{
	if (angle > 2.0 * M_PI)
		angle -= 2.0 * M_PI;
	else if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}


float	mth_degtorad(float angle)
{
	return (periodic((angle * M_PI) / 180.0));
}
