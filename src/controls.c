#include "../includes/cub3d.h"
#include "../includes/struct.h"

double degToRad(int a) { return a*M_PI/180.0;}

void	CalculateRays(t_game *game)
{
	check_vertical(game);
	// check_horizontal(game);

	// translate_to_3d(game);
}

void controls(void* param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		esc_free(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_player(game, 'W');
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_player(game, 'S');
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_player(game, 'A');
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_player(game, 'D');
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate_player(game, 'L');
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate_player(game, 'R');
	CalculateRays(game);
	game->texture->ray_image->instances[0].x = (game->player->x + game->player->delta_x * 5);
	game->texture->ray_image->instances[0].y = (game->player->y + game->player->delta_y * 5);
}

void	move_player(t_game *game, char button)
{
	if (button == 'W')
	{
		game->player->x += game->player->delta_x * 5;
		game->player->y += game->player->delta_y * 5;
	}
	if (button == 'S')
	{
		game->player->x -= game->player->delta_x * 5;
		game->player->y -= game->player->delta_y * 5;
	}
	if (button == 'A')
	{
		game->player->x += game->player->delta_y * 5;
		game->player->y -= game->player->delta_x * 5;
	}
	if (button == 'D')
	{
		game->player->x -= game->player->delta_y * 5;
		game->player->y += game->player->delta_x * 5;
	}
}

void	rotate_player(t_game *game, char button)
{
	if (button == 'L')
	{
		game->player->angle -= 0.1;
		if (game->player->angle < 0)
			game->player->angle = PI * 2;
		game->player->delta_x = cos(game->player->angle) * 2;
		game->player->delta_y = sin(game->player->angle) * 2;
	}
	if (button == 'R')
	{
		game->player->angle += 0.1;
		if (game->player->angle > PI * 2)
			game->player->angle -= PI * 2;
		game->player->delta_x = cos(game->player->angle) * 2;
		game->player->delta_y = sin(game->player->angle) * 2;
	}
}