/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:18:12 by aceauses          #+#    #+#             */
/*   Updated: 2024/07/09 18:28:40 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	update_minimap_position(t_game *game)
{
	mlx_instance_t	*player;

	player = game->texture->map_player->instances;
	player[0].x = game->ray->posx * (int)(WIDTH * W_RATIO) - 3;
	player[0].y = game->ray->posy * (int)(HEIGHT * H_RATIO) - 3;
}

void	camera(void *param)
{
	t_game	*game;
	double	wallx;
	int		x;
	int		mapx;
	int		mapy;

	game = (t_game *)param;
	refresh_camera(game);
	x = -1;
	while (++x < WIDTH)
	{
		update_minimap_position(game);
		init_ray(game->ray, x);
		mapx = (int)game->ray->posx;
		mapy = (int)game->ray->posy;
		calc_sidedist(game->ray, &mapx, &mapy);
		game->ray->which_side = dda(game, &mapx, &mapy, &game->ray->side);
		calculate_wall_distances(game, game->ray->side, mapx, mapy);
		calc_wallx(game, game->ray->side, &wallx);
		put_pixels(game, x, wallx);
		mlx_set_instance_depth(game->texture->camera
		[game->texture->current_buffer]->instances, 0);
	}
}

void	put_image_buffer(t_game *game)
{
	game->texture->camera[(game->texture->current_buffer + 1)
		% NUM_BUFFERS] = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->texture->camera[(game->texture->current_buffer + 2)
		% NUM_BUFFERS] = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx,
		game->texture->camera[(game->texture->current_buffer + 1)
		% NUM_BUFFERS], 0, 0);
	mlx_image_to_window(game->mlx,
		game->texture->camera[(game->texture->current_buffer + 2)
		% NUM_BUFFERS], 0, 0);
}

void	draw_minimap(t_game *game)
{
	int			i;
	int			j;
	mlx_image_t	*map_wall;
	mlx_image_t	*map_player;

	i = -1;
	j = 0;
	game->texture->map_wall = mlx_new_image(game->mlx,
			(int)(WIDTH * W_RATIO), (int)(HEIGHT * H_RATIO));
	map_wall = game->texture->map_wall;
	ft_memset(map_wall->pixels, 200, map_wall->width
		* map_wall->height * sizeof(int32_t));
	game->texture->map_player = mlx_new_image(game->mlx,
			(int)(WIDTH * W_RATIO), (int)(HEIGHT * H_RATIO));
	map_player = game->texture->map_player;
	ft_memset(map_player->pixels, 255, map_player->width
		* map_player->height * sizeof(int32_t));
	while (game->map[++i])
	{
		j = -1;
		while (game->map[i][++j])
			if (game->map[i][j] == '1')
				mlx_image_to_window(game->mlx, map_wall,
					j * ((int)(WIDTH * W_RATIO)), i * (int)(HEIGHT * H_RATIO));
	}
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game->mlx)
		return ;
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	game->texture->background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(game->mlx, game->texture->background, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		return ;
	}
	put_image_buffer(game);
	draw_minimap(game);
	mlx_image_to_window(game->mlx, game->texture->map_player, 0, 0);
	mlx_loop_hook(game->mlx, fill_background, game);
	mlx_loop_hook(game->mlx, &camera, game);
	mlx_loop_hook(game->mlx, &controls, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->texture->ray_image);
	mlx_delete_image(game->mlx, game->texture->background);
	mlx_delete_image(game->mlx, game->texture->map_wall);
	mlx_delete_image(game->mlx, game->texture->map_player);
	mlx_delete_image(game->mlx, game->texture->camera[0]);
	mlx_delete_image(game->mlx, game->texture->camera[1]);
	mlx_terminate(game->mlx);
}
