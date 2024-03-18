/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:27 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/18 20:46:28 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include "struct.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define SIZE 64

# define PATH_ERROR "Invalid path in the map file"
# define RGB_ERROR "Please enter RGB values in the format: R, G, B"
# define RGB_ERROR_2 "Invalid RGB values, must be between 0 and 255"
# define CANNOT_FIND_F "Cannot find the Floor color"
# define CANNOT_FIND_C "Cannot find the Ceiling color"
# define INVALID_MAP "Invalid map"

int		map_validation(char *argv);
char	**read_map(char *argv);
int		find_first_character(char **map, int *x, int *y, int C);
char	**copy_map(char **matrix, int y);

char	*join_double_free(char *buffer, char *buff);
void	free_double_pointer(char **pointer);
char	*handle_tabs(char *line);

int		init_textures(t_game *game);

t_game	*init_data(char *argv);
void	free_game(t_game *game);
void	get_colors(char *argv, t_game *game);
bool	allocate_memory(t_player **player, t_ray **ray, t_texture **texture);
int		array_length(char **pointer);
char	*handle_tabs(char *line);
int		check_map_values(char **map);
int		check_walls(char **map);
void	map_errors(char *error);
int		should_check_path(char **split, char *buffer, int *check);
int		clean_compare(char *s1, char *set, size_t n);\

int		get_rgba(int r, int g, int b, int a);
int		open_fd(char *argv);

void	get_p_pos(char ***map, int *x, int *y, t_player *player);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
void DrawWalls(t_game *game);
// ray
void	init_ray(t_ray *ray, int x);
void	calc_sidedist(t_ray *ray, int *mapX, int *mapY);
int		dda(t_game *game, int *mapX, int *mapY, int *side);
void	calculate_wall_distances(t_game *game, int side);
void	put_pixels(t_game *game, int x, int side, double wallX);
int		calculate_side(t_game *game, int side);
void	refresh_camera(t_game *game);
void	calc_wallx(t_game *game, int side, double *wallx);

// controls.c
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);
void	controls(void *param);

//mlx init
int	init_mlx(t_game *game);

// mlx start
void	start_game(t_game *game);

#endif
