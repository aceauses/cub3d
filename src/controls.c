/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 17:52:54 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/21 12:58:15 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"

void	rotate_right(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->ray->dirx;
	game->ray->dirx = olddirx * cos(0.1) - game->ray->diry * sin(0.1);
	game->ray->diry = olddirx * sin(0.1) + game->ray->diry * cos(0.1);
	oldplanex = game->ray->planex;
	game->ray->planex = oldplanex * cos(0.1) - game->ray->planey * sin(0.1);
	game->ray->planey = oldplanex * sin(0.1) + game->ray->planey * cos(0.1);
}

void	rotate_left(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->ray->dirx;
	game->ray->dirx = olddirx * cos(-0.1) - game->ray->diry * sin(-0.1);
	game->ray->diry = olddirx * sin(-0.1) + game->ray->diry * cos(-0.1);
	oldplanex = game->ray->planex;
	game->ray->planex = oldplanex * cos(-0.1) - game->ray->planey * sin(-0.1);
	game->ray->planey = oldplanex * sin(-0.1) + game->ray->planey * cos(-0.1);
}

void	mouse_direction(t_game *game)
{
	int		x;
	int		y;
	double	olddirx;
	double	oldplx;

	x = 0;
	mlx_get_mouse_pos(game->mlx, &x, &y);
	if (x < WIDTH / 2)
	{
		olddirx = game->ray->dirx;
		game->ray->dirx = olddirx * cos(-0.1) - game->ray->diry * sin(-0.1);
		game->ray->diry = olddirx * sin(-0.1) + game->ray->diry * cos(-0.1);
		oldplx = game->ray->planex;
		game->ray->planex = oldplx * cos(-0.1) - game->ray->planey * sin(-0.1);
		game->ray->planey = oldplx * sin(-0.1) + game->ray->planey * cos(-0.1);
	}
	else if (x > WIDTH / 2)
	{
		olddirx = game->ray->dirx;
		game->ray->dirx = olddirx * cos(0.1) - game->ray->diry * sin(0.1);
		game->ray->diry = olddirx * sin(0.1) + game->ray->diry * cos(0.1);
		oldplx = game->ray->planex;
		game->ray->planex = oldplx * cos(0.1) - game->ray->planey * sin(0.1);
		game->ray->planey = oldplx * sin(0.1) + game->ray->planey * cos(0.1);
	}
}

void	controls(void *param)
{
	t_game	*game;

	game = param;
	mouse_direction(game);
	mlx_set_mouse_pos(game->mlx, WIDTH / 2, HEIGHT / 2);
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
