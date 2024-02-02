/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:39:30 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/02 17:35:12 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char*	handle_tabs(char *line)
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

static char	**read_map(char *argv)
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
		if (*line == '\t')
			line = handle_tabs(line);
		array = free_join(array, line);
		free(line); 
		line = get_next_line(fd);
		if (line == NULL)
			break ;
	}
	map = ft_split(array, '\n');
	return (free(array), map);
}

static int	check_extension(char *argv)
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
	free_double_pointer(map);
	return 0;
}
