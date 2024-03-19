#include "../includes/cub3d.h"
#include "../includes/struct.h"

void	set_angle_from_char(char c, t_ray *ray)
{
	if (c == 'W')
	{
		ray->dirX = -1;
		ray->diry = 0;
		ray->planeX = 0;
		ray->planey = -0.66;
	}
	if (c == 'N')
	{
		ray->dirX = 0;
		ray->diry = -1;
		ray->planeX = 0.66;
		ray->planey = 0;
	}
	if (c == 'S')
	{
		ray->dirX = 0;
		ray->diry = 1;
		ray->planeX = -0.66;
		ray->planey = 0;
	}
	if (c == 'E')
	{
		ray->dirX = 1;
		ray->diry = 0;
		ray->planeX = 0;
		ray->planey = 0.66;
	}
}

char	get_p_pos(char ***map, int *x, int *y)
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
