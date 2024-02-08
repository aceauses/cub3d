/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/08 10:57:56 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/**
 * @brief Temporary function to print the map
 *
 * @param game The game structure
 */
// static void print_map(t_game *game)
// {
// 	for (size_t i = 0; i < game->height; i++)
// 	{
// 		printf("%s", game->map[i]);
// 	}
// }

/**
 * @brief This will allocate memory for the game and player structure
 *
 * @param game The game structure
 * @param player  The player structure
 * @return true If the memory was allocated successfully
 * @return false If the memory was not allocated successfully
 */
bool allocate_memory(t_game **game, t_player **player)
{
	// SHOULD I MALLOC FOR RAYS, IMAGES AND COLORS?
	*game = malloc(sizeof(t_game));
	if (!(*game))
		return false;
	*player = malloc(sizeof(t_player));
	if (!(*player))
	{
		free(*game);
		return false;
	}
	return true;
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
static bool init_structure(char *argv, t_game *game, t_player *player, t_ray *ray)
{

	game->height = calculate_height(argv);
	game->width = calculate_width(argv);
	game->map = get_map_only(argv);
	// print_map(game);
	game->player = player;
	game->player->y = find_player_y(game->map);
	game->player->x = find_player_x(game->map);
	game->player->delta_x = 0;
	game->player->delta_y = 0;
	game->player->angle = 0;
	game->ray = ray;
	game->ray->ray_angle = 0;
	game->ray->wall_hit_x = 0;
	game->ray->wall_hit_y = 0;
	game->ray->x_offset = 0;
	game->ray->y_offset = 0;
	// STILL IN PROGRESS!
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
bool init_data(char *argv)
{
	t_game *game;
	t_ray *ray;
	t_player *player;
	t_image	*image;

	game = NULL;
	player = NULL;
	if (allocate_memory(&game, &player) == false ||
		init_structure(argv, game, player, ray) == false)
		return false;
	return true;
}
