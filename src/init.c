/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/22 18:58:11 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

/**
 * @brief This will allocate memory for the game and player structure
 *
 * @param game The game structure
 * @param player  The player structure
 * @return true If the memory was allocated successfully
 * @return false If the memory was not allocated successfully
 */
bool	allocate_memory(t_player **player, t_ray **ray, t_texture **texture)
{
	*player = malloc(sizeof(t_player));
	if (!(*player))
		return (false);
	ft_memset(*player, 0, sizeof(t_player));
	*ray = malloc(sizeof(t_ray));
	if (!(*ray))
		return (free(*player), false);
	ft_memset(*ray, 0, sizeof(t_ray));
	*texture = malloc(sizeof(t_texture));
	if (!(*texture))
		return (free(*player), free(*ray), false);
	ft_memset(*texture, 0, sizeof(t_texture));
	return (true);
}

/**
 * @brief Initialize all structures and variables to default values
 *
 * @param argv Path to the file
 * @param game Game structure
 * @param player Player structure
 * @return true If the initialization was successful
 * @return false If the initialization was not successful
 */
static t_game	*init_structure(char *argv, t_player *player, t_ray *ray,
		t_texture *texture)
{
	t_game	*game;
	int		x;
	int		y;

	x = 0;
	y = 0;
	game = malloc(sizeof(t_game));
	if (!game)
		return (free(player), free(ray), free(texture), NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->cub_file = read_map(argv);
	find_first_character(game->cub_file, &x, &y, '1');
	game->map = copy_map(game->cub_file, y);
	game->m_height = calculate_height(game->map);
	game->m_width = calculate_width(game->map);
	game->distance = 0.5;
	game->distance_jos = 1.5;
	game->player = player;
	find_first_character(game->map, &game->player->x, &game->player->y, 'N');
	game->texture = texture;
	game->texture->path = malloc(sizeof(char *) * 5);
	if (!game->texture->path)
		return (free(game->player), free(game->ray), free(game->texture)
			, free(game), NULL);
	game->ray = ray;
	return (game);
}

bool	get_texture(t_game *game)
{
	int		i;
	char	**split;

	i = 0;
	while (game->cub_file[i] != NULL)
	{
		split = ft_split(game->cub_file[i], ' ');
		if (!split)
			return (false);
		if (split[0] != NULL)
		{
			if (clean_compare(split[0], "NO", 2))
				game->texture->path[0] = ft_strdup(split[1]);
			else if (clean_compare(split[0], "SO", 2))
				game->texture->path[1] = ft_strdup(split[1]);
			else if (clean_compare(split[0], "WE", 2))
				game->texture->path[2] = ft_strdup(split[1]);
			else if (clean_compare(split[0], "EA", 2))
				game->texture->path[3] = ft_strdup(split[1]);
		}
		free_double_pointer(split);
		i++;
	}
	game->texture->path[4] = NULL;
	return (true);
}


/**
 * @brief Allocate memory for the game and player structure and initialize the
 * game structure
 *
 * @param argv Path to the file
 * @return true If the memory was allocated successfully
 * @return false If the memory was not allocated successfully
 */
t_game	*init_data(char *argv)
{
	t_game		*game;
	t_ray		*ray;
	t_player	*player;
	t_texture	*texture;

	player = NULL;
	ray = NULL;
	game = NULL;
	texture = NULL;
	if (allocate_memory(&player, &ray, &texture) == false)
		return (NULL);
	game = init_structure(argv, player, ray, texture);
	if (!game)
		return (NULL);
	if (get_texture(game) == false)
		return (free_game(game), NULL);
	get_colors(argv, game);
	return (game);
}
