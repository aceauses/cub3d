/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:05:57 by rmitache          #+#    #+#             */
/*   Updated: 2024/03/23 17:58:41 by aceauses         ###   ########.fr       */
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
	mlx_set_instance_depth(image->instances, -1);
}
