/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 18:17:48 by mait-elk          #+#    #+#             */
/*   Updated: 2024/06/04 16:13:31 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

double	periodic(double angle)
{
	if (angle > 2.0 * M_PI)
		angle -= 2.0 * M_PI;
	else if (angle < 0)
		angle += 2.0 * M_PI;
	return (angle);
}


double	mth_degtorad(double angle)
{
	return (periodic((angle * M_PI) / 180.0));
}
