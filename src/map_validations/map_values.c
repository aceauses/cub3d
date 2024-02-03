/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:09:41 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/03 21:43:19 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_textures(char **map)
{
	int		i;
	char **split;

	i = 0;
	while (i < 4)
	{
		split = ft_split(map[i], ' ');
		if ((ft_strcmp(split[0], "NO") && i == 0)
			|| (ft_strcmp(split[0], "SO") && i == 1)
			|| (ft_strcmp(split[0], "WE") && i == 2)
			|| (ft_strcmp(split[0], "EA") && i == 3))
			return (free_double_pointer(split), 0);
		if (open(split[1], O_RDONLY) == -1)
			return (free_double_pointer(split), 0);
		free_double_pointer(split);
		i++;
	}
	return (1);
}

static int	is_digit(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	check_rgb_f(char **map)
{
	int		i;
	char	**split;
	char	**values;
	int		x;

	i = 0;
	x = 0;
	while (ft_strncmp(map[i], "F", 1) != 0)
		i++;
	split = ft_split(map[i], ' ');
	if (!split)
		return (0);
	values = ft_split(split[1], ',');
	if (!values)
		return (free_double_pointer(split), 0);
	while (values[x] != NULL)
	{
		if (!is_digit(values[x])
			|| ft_atoi(values[x]) > 255 || ft_atoi(values[x]) < 0)
			return (free_double_pointer(values), free_double_pointer(split), 0);
		x++;
	}
	if (x > 3)
		return (free_double_pointer(values), free_double_pointer(split), 0);
	return (free_double_pointer(values), free_double_pointer(split), 1);
}

static int	check_rgb_c(char **map)
{
	int		i;
	char	**split;
	char	**values;
	int		x;

	i = 0;
	x = 0;
	while (ft_strncmp(map[i], "C", 1) != 0)
		i++;
	split = ft_split(map[i], ' ');
	if (!split)
		return (0);
	values = ft_split(split[1], ',');
	if (!values)
		return (free_double_pointer(split), 0);
	while (values[x] != NULL)
	{
		if (!is_digit(values[x])
			|| ft_atoi(values[x]) > 255 || ft_atoi(values[x]) < 0)
			return (free_double_pointer(values), free_double_pointer(split), 0);
		x++;
	}
	if (x > 3)
		return (free_double_pointer(values), free_double_pointer(split), 0);
	return (free_double_pointer(values), free_double_pointer(split), 1);
}

int	check_map_values(char **map)
{
	if (!check_textures(map))
		return (0);
	if (!check_rgb_f(map) || !check_rgb_c(map))
		return (0);
	return (1);
}