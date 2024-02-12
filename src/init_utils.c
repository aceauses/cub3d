/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:57:15 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/12 13:29:25 by rmitache         ###   ########.fr       */
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

/**
 * @brief This will duplicate a string from start until end and return a new char pointer
 * map.
 *
 *
 * @param start From where to stat the duplication
 * @param line Which string to duplicate
 * @param end Until where to duplicate
 * @return char *new_str;
 */
char	*ft_start_dup_end(size_t start, char *line, size_t end)
{
	char	*str;
	size_t	i;

	i = 0;
	str = ft_calloc(end - start + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (start < end)
	{
		str[i] = line[start];
		i++;
		start++;
	}
	return (str);
}


void	assign_path_to_texture(char *argv, t_game *game)
{
	int		fd;
	int		l;
	char	*line;

	fd = open_fd(argv);
	line = get_next_line(fd);
	while (line != NULL)
	{
		end = ft_strlen(line) - 1;
		if (line[0] == 'S')
			game->texture->so_path = ft_strdup_from_until(3, line, end);
		if (line[0] == 'N')
			game->texture->no_path = ft_strdup_from_until(3, line, end;
		if (line[0] == 'W')
			game->texture->we_path = ft_strdup_from_until(3, line, end);
		if (line[0] == 'E')
			game->texture->ea_path = ft_strdup_from_until(3, line, end);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

