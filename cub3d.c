/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmitache <rmitache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 21:34:37 by aceauses          #+#    #+#             */
/*   Updated: 2024/02/09 15:48:15 by rmitache         ###   ########.fr       */
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
	if (argc != 2)
	{
		printf("Error\nWrong number of arguments\n");
		return (0);
	}
	if (!ft_strcmp(argv[2], "-l"))
		atexit(check_leaks);
	if (map_validation(argv[1]))
	{
		if (init_data(argv[1]) == false)
			return (1);
		// Do mlx stuff
	}
	// system("leaks cub3d");
	return (0);
}
