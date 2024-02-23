/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
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
  game->player->delta_x = cos(game->player->angle) * 5;
	game->player->delta_y = sin(game->player->angle) * 5;
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
