/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/20 18:40:16 by aceauses         ###   ########.fr       */
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
bool allocate_memory(t_player **player, t_ray **ray, t_texture **texture)
{
	*player = malloc(sizeof(t_player));
	if (!(*player))
		return (false);
	ft_memset(*player, 0, sizeof(t_player));

	*ray = malloc(sizeof(t_ray));
	if (!(*ray))
		return (free(*player), false);

	*texture = malloc(sizeof(t_texture));
	if (!(*texture))
		return (free(*player), free(*ray), false);

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
static t_game *init_structure(char *argv, t_player *player
	, t_ray *ray, t_texture *texture)
{
	t_game *game;

	int x = 0;
	int y = 0;
	game = malloc(sizeof(t_game));
	if (!game)
		return (free(player), free(ray), free(texture), NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->cub_file = read_map(argv);
	if (!find_first_character(game->cub_file, &x, &y, '1'))
		return (0);
	game->map = copy_map(game->cub_file, y);
	game->m_height = calculate_height(game->map);
	game->m_width = calculate_width(game->map);
	game->player = player;
	find_first_character(game->map, &game->player->x, &game->player->y, 'N');
	game->texture = texture;
	game->ray = ray;
	return (game);
}

/**
 * @brief This function will load the images, convert them to images and display them.
 * Will also assign game->texture to the texture structure
 *
 * @param game The game structure
 * @return true If the images were loaded successfully
 * @return false If the mem
 */
// bool	load_images(t_game *game, t_texture *texture)
// {
// 	game->texture = texture;

// 	texture->no = mlx_load_png("sprites/no.png");
// 	texture->image = mlx_texture_to_image(game->mlx, texture->no);
// 	mlx_delete_texture(texture->no);
// 	// put_image(game);

// 	texture->so = mlx_load_png("sprites/so.png");
// 	texture->image = mlx_texture_to_image(game->mlx, texture->so);
// 	mlx_delete_texture(texture->so);
// 	// put_image(game);

// 	texture->we = mlx_load_png("sprites/we.png");
// 	texture->image = mlx_texture_to_image(game->mlx, texture->we);
// 	mlx_delete_texture(texture->we);
// 	// put_image(game);


// 	texture->ea = mlx_load_png("sprites/ea.png");
// 	texture->image = mlx_texture_to_image(game->mlx, texture->ea);
// 	mlx_delete_texture(texture->ea);
// 	// put_image(game);

// 	return (true);
// }

/**
 * @brief Allocate memory for the game and player structure and initialize the
 * game structure
 *
 * @param argv Path to the file
 * @return true If the memory was allocated successfully
 * @return false If the memory was not allocated successfully
 */
t_game *init_data(char *argv)
{
	t_game *game;
	t_ray *ray;
	t_player *player;
	t_texture *texture;

	player = NULL;
	ray = NULL;
	game = NULL;
	texture = NULL;
	if (allocate_memory(&player, &ray, &texture) == false)
		return (NULL);
	game = init_structure(argv, player, ray, texture);
	return (game);
}
