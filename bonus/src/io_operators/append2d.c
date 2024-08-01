/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouqas <aabouqas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 10:15:45 by mait-elk          #+#    #+#             */
/*   Updated: 2024/08/01 11:18:37 by aabouqas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

char	**append_2d(char **old_tab, char *to_append)
{
	char	**new_tab;
	size_t	tab_len;
	size_t	i;

	if (to_append == NULL)
		return (old_tab);
	if (old_tab == NULL)
	{
		new_tab = safe_calloc(2 * sizeof(char *));
		*new_tab = to_append;
		return (new_tab);
	}
	tab_len = 0;
	while (old_tab[tab_len])
		tab_len++;
	new_tab = safe_calloc((tab_len + 2) * sizeof(char *));
	i = 0;
	while (i < tab_len)
	{
		new_tab[i] = old_tab[i];
		i++;
	}
	free(old_tab);
	new_tab[i] = to_append;
	return (new_tab);
}
