/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 14:31:40 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/25 15:35:50 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	put_error_syscall(char *reason)
{
	ft_putstr_fd(COLOR_UNDERLINE_RED"📛error [", 2);
	ft_putstr_fd(reason, 2);
	perror("] ");
	ft_putstr_fd(COLOR_RESET, 2);
}
