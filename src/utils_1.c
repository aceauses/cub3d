/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:26:56 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/02 17:34:49 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char *join_double_free(char *buffer, char *buff)
{
	char *temp;

	temp = ft_strjoin_gnl(buffer, buff);
	free(buffer);
	free(buff);
	return (temp);
}

void	free_double_pointer(char **pointer)
{
	int		i;

	i = 0;
	while (pointer && pointer[i])
		free(pointer[i++]);
	free(pointer);
}