/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 01:17:43 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 00:41:48 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

// Checks individual characters in a line for validity and counts key elements.
// Updates player start position, exit, and collectible counters.
// Returns error code if an invalid character is found.
static int	validate_and_count(t_game *game, t_count *count, int x)
{
	char	c;

	c = game->map.grid[game->map.height][x];
	if (c == PLAYER)
	{
		game->player.x = x;
		game->player.y = game->map.height;
		count->player++;
	}
	else if (c == EXIT)
	{
		game->map.x_exit = x;
		game->map.y_exit = game->map.height;
		count->exit++;
	}
	else if (c == COLLECTIBLE)
		count->collectibles++;
	else if (c != WALL && c != FLOOR && c != ENEMY)
		return (ERR_INVALID_CHAR);
	return (0);
}

// Validates one line of the map: checks length and valid characters.
// Also counts key map components (P, E, C).
static int	validate_line(t_game *game, t_count *count)
{
	int		i;
	int		error;
	char	*line;

	line = game->map.grid[game->map.height];
	if ((int)ft_strlen(line) != game->map.width)
		return (ERR_NOT_RECTANGULAR);
	i = 0;
	while (line[i])
	{
		error = validate_and_count(game, count, i);
		if (error)
			return (error);
		i++;
	}
	return (0);
}

// Ensures the map is surrounded by walls (top, bottom, left, right).
// Returns error if any border is not a wall.
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

// Validates overall map format: size, required characters, and wall boundaries.
// Sets map height and collectible count. Returns appropriate error code.
static int	validate_format(t_game *game)
{
	int		error;
	t_count	count;

	count.player = 0;
	count.exit = 0;
	count.collectibles = 0;
	game->map.height = 0;
	game->map.width = ft_strlen(game->map.grid[0]);
	while (game->map.grid[game->map.height])
	{
		error = validate_line(game, &count);
		if (error)
			return (error);
		game->map.height++;
	}
	if (count.player != 1)
		return (ERR_PLAYER);
	if (count.exit != 1)
		return (ERR_EXIT);
	if (count.collectibles < 1)
		return (ERR_COLLECTIBLES);
	game->map.collectible_count = count.collectibles;
	return (validate_walls(&game->map));
}

// Orchestrates full map validation: format, content, walls, and path.
// Exits with error message if any check fails.
void	validate_map(t_game *game)
{
	int	err;

	err = validate_format(game);
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
