/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:31:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/28 19:01:17 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_error_sys(char *reason)
{
	print(2, COLOR_UNDERLINE_RED"📛error \'", 0);
	print(2, reason, 0);
	perror("\' ");
	print(2, COLOR_RESET, 0);
}

void	eput_error_sys(char *reason, int exit_status)
{
	print(2, COLOR_UNDERLINE_RED"📛error \'", 0);
	print(2, reason, 0);
	perror("\' ");
	print(2, COLOR_RESET, 0);
	safe_exit(exit_status);
}

void	put_error(char *error, char *reason)
{
	print(2, COLOR_UNDERLINE_RED"📛error \'", 0);
	print(2, reason, 0);
	print(2, "\' : ", 0);
	print(2, error, 0);
	print(2, COLOR_RESET, 1);
}

void	eput_error(char *error, char *reason, int exit_status)
{
	print(2, COLOR_UNDERLINE_RED"📛error \'", 0);
	print(2, reason, 0);
	print(2, "\' : ", 0);
	print(2, error, 0);
	print(2, COLOR_RESET, 1);
	safe_exit(exit_status);
}
