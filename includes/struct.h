/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/22 18:58:04 by aceauses         ###   ########.fr       */
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
	size_t m_height; // NOT in Pixels
	size_t m_width;  // NOT in Pixels
	char				**cub_file;
	char				**map;
	char				**floor;
	char				**ceiling;
	double				distance;
	double				distance_jos;
	struct s_player		*player;
	struct s_image		*image;
	struct s_ray		*ray;
	struct s_texture	*texture;
	struct s_color		*color;
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
	double				ray_angle;
	double				wall_hit_x;
	double				wall_hit_y;
	double				x_offset;
	double				y_offset;
}						t_ray;

typedef struct s_texture
{
	char				**path;
	mlx_image_t			*background;
	mlx_image_t			*camera;
	mlx_image_t			*image;
	mlx_texture_t		*no;
	mlx_texture_t		*so;
	mlx_texture_t		*we;
	mlx_texture_t		*ea;
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
