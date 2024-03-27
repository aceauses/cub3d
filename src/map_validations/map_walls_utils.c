/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:40:59 by rmitache          #+#    #+#             */
/*   Updated: 2024/03/27 12:23:48 by aceauses         ###   ########.fr       */
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
	int		y;
	int		x;

	y = 1;
	while (map[y] != NULL)
	{
		x = skip_first_spaces(map[y]);
		if (map[y][x] != '1' || map[y][ft_strlen(map[y]) - 1] != '1')
			return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
		y++;
	}
	return (1);
}

void	normal_flood_fill(char **map, int y, int x, int *good)
{
	if (y < 0 || x < 0 || map[y] == NULL || x >= (int)ft_strlen(map[y]))
	{
		*good += 1;
		return ;
	}
	if (map[y][x] == '\0')
		return ;
	if (map[y][x] == '\0' || map[y][x] == '1' || map[y][x] == '|')
		return ;
	map[y][x] = '|';
	normal_flood_fill(map, y, x + 1, good);
	normal_flood_fill(map, y, x - 1, good);
	normal_flood_fill(map, y + 1, x, good);
	normal_flood_fill(map, y - 1, x, good);
}

int	flood_player(char **map)
{
	int	x;
	int	y;
	int	good;

	x = 0;
	y = 0;
	good = 0;
	if (!find_first_character(map, &x, &y, 'N')
		&& !find_first_character(map, &x, &y, 'S')
		&& !find_first_character(map, &x, &y, 'E')
		&& !find_first_character(map, &x, &y, 'W'))
		return (map_errors("Couldn't Find Player For Food Fill"), 0);
	normal_flood_fill(map, y, x, &good);
	if (good != 0)
		return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
	return (1);
}

int	check_walls(char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (!find_first_character(map, &x, &y, '1'))
		return (0);
	if (!check_horizontal_walls(copy_map(map, y))
		|| !check_player(copy_map(map, y))
		|| !flood_player(copy_map(map, y))
		|| !check_inside_map(copy_map(map, y))
		|| !check_map_walls(copy_map(map, y)))
		return (0);
	return (1);
}