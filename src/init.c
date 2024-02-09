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
#include <stdio.h>

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
bool allocate_memory(t_game **game, t_player **player, t_ray **ray, t_texture **texture)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
		return false;

	*player = malloc(sizeof(t_player));
	if (!(*player))
		return (free(*game), false);

	*ray = malloc(sizeof(t_ray));
	if (!(*ray))
		return (free(*game), free(*player), false);

	*texture = malloc(sizeof(t_texture));
	if (!(*texture))
		return (free(*game), free(*player), free(*ray), false);

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
 * @brief This function will load the images, convert them to images and display them.
 * Will also assign game->texture to the texture structure
 *
 * @param game The game structure
 * @return true If the images were loaded successfully
 * @return false If the mem
 */
bool	load_images(t_game *game, t_texture *texture)
{
	game->texture = texture;

	texture->no = mlx_load_png("sprites/no.png");
	texture->image = mlx_texture_to_image(game->mlx, texture->no);
	mlx_delete_texture(texture->no);
	// put_image(game);

	texture->so = mlx_load_png("sprites/so.png");
	texture->image = mlx_texture_to_image(game->mlx, texture->so);
	mlx_delete_texture(texture->so);
	// put_image(game);

	texture->we = mlx_load_png("sprites/we.png");
	texture->image = mlx_texture_to_image(game->mlx, texture->we);
	mlx_delete_texture(texture->we);
	// put_image(game);


	texture->ea = mlx_load_png("sprites/ea.png");
	texture->image = mlx_texture_to_image(game->mlx, texture->ea);
	mlx_delete_texture(texture->ea);
	// put_image(game);

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
	t_texture *texture;

	game = NULL;
	player = NULL;
	ray = NULL;
	texture = NULL;
	if (allocate_memory(&game, &player, &ray, &texture) == false ||
		init_structure(argv, game, player, ray) == false)
		return (false);
	game->mlx = mlx_init(game->width * 64, game->height * 64, "Deez Nuts", false);
	if (load_images(game, texture) == false)
		return (false);

	// TEMPORARY TO RUN THE GAME SIR
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return true;
}
