/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:52:54 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/18 17:09:54 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"

void	rotate_left(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->ray->dirX;
	game->ray->dirX = olddirx * cos(0.1) - game->ray->diry * sin(0.1);
	game->ray->diry = olddirx * sin(0.1) + game->ray->diry * cos(0.1);
	oldplanex = game->ray->planeX;
	game->ray->planeX = oldplanex * cos(0.1) - game->ray->planey * sin(0.1);
	game->ray->planey = oldplanex * sin(0.1) + game->ray->planey * cos(0.1);
}

void	rotate_right(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->ray->dirX;
	game->ray->dirX = olddirx * cos(-0.1) - game->ray->diry * sin(-0.1);
	game->ray->diry = olddirx * sin(-0.1) + game->ray->diry * cos(-0.1);
	oldplanex = game->ray->planeX;
	game->ray->planeX = oldplanex * cos(-0.1) - game->ray->planey * sin(-0.1);
	game->ray->planey = oldplanex * sin(-0.1) + game->ray->planey * cos(-0.1);
}

void	controls(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_right(game);
}
