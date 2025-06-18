/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:17:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/19 01:45:45 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_format(t_map *map)
{
	int	player;
	int	exit;

	player = 0;
	exit = 0;
	map->height = 0;
	map->width = ft_strlen(map->grid[0]);
	while (map->grid[map->height])
	{
		if(ft_strlen(map->grid[map->height]) != map->width)
			return (-1);
	}
}

static int	validate_path(t_map *map)
{
	return (1);
}

void validate_map(t_game *game)
{
	if (!validate_format(&game->map))
		exit_with_error("Wrong map format", 2);
	if (!validate_path(&game->map))
		exit_with_error("wrong map path.", 2);
}