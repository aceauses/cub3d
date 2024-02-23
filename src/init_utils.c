/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:57:15 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/12 13:29:25 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"


int	open_fd(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCannot open file\n");
		return (-1);
	}
	return (fd);
}

/**
 * @brief This will read the whole file map, and return only the map with
 * spaces at the beginning
 *
 * @param argv File path
 * @return char** Map as a double pointer
 */
size_t	calculate_height(char **map)
{
	size_t	i;
	size_t	height;

	height = 0;
	i = 0;
	while (map && map[i] != NULL)
	{
		i++;
		height++;
	}
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
size_t	calculate_width(char **map)
{
	size_t	i;
	size_t	width;

	width = 0;
	i = 0;
	while (map && map[i] != NULL)
	{
		if (ft_strlen(map[i]) > width)
			width = ft_strlen(map[i]);
		i++;
	}
	return (width);
}

void	get_floor(t_game *game, char *line)
{
	char **floor = ft_split(line + 2, ',');
	game->texture->floor = malloc(sizeof(t_color));
	if (!game->texture->floor)
		return ;
	game->texture->floor->red = ft_atoi(floor[0]);
	game->texture->floor->green = ft_atoi(floor[1]);
	game->texture->floor->blue = ft_atoi(floor[2]);
	free_double_pointer(floor);
}

void	get_ceiling(t_game *game, char *line)
{
	char **ceiling = ft_split(line + 2, ',');
	game->texture->ceiling = malloc(sizeof(t_color));
	if (!game->texture->ceiling)
		return ;
	game->texture->ceiling->red = ft_atoi(ceiling[0]);
	game->texture->ceiling->green = ft_atoi(ceiling[1]);
	game->texture->ceiling->blue = ft_atoi(ceiling[2]);
	free_double_pointer(ceiling);
}

void	get_colors(char *argv, t_game *game)
{
	int		fd;
	char	*line;

	fd = open_fd(argv);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == 'F' && line[1] == ' ')
			get_floor(game, line);
		else if (line[0] == 'C' && line[1] == ' ')
			get_ceiling(game, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}


void	free_game(t_game *game)
{
	if (game->map)
		free_double_pointer(game->map);
	if (game->cub_file)
		free_double_pointer(game->cub_file);
	if (game->floor)
		free_double_pointer(game->floor);
	if (game->ceiling)
		free_double_pointer(game->ceiling);
	if (game->texture->path)
		free_double_pointer(game->texture->path);
	if (game->texture->floor)
		free(game->texture->floor);
	if (game->texture->ceiling)
		free(game->texture->ceiling);
	if (game->texture)
		free(game->texture);
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	free(game);
}

