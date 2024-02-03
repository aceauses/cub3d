/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aceauses <aceauses@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:34:37 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/03 18:00:51 by aceauses         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	check_leaks()
{
	system("leaks cub3d");
}

int main(int argc, char **argv)
{
	(void)argc;
	// if (argc != 2)
	// {
	// 	printf("Error\nWrong number of arguments\n");
	// 	return (0);
	// }
	if (!ft_strcmp(argv[2], "-l"))
		atexit(check_leaks);
	if (map_validation(argv[1]))
	{
		// Do mlx stuff
	}
	// system("leaks cub3d");
	return (0);
}
