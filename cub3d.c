/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:34:37 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/20 18:40:10 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "includes/cub3d.h"

void	check_leaks()
{
	system("leaks cub3d");
}

int main(int argc, char **argv)
{
	t_game *game;

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
		// Do mlx stuff
		for (size_t i = 0; game->map[i]; i++)
		{
			printf("%s\n", game->map[i]);
		}
		printf("playe x: %d\n", game->player->x);
		printf("playe y: %d\n", game->player->y);
		printf("map width: %zu\n", game->m_width);
		printf("map height: %zu\n", game->m_height);
		free_double_pointer(game->map);
		free_double_pointer(game->cub_file);
		free(game->player);
		free(game->ray);
		free(game->texture);
		free(game);
	}
	else
		return (1);
	return (0);
}
