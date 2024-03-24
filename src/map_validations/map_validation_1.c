/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:39:30 by aceauses          #+#    #+#             */
/*   Updated: 2024/07/09 18:23:37 by aceauses         ###   ########.fr       */
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

static void	check_if_map(char *line, bool *start)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] == '1'
			&& !clean_compare(line, "SO", 2) && !clean_compare(line, "NO", 2)
			&& !clean_compare(line, "WE", 2) && !clean_compare(line, "EA", 2)
			&& !clean_compare(line, "F", 1) && !clean_compare(line, "C", 1))
		{
			*start = true;
			return ;
		}
		i++;
	}
}

char	**read_map(char *argv)
{
	char	**map;
	char	*array;
	char	*line;
	int		fd;
	bool	start;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		map_error_exit("Incorect file or path");
	array = ft_calloc(1, 1);
	line = get_next_line(fd);
	start = false;
	while (line != NULL)
	{
		if (*line == '\t')
			line = handle_tabs(line);
		check_if_map(line, &start);
		if (start && clean_compare(line, "\n", 1))
			return (free(line), close(fd), free(array), map_errors(NL), NULL);
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
	while (clean_compare(tmp, "./", 2) || clean_compare(tmp, "../", 3))
	{
		tmp = ft_strchr(tmp + 2, '.');
		if (tmp == NULL)
			return (0);
	}
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
	if (!check_map_values(cube)
		|| !check_walls(cube))
		return (free_double_pointer(cube), 0);
	free_double_pointer(cube);
	return (1);
}
