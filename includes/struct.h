/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/18 16:29:55 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./cub3d.h"

# define PI 3.1415926535
# define HEIGHT 1080 // 2k resolution 2160
# define WIDTH 1920 // 4k resolution 3840
# define NUM_BUFFERS 2

typedef struct s_game
{
	void				*mlx;
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
	double				posx;
	double				posy;
	double				dirX;
	double				diry;
	double				planeX;
	double				planey;
	double				raydirx;
	double				raydiry;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				perpwalldist;
	double				camerax;
	int					stepx;
	int					stepy;
	int					hitted;
	int					which_side;
	double				lineHeight;
	int					drawStart;
	int					drawEnd;
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
