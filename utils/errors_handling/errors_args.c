/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:22:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/27 14:58:48 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_extension(char *file_name, char *ext)
{
	char	*start_point;

	start_point = safe_strrchr(file_name, '.');
	if (str_equal(start_point, ext) == 0)
	{
		put_error("Invalid file name", "Extension");
		return (0);
	}
	return (1);
}

int	check_file(int ac, char **av)
{
	int		fd;

	if (ac != 2)
		exit (put_error("bad input", "[argv]"));
	if (check_extension(av[1], ".cub") == 0)
		exit(1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		put_error_sys(av[1]);
		exit(1);
	}
	return (fd);
}
