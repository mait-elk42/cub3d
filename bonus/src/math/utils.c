/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:26:23 by mait-elk          #+#    #+#             */
/*   Updated: 2024/07/31 12:26:29 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	irange(int *v, int min, int max)
{
	if (*v > max)
		*v = max;
	else if (*v < min)
		*v = min;
}

int	iinrange(int n, int min, int max)
{
	if (n > max || n < min)
		return (0);
	return (1);
}
