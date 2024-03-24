/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:34:37 by aceauses          #+#    #+#             */
/*   Updated: 2024/07/09 18:20:25 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	*game;

	game = NULL;
	atexit(check_leaks);
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
		if (!init_textures(game))
			return (free_game(game), 1);
		start_game(game);
		free_game(game);
	}
	else
		return (1);
	return (0);
}
