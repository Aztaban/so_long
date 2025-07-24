/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 02:37:53 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/24 22:03:40 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	update_collectible_frame(t_game *game)
{
	static int	ticks;
	int			*current;

	ticks++;
	current = &game->textures.collectible.current;
	if (*current == SPR_DOWN && ticks < 2000)
		return ;
	if (ticks < 1000)
		return ;
	ticks = 0;
	(*current)++;
	if (*current >= FRAME_COUNT)
		*current = 0;
}

static void	redraw_collectibles(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == COLLECTIBLE)
			{
				mlx_put_image_to_window(game->mlx_display, game->win,
					game->textures.collectible.frame[
					game->textures.collectible.current],
					x * TILE_SIZE, y * TILE_SIZE);
			}
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	update_collectible_frame(game);
	redraw_collectibles(game);
	return (0);
}
