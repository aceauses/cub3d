/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:39:30 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/01 13:04:20 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*Handle Tabs. If 1 Tab in inside the map it will be replace with 8 Spaces it should be 4*/
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

static int check_extension(char *argv)
{
	int i;

	i = 0;
	while (argv[i] != '\0')
		i++;
	if (argv[i - 1] != 'b' || argv[i - 2] != 'u' || argv[i - 3] != 'c' || argv[i - 4] != '.')
	{
		printf("Error\nInvalid file extension\n");
		return (0);
	}
	return (1);
}

int	map_validation(char *argv)
{
	char **map;

	if (!check_extension(argv))
		return (0);
	map = read_map(argv);
	for (int i = 0; map[i] != NULL; i++)
		printf("%s\n", map[i]);
	return 0;
}
