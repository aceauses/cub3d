/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:18:12 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/19 19:52:15 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_ceiling(mlx_image_t *image, t_game *game, int i)
{
	int	y;
	int	color;

	y = 0;
	while (y < HEIGHT / 2)
	{
		color = ft_pixel(game->texture->ceiling->red,
				game->texture->ceiling->green, game->texture->ceiling->blue,
				150);
		mlx_put_pixel(image, i, y, color);
		y++;
	}
}

void	fill_floor(mlx_image_t *image, t_game *game, int i)
{
	int	y;
	int	color;

	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		color = ft_pixel(game->texture->floor->red, game->texture->floor->green,
				game->texture->floor->blue, 150);
		mlx_put_pixel(image, i, y, color);
		y++;
	}
}

void	fill_background(void *param)
{
	t_game		*game;
	mlx_image_t	*image;
	int			i;

	game = (t_game *)param;
	image = game->texture->background;
	i = 0;
	while (i < WIDTH)
	{
		fill_ceiling(image, game, i);
		fill_floor(image, game, i);
		i++;
	}
}

void	camera(void *param)
{
	t_game	*game;
	int		side;
	double	wallx;
	int		x;
	int		mapx;
	int		mapy;

	game = (t_game *)param;
	refresh_camera(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(game->ray, x);
		mapx = (int)game->ray->posx;
		mapy = (int)game->ray->posy;
		calc_sidedist(game->ray, &mapx, &mapy);
		game->ray->which_side = dda(game, &mapx, &mapy, &side);
		calculate_wall_distances(game, side);
		calc_wallx(game, side, &wallx);
		put_pixels(game, x, side, wallx);
		x++;
	}
}

void	start_game(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game->mlx)
	{
		printf("Error\nmlx_init failed\n");
		return ;
	}
	game->texture->background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (mlx_image_to_window(game->mlx, game->texture->background, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return ;
	}
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
	// DrawWalls(game);
	mlx_loop_hook(game->mlx, fill_background, game);
	mlx_loop_hook(game->mlx, &camera, game);
	mlx_loop_hook(game->mlx, &controls, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
}
