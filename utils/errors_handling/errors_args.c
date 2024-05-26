/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:22:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/26 12:22:49 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_file(int ac, char **av)
{
	char	*start_point;
	int		fd;

	if (ac != 2)
	{
		put_error_custom("bad args");
		exit (1);
	}
	start_point = safe_strrchr(av[1], '.');
	if (str_equal(start_point, ".cub") == 0)
	{
		put_error_custom("Invalid file name");
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		put_error_syscall(av[1]);
		exit(1);
	}
	return (fd);
}
