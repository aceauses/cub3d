/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:38:27 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/08 09:27:20 by rmitache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "struct.h"

int		map_validation(char *argv);
char	*join_double_free(char *buffer, char *buff);
void	free_double_pointer(char **pointer);
char    *handle_tabs(char *line);

bool	init_data(char *argv);
size_t	calculate_height(char *argv);
bool allocate_memory(t_game **game, t_player **player);
size_t	calculate_height(char *argv);
size_t	calculate_width(char *argv);
char	**get_map_only(char *argv);
int		find_player_y(char **map);
int	find_player_x(char **map);
#endif
