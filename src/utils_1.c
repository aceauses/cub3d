/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:26:56 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/07 15:23:19 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char *join_double_free(char *buffer, char *buff)
{
	char *temp;

	temp = ft_strjoin_gnl(buffer, buff);
	free(buffer);
	free(buff);
	return (temp);
}

void	free_double_pointer(char **pointer)
{
	int		i;

	i = 0;
	while (pointer && pointer[i])
		free(pointer[i++]);
	free(pointer);
}

void	ft_free(t_game *game)
{
	if (game)
	{
		if (game->mlx)
			free(game->mlx);
		if (game->win)
			free(game->win);
		free(game);
	}
}