/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/25 13:37:45 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./cub3d.h"

# define HEIGHT			600
# define WIDTH			800
# define NUM_BUFFERS	2

typedef struct s_game
{
	void				*mlx;
	char				**cub_file;
	char				**map;
	struct s_ray		*ray;
	struct s_texture	*texture;
}						t_game;

typedef struct s_ray
{
	double				posx;
	double				posy;
	double				dirx;
	double				diry;
	double				planex;
	double				planey;
	double				raydirx;
	double				raydiry;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				perpwalldist;
	double				camerax;
	int					side;
	int					stepx;
	int					stepy;
	int					hitted;
	int					which_side;
	double				lineheight;
	int					drawstart;
	int					drawend;
}						t_ray;

typedef struct s_texture
{
	mlx_image_t			*ray_image;
	char				**path;
	mlx_image_t			*background;
	mlx_image_t			*camera[NUM_BUFFERS];
	int					current_buffer;
	mlx_texture_t		**sprite;
	mlx_image_t			*map_wall;
	mlx_image_t			*map_player;
	struct s_color		*floor;
	struct s_color		*ceiling;
}						t_texture;

typedef struct s_color
{
	int					red;
	int					green;
	int					blue;
}						t_color;

#endif