/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:31:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 14:17:22 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_error_syscall(char *reason)
{
	ft_putstr_fd(COLOR_UNDERLINE_RED"📛error \'", 2);
	ft_putstr_fd(reason, 2);
	perror("\' ");
	ft_putstr_fd(COLOR_RESET, 2);
}

void	put_error_custom(char *error, char *reason)
{
	ft_putstr_fd(COLOR_UNDERLINE_RED"📛error \'", 2);
	ft_putstr_fd(reason, 2);
	ft_putstr_fd("\' : ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(COLOR_RESET, 2);
}
