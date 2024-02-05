/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:27 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/05 18:36:22 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define PATH_ERROR "Invalid path in the map file"
# define RGB_ERROR "Please enter RGB values in the format: R, G, B"
# define RGB_ERROR_2 "Invalid RGB values, must be between 0 and 255"

int		map_validation(char *argv);
char	*join_double_free(char *buffer, char *buff);
void	free_double_pointer(char **pointer);
int		check_map_values(char **map);
int		check_walls(char **map);
void	map_errors(char *error);
#endif