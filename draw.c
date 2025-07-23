/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:57 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/24 00:40:23 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game, char tile, int x, int y)
{
	void	*img;

	if (tile == WALL)
		img = game->textures.wall;
	else if (tile == FLOOR)
		img = game->textures.floor;
	else if (tile == COLLECTIBLE)
		img = game->textures.collectible.frame[SPR_DOWN];
	else if (tile == EXIT)
	{
		if (game->map.collectible_count == 0)
			img = game->textures.exit_open;
		else
			img = game->textures.exit;
	}
	else if (tile == PLAYER)
		img = game->textures.player.frame[game->textures.player.current];
	else if (tile == ENEMY)
		img = game->textures.enemy.frame[game->textures.enemy.current];
	else
		return ;
	mlx_put_image_to_window(game->mlx_display, game->win,
		img, x * TILE_SIZE, y * TILE_SIZE);
}

void	draw_map(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			draw_tile(game, game->map.grid[y][x], x, y);
			x++;
		}
		y++;
	}
}
