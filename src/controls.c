#include "../includes/cub3d.h"
#include "../includes/struct.h"

double degToRad(int a) { return a*M_PI/180.0;}

void	which_check_hit_wall(t_game *game, int r, double tmp_x, double tmp_y)
{
	if (game->ray->distH < game->ray->distV)
	{
		game->tmp_ray_image->instances[r].x = game->ray->x;
		game->tmp_ray_image->instances[r].y = game->ray->y;
		printf("distH[%d]: %f\n", r, game->ray->distH);
	}
	else
	{
		game->tmp_ray_image->instances[r].x = tmp_x;
		game->tmp_ray_image->instances[r].y = tmp_y;
		printf("distV[%d]: %f\n", r, game->ray->distV);
	}
}

void	convert_to_3d(t_game *game, int r)
{
	// if distH is big, then the wall is far away so less pixels to output
	(void)game;
	(void)r;
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_put_pixel(game->texture->ea_image, x0, y0, 0xFFFFFF); // Draw pixel at (x0, y0)
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void	CalculateRays(t_game *game)
{
	int		r;
	double	ft_tan;
	double	tmp_y;
	double	tmp_x;

	r = -1;
	game->ray->angle = FixAng((-game->player->angle) * 60);
	while (++r < 60)
	{
		ft_tan = tan(degToRad(game->ray->angle));
		game->ray->dof = 0;
		check_horizontal(game, ft_tan);
		tmp_x = game->ray->x;
		tmp_y = game->ray->y;
		game->ray->dof = 0;
		ft_tan = 1.0 / ft_tan;
		check_vertical(game, ft_tan);
		game->ray->angle = FixAng(game->ray->angle + 1);
		which_check_hit_wall(game, r, tmp_x, tmp_y);
		printf("image %d x%d y%d\n", r,game->ray->map_x, game->ray->map_y);
		if (game->ray->map_x >= 0 && game->ray->map_y >= 0)
			draw_line(game, game->player->x, game->player->y, game->tmp_ray_image->instances[0].x, game->tmp_ray_image->instances[0].y);
		convert_to_3d(game, r);
	}
}

void controls(void* param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		esc_free(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		move_player(game, 'W');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		move_player(game, 'S');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		move_player(game, 'A');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		move_player(game, 'D');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		rotate_player(game, 'L');
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		mlx_delete_image(game->mlx, game->texture->camera);
		game->texture->camera = mlx_new_image(game->mlx, WIDTH, HEIGHT);
		mlx_image_to_window(game->mlx, game->texture->camera, 0, 0);
		rotate_player(game, 'R');
	}
	CalculateRays(game);
	game->texture->ray_image->instances[0].x = (game->player->x + game->player->delta_x * 2);
	game->texture->ray_image->instances[0].y = (game->player->y + game->player->delta_y * 2);
}

void	move_player(t_game *game, char button)
{
	if (button == 'W')
	{
		game->player->x += game->player->delta_x * 1;
		game->player->y += game->player->delta_y * 1;
	}
	if (button == 'S')
	{
		game->player->x -= game->player->delta_x * 1;
		game->player->y -= game->player->delta_y * 1;
	}
	if (button == 'A')
	{
		game->player->x += game->player->delta_y * 1;
		game->player->y -= game->player->delta_x * 1;
	}
	if (button == 'D')
	{
		game->player->x -= game->player->delta_y * 1;
		game->player->y += game->player->delta_x * 1;
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