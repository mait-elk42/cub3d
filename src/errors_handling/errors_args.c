/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-elk <mait-elk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:22:17 by mait-elk          #+#    #+#             */
/*   Updated: 2024/05/29 10:47:09 by mait-elk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

bool	check_file_ext(char *file_name, char *ext)
{
	char	*file_extension;

	file_extension = safe_strrchr(file_name, '.');
	if (str_equal(file_extension, ext) == 0)
	{
		put_error("Invalid file extension", file_name);
		return (false);
	}
	return (true);
}

void	check_file(int ac, char **av)
{
	int		fd;

	if (ac != 2)
		eput_error("bad input", "[argv]", 1);
	if (check_file_ext(av[1], ".cub") == false)
		safe_exit(1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
	{
		if (fd != -1)
			close(fd);
		put_error_sys(av[1]);
		exit(1);
	}
	data_hook(NULL)->fd_file_input = fd;
}
