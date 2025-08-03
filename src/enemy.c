/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:39:36 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 00:34:21 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Randomly determines enemy movement direction (up/down/left/right).
// Updates new_x and new_y based on the chosen direction.
// Returns the direction as a sprite state.
static int	decide_enemy_move(int x, int y, int *new_x, int *new_y)
{
	int	random;

	random = rand() % 4;
	*new_x = x;
	*new_y = y;
	if (random == SPR_RIGHT)
		(*new_x)++;
	else if (random == SPR_LEFT)
		(*new_x)--;
	else if (random == SPR_DOWN)
		(*new_y)++;
	else if (random == SPR_UP)
		(*new_y)--;
	return (random);
}

// Attempts to move an enemy from (x, y) to a new position.
// If the new position is the player, triggers game over.
// Otherwise, updates grid and redraws enemy.
static void	move_enemy(t_game *game, int x, int y)
{
	int		new_x;
	int		new_y;
	char	tile;

	game->textures.enemy.current = decide_enemy_move(x, y, &new_x, &new_y);
	tile = game->map.grid[new_y][new_x];
	if (new_x == game->player.x && new_y == game->player.y)
	{
		ft_printf("Orcs got you after %i steps.\n", ++game->player.moves_count);
		exit_game(game);
	}
	if (tile == WALL || tile == COLLECTIBLE || tile == ENEMY || tile == EXIT)
		return ;
	game->map.grid[y][x] = FLOOR;
	game->map.grid[new_y][new_x] = FLOOD;
	draw_tile(game, FLOOR, x, y);
	draw_tile(game, ENEMY, new_x, new_y);
}

// Restores the map state by converting temporary FLOOD marks back to ENEMY.
static void	fix_enemy_grid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == FLOOD)
				game->map.grid[y][x] = ENEMY;
			x++;
		}
		y++;
	}
}

void	update_enemies(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == ENEMY)
				move_enemy(game, x, y);
			x++;
		}
		y++;
	}
	fix_enemy_grid(game);
}
