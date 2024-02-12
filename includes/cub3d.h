/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:27 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/12 12:49:07 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "struct.h"

# define SIZE 64

# define PATH_ERROR "Invalid path in the map file"
# define RGB_ERROR "Please enter RGB values in the format: R, G, B"
# define RGB_ERROR_2 "Invalid RGB values, must be between 0 and 255"
# define CANNOT_FIND_F "Cannot find the Floor color"
# define CANNOT_FIND_C "Cannot find the Ceiling color"
# define INVALID_MAP "Invalid map"

int	map_validation(char *argv);

char	*join_double_free(char *buffer, char *buff);
void	free_double_pointer(char **pointer);
char    *handle_tabs(char *line);

bool	init_data(char *argv);
size_t	calculate_height(char *argv);
bool	allocate_memory(t_game **game, t_player **player, t_ray **ray, t_texture **texture);
 char	**get_map_only(char *argv, t_game *game);
int		array_length(char **pointer);
char	*handle_tabs(char *line);
int		check_map_values(char **map);
int		check_walls(char **map);
void	map_errors(char *error);
int		should_check_path(char **split, char *buffer, int *check);
int		clean_compare(char *s1, char *set, size_t n);
char    *handle_tabs(char *line);

bool	init_data(char *argv);
size_t	calculate_height(char *argv);
bool allocate_memory(t_game **game, t_player **player, t_ray **ray, t_texture **texture);
void	assign_path_to_texture(char *argv, t_game *game);

int get_rgba(int r, int g, int b, int a);
int open_fd(char *argv);

void	get_colors(char *argv, char ***floor_colors, char ***ceiling_colors);
void	get_window_size(char *argv, size_t	*height, size_t	*width);
void	get_player_position(char	***map, double *x, double *y);
#endif
