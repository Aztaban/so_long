/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:13:47 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/19 14:06:29 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_player(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	tile;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	tile = game->map.grid[new_y][new_x];
	if (tile == COLLECTIBLE)
	{
		game->map.grid[new_y][new_x] = FLOOR;
		game->map.collectible_count--;
	}
	if (tile == EXIT && game->map.collectible_count == 0)
	{
		ft_printf("You finished with %i steps.\n", ++game->player.moves_count);
		exit_game(game);
	}
	if (tile == EXIT || tile == WALL)
		return ;
	draw_tile(game, FLOOR, game->player.x, game->player.y);
	game->player.x = new_x;
	game->player.y = new_y;
	game->player.moves_count++;
	draw_tile(game, PLAYER, game->player.x, game->player.y);
	ft_printf("You walked %d steps\n", game->player.moves_count);
}

int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		exit_game(game);
	else if (keycode == KEY_W)
		move_player(game, 0, -1);
	else if (keycode == KEY_S)
		move_player(game, 0, 1);
	else if (keycode == KEY_A)
		move_player(game, -1, 0);
	else if (keycode == KEY_D)
		move_player(game, 1, 0);
	return (0);
}
