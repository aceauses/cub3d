/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:57:15 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/10 15:04:19 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"

/**
 * @brief This will read the whole file and calculate only the height of the
 * map.
 *
 *
 * @param argv Path to the file
 * @return size_t The height of the map
 */

int open_fd(char *argv)
{
	int fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror(argv);
		exit (1);
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
 char	**get_map_only(char *argv, t_game *game)
{
	int		fd;
	size_t	i;
	size_t	j;
	char	**map;
	char	*line;

	fd = open_fd(argv);
	map = ft_calloc(game->height + 1, sizeof(char *));
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

char	**get_map_textures(char *argv, t_game *game)
{
	int		fd;
	size_t	i;
	char	**map;
	char	*line;

	fd = open_fd(argv);
	map = ft_calloc(game->height + 1, sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == 'S')
		{
			map[i++] = ft_strdup(line);
			game->texture->so_path = ft_strdup(line + 3);
		}
		if (line[0] == 'N')
		{
			map[i++] = ft_strdup(line);
			game->texture->no_path = ft_strdup(line + 3);
		}
		if (line[0] == 'W')
		{
			map[i++] = ft_strdup(line);
			game->texture->we_path = ft_strdup(line + 3);
		}
		if (line[0] == 'E')
		{
			map[i++] = ft_strdup(line);
			game->texture->ea_path = ft_strdup(line + 3);
		}
		line = get_next_line(fd);
	}
	map[i] = NULL;
	free(line);
	close(fd);
	return (game->map);
}

