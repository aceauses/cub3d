/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:40:59 by rmitache          #+#    #+#             */
/*   Updated: 2024/03/20 18:49:38 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	check_inside_map(char **map)
{
	int	y;
	int	x;
	int	bad;

	y = 1;
	bad = 0;
	while (map[y] != NULL)
	{
		x = skip_first_spaces(map[y]);
		while (map[y][x] != '\0')
		{
			if (map[y][x] == ' ')
				fill(map, y, x, &bad);
			while (map[y][x] != '\0' && map[y][x] == '|')
				x++;
			x++;
		}
		y++;
	}
	if (bad > 0)
		return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
	return (1);
}

int	check_map_walls(char **map)
{
	int	y;
	int	x;
	int	bad;

	y = 1;
	bad = 0;
	while (map[y] != NULL)
	{
		x = skip_first_spaces(map[y]);
		if (map[y][x] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
			return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
		y++;
	}
	if (bad > 0)
		return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
	return (1);
}

int	check_walls(char **map)
{
	int		x;
	int		y;
	char	**map_copy;

	x = 0;
	y = 0;
	if (!find_first_character(map, &x, &y, '1'))
		return (0);
	map_copy = copy_map(map, y);
	if (!check_horizontal_walls(map_copy) || !check_inside_map(map_copy)
		|| !check_map_walls(map_copy))
		return (0);
	free_double_pointer(map_copy);
	return (1);
}
