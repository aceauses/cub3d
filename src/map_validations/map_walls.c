/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:00:02 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/05 20:23:49 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	find_first_wall(char **map, int *x, int *y)
{
	int	y_m;
	int	x_m;

	y_m = 0;
	while (map && map[y_m] != NULL)
	{
		x_m = 0;
		if (!ft_strncmp(map[y_m], "SO", 2) || !ft_strncmp(map[y_m], "NO", 2)
			|| !ft_strncmp(map[y_m], "WE", 2) || !ft_strncmp(map[y_m], "EA", 2)
			|| !ft_strncmp(map[y_m], "F", 1) || !ft_strncmp(map[y_m], "C", 1))
			{
				y_m++;
				continue;
			}
		while (map[y_m][x_m] == ' ' || (map[y_m][x_m] != '1' && map[y_m][x_m] != '\0'))
			x_m++;
		if (map[y_m][x_m] == '1')
		{
			*x = x_m;
			*y = y_m;
			return (1);
		}
		y_m++;
	}
	return (0);
}

/*Function to copy a double pointer and return a new double pointer*/
char	**copy_map(char **matrix)
{
	char	**copied;
	int		y;

	y = 0;
	while (matrix[y] != NULL)
		y++;
	copied = malloc(sizeof(char *) * (y + 1));
	y = 0;
	while (matrix[y] != NULL)
	{
		copied[y] = ft_strdup(matrix[y]);
		y++;
	}
	copied[y] = NULL;
	return (copied);
}

/*Using flood fill to find the path of the player*/
void	fill(char **matrix, int y, int x)
{
	if (y < 0 || x < 0 || matrix[y] == NULL || x >= (int)ft_strlen(matrix[y]))
		return ;
	if (matrix[y][x] == '\0' || matrix[y][x] == ' '
		|| matrix[y][x] == '0' || matrix[y][x] == '|' || matrix[y][x] == ','
		|| matrix[y][x] == 'W' || matrix[y][x] == 'N' || matrix[y][x] == 'S'
		|| matrix[y][x] == 'E')
		return ;
	matrix[y][x] = '|';
	fill(matrix, y, x + 1);
	fill(matrix, y, x - 1);
	fill(matrix, y + 1, x);
	fill(matrix, y - 1, x);
}

int	check_walls(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (find_first_wall(map, &x, &y) == 1)
	{
		printf("%d %d, %c\n", y, x, map[y][x]);
		fill(map, y, x);
	}
	// find_first_wall(map, &x, &y);
	// fill(map, y, x);
	return (1);
}
