/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/08 10:18:33 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./cub3d.h"


# define PI 3.1415926535

typedef struct	s_game
{
	void				*mlx;
	size_t				height; // NOT in Pixels
	size_t				width; // NOT in Pixels
	void				*win;
	char				**map;
	struct s_player		*player;
	struct s_image		*image;
	struct s_ray		*ray;
	struct s_texture	*texture;
	struct s_color		*color;
}						t_game;

typedef struct	s_player
{
	int			x;
	int			y;
	double			delta_x;
	double			delta_y;
	double			angle;
}					t_player;

typedef struct	s_ray
{
	double		ray_angle;
	double		wall_hit_x;
	double		wall_hit_y;
	double		x_offset;
	double		y_offset;
}				t_ray;

typedef struct	s_texture
{
	mlx_image_t		*image;
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
	struct s_color	*flor;
	struct s_color	*ceiling;
}				t_texture;

typedef struct	s_color
{
	size_t		red;
	size_t		green;
	size_t		blue;
}				t_color;



#endif
