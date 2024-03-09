#include "../includes/cub3d.h"
#include "../includes/struct.h"

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

void controls(void* param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->map[(int)(game->ray->posY + game->ray->dirY * 0.1)][(int)game->ray->posX] != '1')
			game->ray->posY += game->ray->dirY * 0.1;
		if (game->map[(int)game->ray->posY][(int)(game->ray->posX + game->ray->dirX * 0.1)] != '1')
			game->ray->posX += game->ray->dirX * 0.1;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->map[(int)(game->ray->posY - game->ray->dirY * 0.1)][(int)game->ray->posX] != '1')
			game->ray->posY -= game->ray->dirY * 0.1;
		if (game->map[(int)game->ray->posY][(int)(game->ray->posX - game->ray->dirX * 0.1)] != '1')
			game->ray->posX -= game->ray->dirX * 0.1;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map[(int)(game->ray->posY - game->ray->planeY * 0.1)][(int)game->ray->posX] != '1')
			game->ray->posY -= game->ray->planeY * 0.1;
		if (game->map[(int)game->ray->posY][(int)(game->ray->posX - game->ray->planeX * 0.1)] != '1')
			game->ray->posX -= game->ray->planeX * 0.1;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map[(int)(game->ray->posY + game->ray->planeY * 0.1)][(int)game->ray->posX] != '1')
			game->ray->posY += game->ray->planeY * 0.1;
		if (game->map[(int)game->ray->posY][(int)(game->ray->posX + game->ray->planeX * 0.1)] != '1')
			game->ray->posX += game->ray->planeX * 0.1;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		double oldDirX = game->ray->dirX;
		game->ray->dirX = game->ray->dirX * cos(0.1) - game->ray->dirY * sin(0.1);
		game->ray->dirY = oldDirX * sin(0.1) + game->ray->dirY * cos(0.1);
		double oldPlaneX = game->ray->planeX;
		game->ray->planeX = game->ray->planeX * cos(0.1) - game->ray->planeY * sin(0.1);
		game->ray->planeY = oldPlaneX * sin(0.1) + game->ray->planeY * cos(0.1);
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		double oldDirX = game->ray->dirX;
		game->ray->dirX = game->ray->dirX * cos(-0.1) - game->ray->dirY * sin(-0.1);
		game->ray->dirY = oldDirX * sin(-0.1) + game->ray->dirY * cos(-0.1);
		double oldPlaneX = game->ray->planeX;
		game->ray->planeX = game->ray->planeX * cos(-0.1) - game->ray->planeY * sin(-0.1);
		game->ray->planeY = oldPlaneX * sin(-0.1) + game->ray->planeY * cos(-0.1);
	}
}
