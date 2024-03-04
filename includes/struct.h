/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/28 18:05:32 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./cub3d.h"

# define PI 3.1415926535
# define HEIGHT 1080
# define WIDTH 1920

typedef struct s_game
{
	void				*mlx;
	size_t				height; // NOT in Pixels
	size_t				width;  // NOT in Pixels
	char				**cub_file;
	char				**map;
	double				distance;
	double				distance_jos;
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
	double				angle;
	int					x;
	int					y;
	double				x_offset;
	double				y_offset;
	int					map_x;
	int					dof;
	int					map_y;
	int					map_p;
	double				distH;
	double				distV;
	double				posX; // x and y start position Player
	double				posY;
	double				dirX; //initial direction vector
	double				dirY;
	double				planeX; //the 2d raycaster version of camera plane
	double				planeY; 
	double				ray_angle;
	double				wall_hit_x;
	double				wall_hit_y;
}						t_ray;

typedef struct s_texture
{
	mlx_image_t			*no_image;
	mlx_image_t			*so_image;
	mlx_image_t			*we_image;
	mlx_image_t			*ea_image;
	mlx_image_t			*ray_image;
	char				**path;
	mlx_image_t			*background;
	mlx_image_t			*camera;
	mlx_image_t			*buffer_camera;
	mlx_image_t			*image;
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
