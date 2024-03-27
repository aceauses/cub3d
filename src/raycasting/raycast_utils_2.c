/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:21:24 by rmitache          #+#    #+#             */
/*   Updated: 2024/03/22 14:12:50 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	calculate_tex(double texpos, char c)
{
	int	result;

	result = -1;
	if (c == 'Y')
		result = (int)(texpos * 64) % 64;
	else if (c == 'X')
		result = (int)(texpos * 64) % 64;
	return (result);
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

int	calculate_tex_index(int texX, int texY)
{
	int	texindex;

	texX = clamp(texX, 0, 64 - 1);
	texY = clamp(texY, 0, 64 - 1);
	texindex = texY * 64 + texX;
	return (texindex * 4);
}
