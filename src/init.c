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
bool	allocate_memory(t_game **game, t_player **player,
	t_ray **ray, t_texture **texture)
{
	*game = malloc(sizeof(t_game));
	if (!(*game))
		return (false);
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
	return (true);
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
static bool	init_structure(char *argv, t_game *game,
	t_player *player, t_ray *ray)
{
	(void)player;
	(void)ray;
	get_window_size(argv, &game->height, &game->width);
	game->map = get_map_only(argv, game);
	assign_path_to_texture(argv, game);
	get_colors(argv, &game->floor_colors, &game->ceiling_colors);
	get_p_pos(&game->map, &game->player->x, &game->player->y, game->player);
	game->player->delta_x = cos(game->player->angle) * 5;
	game->player->delta_y = sin(game->player->angle) * 5;
	game->ray = ray;
	game->ray->map_x = 0;
	game->ray->map_y = 0;
	game->ray->map_p = 0;
	game->ray->x = 0;
	game->ray->dof = 0;
	game->ray->y = 0;
	game->ray->x_offset = 0;
	game->ray->y_offset = 0;
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
	game->texture->no_image = mlx_texture_to_image(game->mlx, game->texture->no);
	game->texture->so_image = mlx_texture_to_image(game->mlx, game->texture->so);
	game->texture->we_image = mlx_texture_to_image(game->mlx, game->texture->we);
	game->texture->ea_image = mlx_texture_to_image(game->mlx, game->texture->ea);


	game->texture->ray_image = mlx_new_image(game->mlx, 20, 20);
	memset(game->texture->ray_image->pixels, 255, game->texture->ray_image->width * game->texture->ray_image->height * sizeof(int32_t));

	mlx_image_to_window(game->mlx, game->texture->ray_image, game->player->x, game->player->y);
	return (true);
}

double	FixAng(double a)
{
	if (a > 0)
		a -= 360;
	if (a < 0)
		a += 360;
	if (a < 0)
		a = 0;
	return (a);
}

double	get_distance(t_game *game)
{
	double	ft_cos;
	double	ft_sin;

	ft_cos = cos(degToRad(game->ray->angle)) * (game->ray->x - game->player->x);
	ft_sin = sin(degToRad(game->ray->angle)) * (game->ray->y - game->player->y);
	return (ft_cos - ft_sin);
}

void	check_if_wall(t_game *game, char check_for)
{
	while (game->ray->dof < 8)
	{
		game->ray->map_x = (int)game->ray->x >> 6;
		game->ray->map_y = (int)game->ray->y >> 6;
		game->ray->map_p = game->ray->map_y * game->width + game->ray->map_x;
		if (game->ray->map_x < 0 || game->ray->map_x >= (int)game->width
			|| game->ray->map_y < 0 || game->ray->map_y >= (int)game->height)
			break ;
		if (game->ray->map_p > 0 && game->ray->map_p < (int)game->width
			* (int)game->height
			&& game->map[game->ray->map_y][game->ray->map_x] == '1')
		{
			game->ray->dof = 8;
			if (check_for == 'V')
				game->ray->distV = get_distance(game);
			else if (check_for == 'H')
				game->ray->distH = get_distance(game);
		}
		else
		{
			game->ray->x += game->ray->x_offset;
			game->ray->y += game->ray->y_offset;
			game->ray->dof++;
		}
	}
}

void	check_horizontal(t_game *game, double ft_tan)
{
	if (cos(degToRad(game->ray->angle)) > 0.001)
	{
		game->ray->x = (((int)game->player->x >> 6) << 6) + 64;
		game->ray->y = (game->player->x - game->ray->x) * ft_tan + game->player->y;
		game->ray->x_offset = 64;
		game->ray->y_offset = -game->ray->x_offset * ft_tan;
	}
	else if (cos(degToRad(game->ray->angle)) < -0.001)
	{
		game->ray->x = (((int)game->player->x >> 6) << 6) - 0.0001;
		game->ray->y = (game->player->x - game->ray->x) * ft_tan + game->player->y;
		game->ray->x_offset = -64;
		game->ray->y_offset = -game->ray->x_offset * ft_tan;
	}
	else
	{
		game->ray->x = game->player->x;
		game->ray->y = game->player->y;
		game->ray->dof = 8;
	}
	check_if_wall(game, 'V');
}

void	check_vertical(t_game *game, double ft_tan)
{
	if (sin(degToRad(game->ray->angle)) > 0.001)
	{
		game->ray->y = (((int)game->player->y >> 6) << 6) - 0.0001;
		game->ray->x = (game->player->y - game->ray->y) * ft_tan + game->player->x;
		game->ray->y_offset = -64;
		game->ray->x_offset = -game->ray->y_offset * ft_tan;
	}
	else if (sin(degToRad(game->ray->angle)) < -0.001)
	{
		game->ray->y = (((int)game->player->y >> 6) << 6) + 64;
		game->ray->x = (game->player->y-game->ray->y) * ft_tan + game->player->x;
		game->ray->y_offset = 64;
		game->ray->x_offset = -game->ray->y_offset * ft_tan;
	}
	else
	{
		game->ray->x = game->player->x;
		game->ray->y = game->player->y;
		game->ray->dof = 8;
	}
	check_if_wall(game, 'H');
}

void	esc_free(t_game *game)
{
	mlx_terminate(game->mlx);
	free_double_pointer(game->map);
	free(game->player);
	free(game->ray);
	free_double_pointer(game->floor_colors);
	free_double_pointer(game->ceiling_colors);
	free(game);
	exit(system("leaks cub3d"));
}

void DrawWalls(t_game *game)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (game->map == NULL)
		return ;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, game->texture->no_image, j * 64, i * 64);
			j++;
		}
		i++;
	}
}

bool	init_data(char *argv)
{
	t_game		*game;
	t_ray		*ray;
	t_player	*player;
	t_texture	*texture;

	game = NULL;
	player = NULL;
	ray = NULL;
	texture = NULL;
	if (!allocate_memory(&game, &player, &ray, &texture)
			|| !init_structure(argv, game, player, ray))
		return (false);
	game->mlx = mlx_init((game->width * SIZE), (game->height * SIZE), "Deez Nuts 💀", false);
	if (load_images(game) == false)
		return (false);
	// TEMPORARY TO RUN THE GAME SIR
	DrawWalls(game);
	game->tmp_ray_image = mlx_new_image(game->mlx, 20, 100);
	mlx_texture_t *sa = mlx_load_png("sprites/ea.png");
	game->tmp_ray_image = mlx_texture_to_image(game->mlx, sa);
	for (int i = 0; i < 60; i++)
		mlx_image_to_window(game->mlx, game->tmp_ray_image, i, i);

	mlx_loop_hook(game->mlx, controls, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	return (true);
}
