/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/07 16:40:01 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	init_data()
{
	t_game		*game;
	t_player	*player;
	

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
	{
		return (false);
	}
	player = ft_calloc(1, sizeof(t_player));
	if (!player)
	{
		return (free(game), false);
	}
	
	
	return (true);
}
