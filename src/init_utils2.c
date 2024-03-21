/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:30:01 by rmitache          #+#    #+#             */
/*   Updated: 2024/03/21 14:33:09 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/struct.h"

static void	set_angle_from_char_rest(char c, t_ray *ray)
{
	if (c == 'S')
	{
		ray->dirx = 0;
		ray->diry = 1;
		ray->planex = -0.66;
		ray->planey = 0;
		return ;
	}
	if (c == 'E')
	{
		ray->dirx = 1;
		ray->diry = 0;
		ray->planex = 0;
		ray->planey = 0.66;
		return ;
	}
}

void	set_angle_from_char(char c, t_ray *ray)
{
	if (c == 'W')
	{
		ray->dirx = -1;
		ray->diry = 0;
		ray->planex = 0;
		ray->planey = -0.66;
		return ;
	}
	if (c == 'N')
	{
		ray->dirx = 0;
		ray->diry = -1;
		ray->planex = 0.66;
		ray->planey = 0;
		return ;
	}
	set_angle_from_char_rest(c, ray);
}

char	get_p_pos(char ***map, double *x, double *y)
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
				*y = i;
				*x = j;
				return ((*map)[i][j]);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	init_textures(t_game *game)
{
	game->texture->sprite = malloc(sizeof(mlx_texture_t *) * 4);
	if (!game->texture->sprite)
		return (0);
	game->texture->sprite[0] = mlx_load_png(game->texture->path[0]);
	game->texture->sprite[1] = mlx_load_png(game->texture->path[1]);
	game->texture->sprite[2] = mlx_load_png(game->texture->path[2]);
	game->texture->sprite[3] = mlx_load_png(game->texture->path[3]);
	return (1);
}
