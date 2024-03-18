/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:01:11 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/18 17:01:20 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_game *game)
{
	int		px;
	int		py;
	double	new_posx;
	double	new_posy;

	px = (int)game->ray->posx;
	py = (int)game->ray->posy;
	new_posx = game->ray->posx + game->ray->dirX * 0.1;
	new_posy = game->ray->posy + game->ray->diry * 0.1;
	if (game->map[(int)new_posy][px] != '1'
		&& game->map[py][(int)new_posx] != '1')
	{
		game->ray->posx = new_posx;
		game->ray->posy = new_posy;
	}
}

void	move_backward(t_game *game)
{
	int		px;
	int		py;
	double	new_posx;
	double	new_posy;

	px = (int)game->ray->posx;
	py = (int)game->ray->posy;
	new_posx = game->ray->posx - game->ray->dirX * 0.1;
	new_posy = game->ray->posy - game->ray->diry * 0.1;
	if (game->map[(int)new_posy][px] != '1'
		&& game->map[py][(int)new_posx] != '1')
	{
		game->ray->posx = new_posx;
		game->ray->posy = new_posy;
	}
}

void	move_left(t_game *game)
{
	int		px;
	int		py;
	double	new_posx;
	double	new_posy;

	px = (int)game->ray->posx;
	py = (int)game->ray->posy;
	new_posx = game->ray->posx - game->ray->planeX * 0.1;
	new_posy = game->ray->posy - game->ray->planey * 0.1;
	if (game->map[(int)new_posy][px] != '1'
		&& game->map[py][(int)new_posx] != '1')
	{
		game->ray->posx = new_posx;
		game->ray->posy = new_posy;
	}
}

void	move_right(t_game *game)
{
	int		px;
	int		py;
	double	new_posx;
	double	new_posy;

	px = (int)game->ray->posx;
	py = (int)game->ray->posy;
	new_posx = game->ray->posx + game->ray->planeX * 0.1;
	new_posy = game->ray->posy + game->ray->planey * 0.1;
	if (game->map[(int)new_posy][px] != '1'
		&& game->map[py][(int)new_posx] != '1')
	{
		game->ray->posx = new_posx;
		game->ray->posy = new_posy;
	}
}
