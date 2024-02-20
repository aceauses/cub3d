/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:57:15 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/20 18:28:20 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
