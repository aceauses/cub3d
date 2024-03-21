/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:00:02 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/20 18:42:35 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	find_first_character(char **map, int *x, int *y, int C)
{
	int	y_m;
	int	x_m;

	y_m = 0;
	while (map && map[y_m] != NULL)
	{
		x_m = 0;
		while (map[y_m][x_m] == ' '
			&& (map[y_m][x_m] != C && map[y_m][x_m] != '\0'))
			x_m++;
		if (!ft_strncmp(map[y_m], "SO", 2) || !ft_strncmp(map[y_m], "NO", 2)
			|| !ft_strncmp(map[y_m], "WE", 2) || !ft_strncmp(map[y_m], "EA", 2)
			|| !ft_strncmp(map[y_m], "F", 1) || !ft_strncmp(map[y_m], "C", 1))
		{
			y_m++;
			continue ;
		}
		while (map[y_m][x_m] != '\0' && map[y_m][x_m] != ' ')
		{
			if (map[y_m][x_m++] == C)
				return (*x = x_m, *y = y_m, 1);
		}
		y_m++;
	}
	return (0);
}

/*Function to copy a double pointer and return a new double pointer*/
char	**copy_map(char **matrix, int y)
{
	char	**copied;
	int		y_c;

	y_c = 0;
	while (matrix[y + y_c] != NULL)
		y_c++;
	copied = malloc(sizeof(char *) * (y_c + 1));
	if (!copied)
		return (NULL);
	y_c = 0;
	while (matrix[y + y_c] != NULL)
	{
		copied[y_c] = ft_strdup(matrix[y + y_c]);
		y_c++;
	}
	copied[y_c] = NULL;
	return (copied);
}

void	fill(char **matrix, int y, int x, int *good)
{
	if (y < 0 || x < 0 || matrix[y] == NULL || x >= (int)ft_strlen(matrix[y]))
		return ;
	if (matrix[y][x] == '\0' || matrix[y][x] == '0')
	{
		*good += 1;
		return ;
	}
	if (matrix[y][x] == '\0' || matrix[y][x] == '1'
		|| matrix[y][x] == '0' || matrix[y][x] == '|')
		return ;
	matrix[y][x] = '|';
	fill(matrix, y, x + 1, good);
	fill(matrix, y, x - 1, good);
	fill(matrix, y + 1, x, good);
	fill(matrix, y - 1, x, good);
	fill(matrix, y + 1, x + 1, good);
	fill(matrix, y + 1, x - 1, good);
	fill(matrix, y - 1, x + 1, good);
	fill(matrix, y - 1, x - 1, good);
}

int	skip_first_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int	check_horizontal_walls(char **map)
{
	int	x;
	int	y;
	int	bad;

	y = 0;
	bad = 0;
	if (map[y] != NULL)
	{
		x = skip_first_spaces(map[y]);
		while (map[y][x] != '\0' && map[y][x] == '1')
			x++;
		if (map[y][x] != '\0' && map[y][x] == ' ')
			fill(map, y, x, &bad);
		if (bad > 0)
			return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
		while (map[y][x] != '\0' && map[y][x] == '|')
			x++;
		while (map[y][x] != '\0' && map[y][x] == '1')
			x++;
		if (map[y][x] == '\0')
			return (1);
		else
			return (map_errors(INVALID_MAP), free_double_pointer(map), 0);
	}
	return (1);
}
