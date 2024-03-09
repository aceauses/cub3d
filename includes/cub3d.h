/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:27 by aceauses          #+#    #+#             */
/*   Updated: 2024/03/08 16:42:12 by aceauses         ###   ########.fr       */
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

t_game	*init_data(char *argv);
void	free_game(t_game *game);
void	get_colors(char *argv, t_game *game);
bool	allocate_memory(t_player **player, t_ray **ray, t_texture **texture);
size_t	calculate_height(char **map);
size_t	calculate_width(char **map);
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
void DrawWalls(t_game *game);
// ray
void	check_vertical(t_game *game, double ft_tan);
void	check_horizontal(t_game *game, double ft_tan);
void	esc_free(t_game *game);
double	FixAng(double a);

// controls.c
void	controls(void* param);

//mlx init
int	init_mlx(t_game *game);

// mlx start
void	start_game(t_game *game);

#endif
