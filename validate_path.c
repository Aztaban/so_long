/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 02:48:07 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/23 01:19:08 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
			free_map(copy);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == WALL || map[y][x] == FLOOD)
		return ;
	map[y][x] = FLOOD;
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
}

static int	check_path(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == COLLECTIBLE || map[y][x] == EXIT)
				return (ERR_WRONG_PATH);
			x++;
		}
		y++;
	}
	return (0);
}

int	validate_path(t_game *game)
{
	char	**copy;
	int		err;

	copy = copy_map(game->map.grid, game->map.height);
	if (!copy)
		return (ERR_WRONG_PATH);
	flood_fill(copy, game->player.x, game->player.y);
	err = check_path(copy);
	free_map(copy);
	return (err);
}
