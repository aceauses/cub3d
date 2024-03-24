/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:19:11 by rmitache          #+#    #+#             */
/*   Updated: 2024/07/09 18:23:11 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

bool	allocate_memory(t_ray **ray, t_texture **texture)
{
	*ray = malloc(sizeof(t_ray));
	if (!(*ray))
		return (false);
	ft_memset(*ray, 0, sizeof(t_ray));
	*texture = malloc(sizeof(t_texture));
	if (!(*texture))
		return (free(*ray), false);
	ft_memset(*texture, 0, sizeof(t_texture));
	return (true);
}

static t_game	*init_structure(char *argv, t_ray *ray,
		t_texture *texture)
{
	t_game	*game;
	int		x;
	int		y;

	x = 0;
	y = 0;
	game = malloc(sizeof(t_game));
	if (!game)
		return (free(ray), free(texture), NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->cub_file = read_map(argv);
	find_first_character(game->cub_file, &x, &y, '1');
	game->map = copy_map(game->cub_file, y);
	game->texture = texture;
	game->texture->path = malloc(sizeof(char *) * 5);
	if (!game->texture->path)
		return (free(game->ray), free(game->texture), free(game), NULL);
	game->ray = ray;
	set_angle_from_char(get_p_pos(&game->map, &game->ray->posx,
			&game->ray->posy), game->ray);
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
	t_texture	*texture;

	ray = NULL;
	game = NULL;
	texture = NULL;
	if (allocate_memory(&ray, &texture) == false)
		return (NULL);
	game = init_structure(argv, ray, texture);
	if (!game)
		return (NULL);
	if (get_texture(game) == false)
		return (free_game(game), NULL);
	get_colors(argv, game);
	return (game);
}
