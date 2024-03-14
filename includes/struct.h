/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/14 21:43:42 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./cub3d.h"

# define PI 3.1415926535
# define HEIGHT 1080
# define WIDTH 1920
#define NUM_BUFFERS 2

typedef struct s_game
{
	void				*mlx;
	size_t				height; // NOT in Pixels
	size_t				width;  // NOT in Pixels
	char				**cub_file;
	char				**map;
	struct s_player		*player;
	struct s_image		*image;
	struct s_ray		*ray;
	struct s_texture	*texture;
	mlx_image_t			*tmp_ray_image;
}						t_game;

typedef struct s_player
{
	int					x;
	int					y;
	double				delta_x;
	double				delta_y;
	double				angle;
}						t_player;

typedef struct s_ray
{
	double				posX; // x and y start position Player
	double				posY;
	double				dirX; //initial direction vector
	double				dirY;
	double				planeX; //the 2d raycaster version of camera plane
	double				planeY; 
	double				rayDirX;
	double				rayDirY;
	double				sideDistX;
	double				sideDistY;
	double				deltaDistX;
	double				deltaDistY;
	double				perpWallDist;
	double				cameraX;
	int					stepX;
	int					stepY;
}						t_ray;

typedef struct s_texture
{
	mlx_image_t			**images;
	mlx_image_t			*ray_image;
	char				**path;
	mlx_image_t			*background;
	mlx_image_t			*camera[NUM_BUFFERS];
	int					current_buffer;
	mlx_image_t			*image;
	mlx_texture_t		**sprite;
	mlx_texture_t		*no;
	mlx_texture_t		*so;
	mlx_texture_t		*we;
	mlx_texture_t		*ea;
	mlx_texture_t		*ray;
	struct s_color		*floor;
	struct s_color		*ceiling;
}						t_texture;

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
}						t_color;

#endif
