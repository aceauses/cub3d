/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_values_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 16:22:47 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/17 17:51:08 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/**
 * @brief Function to check if the buffer contains the split string
*/
static int	check_inside_buffer(char *buffer, char *split, int *check)
{
	if (ft_strnstr(buffer, split, ft_strlen(buffer)))
	{
		*check += 6;
		return (1);
	}
	*check += 1;
	return (0);
}

/**
 * @brief Function to return 1 if the path should be checked and 0 if not
*/
int	should_check_path(char **split, char *buffer, int *check)
{
	if ((!ft_strcmp(split[0], "NO")
			&& !check_inside_buffer(buffer, split[0], check))
		|| (!ft_strcmp(split[0], "SO")
			&& !check_inside_buffer(buffer, split[0], check))
		|| (!ft_strcmp(split[0], "WE")
			&& !check_inside_buffer(buffer, split[0], check))
		|| (!ft_strcmp(split[0], "EA")
			&& !check_inside_buffer(buffer, split[0], check)))
	{
		return (1);
	}
	return (0);
}

int	clean_compare(char *s1, char *set, size_t n)
{
	char	*mem;

	mem = ft_strtrim(s1, " \t\r\v\f");
	if (!ft_strncmp(mem, set, n))
	{
		free(mem);
		return (1);
	}
	free(mem);
	return (0);
}
