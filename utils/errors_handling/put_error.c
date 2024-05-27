/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:31:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/27 17:11:26 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_error_sys(char *reason)
{
	print(2, COLOR_UNDERLINE_RED"📛error \'", 0);
	ft_putstr_fd(COLOR_UNDERLINE_RED"📛error \'", 2);
	print(2, reason, 0);
	print(2, "\' ", 0);
	print(2, COLOR_RESET, 1);
}

int	put_error(char *error, char *reason)
{
	print(2, COLOR_UNDERLINE_RED"📛error \'", 0);
	print(2, reason, 0);
	print(2, "\' : ", 0);
	print(2, error, 0);
	print(2, COLOR_RESET, 1);
	return (1);
}

void	eput_error_custom(char *error, char *reason, int exit_status)
{
	ft_putstr_fd(COLOR_UNDERLINE_RED"📛error \'", 2);
	ft_putstr_fd(reason, 2);
	ft_putstr_fd("\' : ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(COLOR_RESET, 2);
	safe_exit(exit_status);
}