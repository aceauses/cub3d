/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:39:30 by aceauses          #+#    #+#             */
/*   Updated: 2024/01/31 15:49:25 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char **read_map(char *argv)
{
	char **map;
	char *array;
	char *line;
	int fd;

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
		// if (!check_single_line(line))
		array = free_join(array, line);
		free(line); 
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	map = ft_split(array, '\n');
	return (map);
}

int	map_validation(char *argv)
{
	char **map;

	map = read_map(argv);
	// for (int i = 0; map[i] != NULL; i++)
	// 	printf("%s\n", map[i]);
	return 0;
}
