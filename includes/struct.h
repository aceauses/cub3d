/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:25 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/12 12:47:28 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "./cub3d.h"


# define PI 3.1415926535

typedef uint32_t	t_color;


typedef struct	s_game
{
	void				*mlx;
	size_t				height; // NOT in Pixels
	size_t				width; // NOT in Pixels
	void				*win;
	char				**map;
	char				**floor_colors;
	char				**ceiling_colors;
	t_color				floor;
	t_color				ceiling;
	struct s_player		*player;
	struct s_image		*image;
	struct s_ray		*ray;
	struct s_texture	*texture;
	mlx_image_t			*tmp_ray_image;
}						t_game;

typedef struct	s_player
{
	double				x;
	double				y;
	double				delta_x;
	double				delta_y;
	double				angle;
}						t_player;

typedef struct	s_ray
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
}						t_ray;

typedef struct	s_texture
{
	mlx_image_t			*no_image;
	mlx_image_t			*so_image;
	mlx_image_t			*we_image;
	mlx_image_t			*ea_image;
	mlx_image_t			*ray_image;
	mlx_texture_t		*no;
	mlx_texture_t		*so;
	mlx_texture_t		*we;
	mlx_texture_t		*ea;
	mlx_texture_t		*ray;
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;

}						t_texture;

#endif
