/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:17:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/21 22:41:33 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

static int	validate_format(t_map *map)
{
	//int	player;
	//int	exit;

	//player = 0;
	//exit = 0;
	map->height = 0;
	map->width = ft_strlen(map->grid[0]) - 1;
	while (map->grid[map->height])
	{
/* 		if((int)ft_strlen(map->grid[map->height]) != map->width)
			return (1); */
		map->height++;
	}
	return (1);
}

static int	validate_path(t_map *map)
{
	(void)map;
	return (1);
}

void validate_map(t_game *game)
{
	if (!validate_format(&game->map))
		exit_with_error(game, "Wrong map format");
	if (!validate_path(&game->map))
		exit_with_error(game, "wrong map path.");
}