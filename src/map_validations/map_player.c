/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:50:02 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/22 18:51:17 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_player(char **map)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	y = -1;
	while (map[++y] != NULL)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
				i++;
			if (map[y][x] != '1' && map[y][x] != '0' && map[y][x] != 'N'
				&& map[y][x] != 'S' && map[y][x] != 'E'
				&& map[y][x] != 'W' && map[y][x] != ' ')
				return (map_errors(INVALID_PLAYER), 0);
			x++;
		}
	}
	if (i != 1)
		return (map_errors(INVALID_PLAYER), 0);
	return (1);
}
