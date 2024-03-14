#include "../includes/cub3d.h"
#include "../includes/struct.h"

void	set_angle_from_char(char c, t_player *player)
{
	
	(void)c;
	(void)player;
	// if (c == 'N')
	// 	player->angle = degToRad(270);
	// if (c == 'E')
	// 	player->angle = degToRad(0);
	// if (c == 'S')
	// 	player->angle = degToRad(90);
	// if (c == 'W')
	// 	player->angle = degToRad(180);
}

void	get_p_pos(char ***map, int *x, int *y, t_player *player)
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
				set_angle_from_char((*map)[i][j], player);
				return ;
			}
			j++;
		}
		i++;
	}
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