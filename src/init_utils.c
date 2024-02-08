/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:57:15 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/08 10:30:57 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief This will read the whole file and calculate only the height of the
 * map.
 *
 *
 * @param argv Path to the file
 * @return size_t The height of the map
 */
size_t	calculate_height(char *argv)
{
	int		fd;
	size_t	i;
	size_t	height;
	char	*line;

	height = 0;
	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror(argv);
		exit (1);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '1' || line[i] == '0')
			height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (height);
}

/**
 * @brief This will read the whole file and calculate only the width of the
 * map.
 *
 *
 * @param argv Path to the file
 * @return size_t The width of the map
 */
size_t	calculate_width(char *argv)
{
	int		fd;
	size_t	i;
	size_t	width;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror(argv);
		exit (1);
	}
	width = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '1' || line[i] == '0')
		{
			if (ft_strlen(line) > width)
				width = ft_strlen(line);
		}
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (width);
}

/**
 * @brief This will read the whole file map, and return only the map with
 * spaces at the beginning
 *
 * @param argv File path
 * @return char** Map as a double pointer
 */
 char	**get_map_only(char *argv)
{
	int		fd;
	size_t	i;
	size_t	j;
	char	**map;
	char	*line;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror(argv);
		exit (1);
	}
	map = ft_calloc(calculate_height(argv) + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		j = 0;
		while (line[j++] == ' ' || line[j] == '\t')
			line = handle_tabs(line);
		if (line[j] == '1' || line[j] == '0')
			map[i++] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
	}
	map[i] = NULL;
	free(line);
	close(fd);
	return (map);
}

/**
 * @brief Find the player's Y position
 *
 *
 * @param map The map as a double pointer
 * @return The Y position of the player
 */
int	find_player_y(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
					return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

/**
 * @brief Find the player's X position
 *
 *
 * @param map The map as a double pointer
 * @return The X position of the player
 */
int	find_player_x(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
					return (j);
			j++;
		}
		i++;
	}
	return (-1);
}
