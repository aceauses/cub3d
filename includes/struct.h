/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/07 16:36:21 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "cub3d.h"

# define PI 3.1415926535

typedef struct	s_game
{
	void				*mlx;
	void				*win;
	char				**map;
	struct s_player		*player;
	struct s_img		*img;
	struct s_ray		*ray;
	struct s_texture	*texture;
}					t_game;

typedef struct	s_player
{
	float		x;
	float		y;
	float		delta_x;
	float		delta_y;
	float		angle;
}				t_player;

typedef struct	s_ray
{
	float		ray_angle;
	float		wall_hit_x;
	float		wall_hit_y;
	float		x_offset;
	float		y_offset;
}				t_ray;

typedef struct	s_img
{
	void			*img;
	struct s_game	*game;
	char			*path;
	int				width;
	int				height;
}				t_img;

typedef struct	s_texture
{
	struct s_img	*no;
	struct s_img	*so;
	struct s_img	*we;
	struct s_img	*ea;
	struct s_img	*flor;
	struct s_img	*ceiling;
}				t_texture;

typedef struct	s_color
{
	size_t		red;
	size_t		green;
	size_t		blue;
}				t_color;



#endif