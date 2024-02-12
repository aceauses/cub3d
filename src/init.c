/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/02/12 10:21:11 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"
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

	(*game)->texture = *texture;

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


void	get_colors(char *argv, char ***floor_colors, char ***ceiling_colors)
{
	int		fd;
	char	*line;

	fd = open_fd(argv);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] == 'F' && line[1] == ' ')
			*floor_colors = ft_split(line + 2, ',');
		else if (line[0] == 'C' && line[1] == ' ')
			*ceiling_colors = ft_split(line + 2, ',');
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	get_window_size(char *argv, size_t	*height, size_t	*width)
{
	int		fd;
	char	*line;
	int		i;

	fd = open_fd(argv);
	line = get_next_line(fd);
	*height = 0;
	*width = 0;
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '1' || line[i] == '0')
		{
			*height += 1;
			if (ft_strlen(line) > *width)
				*width = ft_strlen(line);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

void	get_player_position(char	***map, int *x, int *y)
{
	int		i;
	int		j;

	i = 0;
	*x = 0;
	*y = 0;
	while ((*map)[i] != NULL)
	{
		j = 0;
		while ((*map)[i][j] != '\0')
		{
			if ((*map)[i][j] == 'N' || (*map)[i][j] == 'S' ||
					(*map)[i][j] == 'E' || (*map)[i][j] == 'W')
			{
				*x = i;
				*y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

static bool init_structure(char *argv, t_game *game, t_player *player, t_ray *ray)
{
	get_window_size(argv, &game->height, &game->width);
	game->map = get_map_only(argv, game);
	game->map_textures = get_map_textures(argv, game);
	get_colors(argv, &game->floor_colors, &game->ceiling_colors);	// HOW TF DO COLORS EVEN WORK? BRUH
																	// MAYBE JUST PIXELPUT EVERYTHING AND HOPE FOR THE BEST?
	game->player = player;
	get_player_position(&game->map, &game->player->x, &game->player->y);
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
 * @return false If the mem images were not loaded successfully
 */
bool	load_images(t_game *game)
{
	if (ft_strcmp(game->texture->no_path, "./sprites/no.png") != 0)
	{
		game->texture->no = mlx_load_png("./sprites/no.png");
		game->texture->image = mlx_texture_to_image(game->mlx, game->texture->no);
		
	}
	if (ft_strcmp(game->texture->so_path, "./sprites/so.png") != 0)
	{
		game->texture->so = mlx_load_png("./sprites/so.png");
		game->texture->image = mlx_texture_to_image(game->mlx, game->texture->so);
	}
	if (ft_strcmp(game->texture->we_path, "./sprites/we.png") != 0)
	{
		game->texture->we = mlx_load_png("./sprites/we.png");
		game->texture->image = mlx_texture_to_image(game->mlx, game->texture->we);
	}
	if (ft_strcmp(game->texture->ea_path, "./sprites/ea.png") != 0)
	{
		game->texture->ea = mlx_load_png("./sprites/ea.png");
		game->texture->image = mlx_texture_to_image(game->mlx, game->texture->ea);
	}
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
	game->mlx = mlx_init(game->width * SIZE, game->height * SIZE, "Deez Nuts", false);
	if (load_images(game) == false)
		return (false);
	
	// TEMPORARY TO RUN THE GAME SIR
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return true;
}
