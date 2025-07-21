/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:57 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/21 02:11:54 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_tile(t_game *game, char tile, int x, int y)
{
	void	*img;

	if (tile == '1')
		img = game->textures.wall;
	else if (tile == '0')
		img = game->textures.floor;
	else if (tile == 'C')
		// TODO Change collectible textures print to loopt through sprite (iddle animation)
		img = game->textures.collectible;
	else if (tile == 'E')
	{
		if (game->map.collectible_count == 0)
			img = game->textures.exit_open;
		else
			img = game->textures.exit;
	}
	else if (tile == 'P')
		// TODO Add method for drawing player sprites (enemy later)
			img = game->textures.player;
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
