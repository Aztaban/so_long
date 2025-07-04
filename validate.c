/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:17:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/23 02:51:15 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

static int	validate_and_count(char c, t_count *count)
{
	if (c == PLAYER)
		count->player++;
	else if (c == EXIT)
		count->exit++;
	else if (c == COLLECTIBLE)
		count->collectibles++;
	else if (c != WALL && c != FLOOR)
		return (ERR_INVALID_CHAR);
	return (0);
}

static int	validate_line(t_map *map, t_count *count, t_player *player)
{
	int		i;
	int		error;
	char	*line;

	line = map->grid[map->height];
	if ((int)ft_strlen(line) != map->width)
		return (ERR_NOT_RECTANGULAR);
	i = 0;
	while (line[i])
	{
		if (line[i] == PLAYER)
		{
			player->x = i;
			player->y = map->height;
		}
		error = validate_and_count(line[i], count);
		if (error)
			return (error);
		i++;
	}
	return (0);
}

static int	validate_walls(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != WALL || map->grid[map->height -1][i] != WALL)
			return (ERR_WALLS);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != WALL || map->grid[i][map->width - 1] != WALL)
			return (ERR_WALLS);
		i++;
	}
	return (0);
}

static int	validate_format(t_map *map, t_player *player)
{
	int		error;
	t_count	count;

	count.player = 0;
	count.exit = 0;
	count.collectibles = 0;
	map->height = 0;
	map->width = ft_strlen(map->grid[0]);
	while (map->grid[map->height])
	{
		error = validate_line(map, &count, player);
		if (error)
			return (error);
		map->height++;
	}
	if (count.player != 1)
		return (ERR_PLAYER);
	if (count.exit != 1)
		return (ERR_EXIT);
	if (count.collectibles < 1)
		return (ERR_COLLECTIBLES);
	map->collectible_count = count.collectibles;
	return (validate_walls(map));
}

void	validate_map(t_game *game)
{
	int	err;

	err = validate_format(&game->map, &game->player);
	if (err == ERR_NOT_RECTANGULAR)
		exit_with_error(game, "Map not rectangular!");
	else if (err == ERR_INVALID_CHAR)
		exit_with_error(game, "Map contains a forbidden symbol!");
	else if (err == ERR_PLAYER)
		exit_with_error(game, "There must be exactly 1 player!");
	else if (err == ERR_EXIT)
		exit_with_error(game, "There must be exactly 1 exit!");
	else if (err == ERR_COLLECTIBLES)
		exit_with_error(game, "No collectibles found.");
	else if (err == ERR_WALLS)
		exit_with_error(game, "Missing walls around map");
	err = validate_path(game);
	if (err == ERR_WRONG_PATH)
		exit_with_error(game, "Wrong map. Exit or collectible not reachable.");
}
