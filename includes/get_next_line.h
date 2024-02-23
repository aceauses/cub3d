/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:45:36 by aceauses          #+#    #+#             */
/*   Updated: 2024/01/31 15:47:58 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 52
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

char	*get_next_line(int fd);

void	*ft_calloc_gnl(size_t count, size_t size);
char	*ft_strjoin_gnl(char const *line, char const *new_line);
size_t	ft_strlen_mod(const char *str);
char	*ft_strchr_gnl(const char *str, int c);
char	*free_join(char *buffer, char *buff);

#endif