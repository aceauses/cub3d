/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:27 by aceauses          #+#    #+#             */
/*   Updated: 2024/07/09 18:24:39 by aceauses         ###   ########.fr       */
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

# define EMPTY_MAP "Empty map"
# define PATH_ERROR "Invalid path in the map file"
# define RGB_ERROR "Please enter RGB values in the format: R, G, B"
# define RGB_ERROR_2 "Invalid RGB values, must be between 0 and 255"
# define CANNOT_FIND_F "Cannot find the Floor color"
# define CANNOT_FIND_C "Cannot find the Ceiling color"
# define INV_PLAYER "More than one player in the map or invalid map"
# define INVALID_MAP "Invalid map"
# define NL "Found a new line"

# define W_RATIO 0.008333
# define H_RATIO 0.014815

int		map_validation(char *argv);
int		check_player(char **map);
char	**read_map(char *argv);
int		find_first_character(char **map, int *x, int *y, int C);
char	**copy_map(char **matrix, int y);

/* Map Errors */
void	map_errors(char *error);
void	map_error_exit(char *error);

/* Map Validation 1 */
char	*handle_tabs(char *line);
char	**read_map(char *argv);
int		map_validation(char *argv);

/* Map Values Utils */
int		should_check_path(char **split, char *buffer, int *check);
int		clean_compare(char *s1, char *set, size_t n);

/* Map Values */
int		check_map_values(char **map);

/* Map Walls Utils */
int		check_inside_map(char **map);
int		check_map_walls(char **map);
int		check_walls(char **map);

/* Map Walls */
int		find_first_character(char **map, int *x, int *y, int C);
char	**copy_map(char **matrix, int y);
void	fill(char **matrix, int y, int x, int *good);
int		skip_first_spaces(char *line);
int		check_horizontal_walls(char **map);

/* Raycast Utils 1 */
int		calculate_side(t_game *game, int side);
int		dda(t_game *game, int *mapX, int *mapY, int *side);
void	calculate_wall_distances(t_game *game, int side, int mapx, int mapy);
void	calc_wallx(t_game *game, int side, double *wallx);

/* Raycast Utils 2 */
int		calculate_tex(double texpos, char c);
int		clamp(int value, int min, int max);
int		calculate_tex_index(int texX, int texY);

/* Raycast Utils */
int		get_texture_color(t_game *game, int texindex);
void	init_ray(t_ray *ray, int x);
void	put_pixels(t_game *game, int x, double wallX);
void	calc_sidedist(t_ray *ray, int *mapX, int *mapY);
void	refresh_camera(t_game *game);

/* Colors */
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

/* Fill Background */
void	fill_ceiling(mlx_image_t *image, t_game *game, int i);
void	fill_floor(mlx_image_t *image, t_game *game, int i);
void	fill_background(void *param);

/* Controls Utils */
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_left(t_game *game);
void	move_right(t_game *game);

/* Controls */
void	rotate_right(t_game *game);
void	rotate_left(t_game *game);
void	controls(void *param);

/* Init Utils */
int		open_fd(char *argv);
void	get_floor(t_game *game, char *line);
void	get_ceiling(t_game *game, char *line);
void	get_colors(char *argv, t_game *game);
void	free_game(t_game *game);

/* Init Utils 2 */
void	set_angle_from_char(char c, t_ray *ray);
char	get_p_pos(char ***map, double *x, double *y);
int		init_textures(t_game *game);

/* Init */
bool	allocate_memory(t_ray **ray, t_texture **texture);
bool	get_texture(t_game *game);
t_game	*init_data(char *argv);

/* Mlx Init */ // Do we still need this?
int		init_mlx(t_game *game);

/* mlx */
void	fill_ceiling(mlx_image_t *image, t_game *game, int i);
void	fill_floor(mlx_image_t *image, t_game *game, int i);
void	fill_background(void *param);
void	camera(void *param);
void	start_game(t_game *game);

/* Utils 1 */
char	*join_double_free(char *buffer, char *buff);
void	free_double_pointer(char **pointer);
void	free_double_texture(mlx_texture_t **texture_pointer);
int		array_length(char **pointer);

void	DrawWalls(t_game *game);

#endif
