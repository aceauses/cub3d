/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/12 13:48:20 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"
#include <stdio.h>

/**
 * @brief This will allocate memory for the game and player structure
 *
 * @param game The game structure
 * @param player The player structure
 * @param texture The texture structure
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

	(*game)->texture = *texture;
	(*game)->player = *player;
	(*game)->ray = *ray;
	return true;
}


/**
 * @brief Initialize all structures and variables to default values
 *
 * @param argv Path to the file
 * @param game Game structure
 * @param player Player structure
 * @param ray Ray structure
 * @return true If the initialization was successful
 * @return false If the initialization was not successfuls
 */
static bool init_structure(char *argv, t_game *game, t_player *player, t_ray *ray)
{
	(void)player;
	(void)ray;
	get_window_size(argv, &game->height, &game->width);
	game->map = get_map_only(argv, game);
	assign_path_to_texture(argv, game);
	get_colors(argv, &game->floor_colors, &game->ceiling_colors);	// HOW TF DO COLORS EVEN WORK? BRUH
																	// MAYBE JUST PIXELPUT EVERYTHING AND HOPE FOR THE BEST?
	get_player_position(&game->map, &game->player->x, &game->player->y);
	game->player->delta_x = 0;
	game->player->delta_y = 0;
	game->player->angle = 0;
	// game->ray = ray;
	game->ray->ray_angle = 0;
	game->ray->wall_hit_x = 0;
	game->ray->wall_hit_y = 0;
	game->ray->x_offset = 0;
	game->ray->y_offset = 0;
	// STILL IN PROGRESS!
	return (true);
}

/**
 * @brief This function will load the images using mlx_load_png and save them
 * into the correct texture property of game->texture for later use.
 *
 * @param game The game structure
 * @return true If the images were loaded successfully
 * @return false If the mem images were not loaded successfully
 */
bool	load_images(t_game *game)
{
	game->texture->no = mlx_load_png(game->texture->no_path);
	game->texture->so = mlx_load_png(game->texture->so_path);
	game->texture->we = mlx_load_png(game->texture->we_path);
	game->texture->ea = mlx_load_png(game->texture->ea_path);

	if (!game->texture->no || !game->texture->so || !game->texture->we
			|| !game->texture->ea)
		return (false);
	return (true);
}


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
	game->mlx = mlx_init(game->width * SIZE, game->height * SIZE, "Deez Nuts", false);
	if (load_images(game) == false)
		return (false);

	// TEMPORARY TO RUN THE GAME SIR
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return true;
}
