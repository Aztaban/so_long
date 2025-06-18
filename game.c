/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:33 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/19 00:29:26 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_game(t_game *game, const char *filename)
{
	ft_bzero(game, sizeof(t_game));
	game->map.grid = read_map(filename);
	if (!game->map.grid)
		exit_with_error(game, "Failed to read the map!");
	game->mlx_display = mlx_init();
	if (!game->mlx_display)
		exit_with_error(game, "MLX failed to initalize");
	game->win = mlx_new_window(game->mlx_display, WIDTH, HEIGHT, "Hello 42");
	if (!game->win)
		exit_with_error(game, "MLX failed to create window");
	game->img.img = mlx_new_image(game->mlx_display, WIDTH, HEIGHT);
	if (!game->img.img)
		exit_with_error(game, "MLX failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		exit_with_error(game, "MLX failed to get image data address");
}

void	exit_game(t_game *game)
{
	if (game->img.img)
		mlx_destroy_image(game->mlx_display, game->img.img);
	if (game->win)
		mlx_destroy_window(game->mlx_display, game->win);
	if (game->mlx_display)
	{
		mlx_destroy_display(game->mlx_display);
		free(game->mlx_display);
	}
	if(game->map.grid)
		free_map(game->map.grid);
	exit(0);
}

int	close_game(t_game *game)
{
	exit_game(game);
	return (0);
}