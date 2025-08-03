/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:58:01 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 00:32:12 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Entry point of the program. Validates arguments.
// Initializes the game, sets up hooks, and starts the main loop.
int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (ft_printf("Usage: %s map.ber\n", argv[0]));
	init_game(&game, argv[1]);
	mlx_key_hook(game.win, handle_keypress, &game);
	mlx_hook(game.win, 17, 0, close_game, &game);
	mlx_loop_hook(game.mlx_display, game_loop, &game);
	mlx_loop(game.mlx_display);
	return (0);
}
