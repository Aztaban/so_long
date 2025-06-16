/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:33 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/16 01:21:47 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_game(t_game *game)
{
	mlx_destroy_image(game->mlx_display, game->img.img);
	mlx_destroy_window(game->mlx_display, game->win);
	mlx_destroy_display(game->mlx_display);
	exit(0);
}

int	close_game(t_game *game)
{
	exit_game(game);
	return (0);
}

void	init_game(t_game *game, const char *filename)
{
	(void)filename;
	game->mlx_display = mlx_init();
	game->win = mlx_new_window(game->mlx_display, WIDTH, HEIGHT, "Hello 42");
	game->img.img = mlx_new_image(game->mlx_display, WIDTH, HEIGHT);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
}
