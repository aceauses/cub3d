/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:39:30 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/22 19:33:23 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*handle_tabs(char *line)
{
	char	*new;
	int		i;
	int		spaces;

	i = -1;
	new = NULL;
	while (line[++i] != '\0' && line[i] == '\t')
		;
	new = ft_calloc(i * 4, sizeof(char *));
	if (!new)
		return (NULL);
	spaces = 0;
	while (spaces < i * 4)
		new[spaces++] = ' ';
	new = join_double_free(new, ft_strtrim(line, "\t"));
	return (free(line), new);
}

char	**read_map(char *argv)
{
	char	**map;
	char	*array;
	char	*line;
	int		fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
	{
		perror(argv);
		exit (1);
	}
	array = ft_calloc(1, 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (*line == '\t')
			line = handle_tabs(line);
		array = free_join(array, line);
		free(line);
		line = get_next_line(fd);
	}
	map = ft_split(array, '\n');
	return (free(array), close(fd), map);
}

static int	check_extension(char *argv)
{
	char	*tmp;

	if (argv == NULL)
		return (0);
	tmp = ft_strchr(argv, '.');
	if (tmp == NULL)
		return (0);
	if (ft_strncmp(tmp, ".cub", 5) != 0 && ft_strlen(tmp) != 4)
		return (map_errors("Invalid file extension"), 0);
	return (1);
}

int	map_validation(char *argv)
{
	char	**cube;

	if (HEIGHT < 150 || WIDTH < 150)
		return (map_errors("Invalid screen size"), 0);
	if (!check_extension(argv))
		return (0);
	cube = read_map(argv);
	for (int i = 0; cube[i] != NULL; i++)
	{
		printf("%s", cube[i]);
	}
	if (!check_map_values(cube)
		|| !check_walls(cube))
		return (free_double_pointer(cube), 0);
	free_double_pointer(cube);
	return (1);
}
