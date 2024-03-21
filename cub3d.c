/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:34:37 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/21 18:14:40 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (0);
	}
	if (map_validation(argv[1]))
	{
		game = init_data(argv[1]);
		if (!game)
			return (1);
		if (!init_mlx(game))
			return (1);
		if (!init_textures(game))
			return (free_game(game), 1);
		start_game(game);
		free_game(game);
	}
	else
		return (1);
	return (0);
}
