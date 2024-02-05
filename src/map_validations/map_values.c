/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:09:41 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/05 20:23:32 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	dcte(char *buffer, char *split, int *check)
{
	if (ft_strnstr(buffer, split, ft_strlen(buffer)))
	{
		*check += 6;
		return (1);
	}
	*check += 1;
	return (0);
}

static int	check_textures(char **map)
{
	int		i;
	char	**split;
	char	*buffer;
	int		check;

	i = -1;
	check = 0;
	buffer = ft_strdup("");
	while (map[++i] != NULL && check <= 4)
	{
		split = ft_split(map[i], ' ');
		if ((!ft_strcmp(split[0], "NO") && !dcte(buffer, split[0], &check))
			|| (!ft_strcmp(split[0], "SO") && !dcte(buffer, split[0], &check))
			|| (!ft_strcmp(split[0], "WE") && !dcte(buffer, split[0], &check))
			|| (!ft_strcmp(split[0], "EA") && !dcte(buffer, split[0], &check)))
		{
			if (open(split[1], O_RDONLY) == -1)
				return (map_errors(PATH_ERROR), free(buffer), free_double_pointer(split), 0);
			buffer = free_join(buffer, split[0]);
		}
		free_double_pointer(split);
	}
	if (check != 4)
		return (map_errors("Textures are not correct"), free(buffer), 0);
	return (free(buffer), 1);
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
	x = -1;
	while (map[i] && ft_strncmp(map[i], "F", 1) != 0)
		i++;
	split = ft_split(map[i], ' ');
	if (!split)
		return (0);
	values = ft_split(split[1], ',');
	if (!values)
		return (free_double_pointer(split), 0);
	while (values[++x] != NULL)
		if (!is_digit(values[x])
			|| ft_atoi(values[x]) > 255 || ft_atoi(values[x]) < 0)
			return (map_errors(RGB_ERROR_2)
				, free_double_pointer(values), free_double_pointer(split), 0);
	if (x != 3)
		return (map_errors(RGB_ERROR)
			, free_double_pointer(values), free_double_pointer(split), 0);
	return (free_double_pointer(values), free_double_pointer(split), 1);
}

static int	check_rgb_c(char **map)
{
	int		i;
	char	**split;
	char	**values;
	int		x;

	i = 0;
	x = -1;
	while (map[i] && ft_strncmp(map[i], "C", 1) != 0)
		i++;
	split = ft_split(map[i], ' ');
	if (!split)
		return (0);
	values = ft_split(split[1], ',');
	if (!values)
		return (free_double_pointer(split), 0);
	while (values[++x] != NULL)
		if (!is_digit(values[x])
			|| ft_atoi(values[x]) > 255 || ft_atoi(values[x]) < 0)
			return (free_double_pointer(values), free_double_pointer(split), 0);
	if (x != 3)
		return (map_errors(RGB_ERROR)
			, free_double_pointer(values), free_double_pointer(split), 0);
	return (free_double_pointer(values), free_double_pointer(split), 1);
}

int	check_map_values(char **map)
{
	if (!map || !map[0])
		return (0);
	if (!check_textures(map))
		return (0);
	if (!check_rgb_f(map) || !check_rgb_c(map))
		return (0);
	return (1);
}