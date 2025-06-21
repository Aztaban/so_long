/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:31:21 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/21 23:57:34 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_textures(t_game *game)
{
	int	width;
	int	height;

	game->textures.wall = mlx_xpm_file_to_image(game->mlx_display,
			"textures/bush96.xpm", &width, &height);
	game->textures.floor = mlx_xpm_file_to_image(game->mlx_display,
			"textures/floor96.xpm", &width, &height);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx_display,
			"textures/collectible96.xpm", &width, &height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx_display,
			"textures/exit96.xpm", &width, &height);
	game->textures.player = mlx_xpm_file_to_image(game->mlx_display,
			"textures/player96.xpm", &width, &height);
	if (!game->textures.wall || !game->textures.floor
		|| !game->textures.collectible || !game->textures.exit
		|| !game->textures.player)
		exit_with_error(game, "Failed to load textures.");
}

void	init_graphics(t_game *game)
{
	int	scr_w;
	int	scr_h;

	scr_w = game->map.width * TILE_SIZE;
	scr_h = game->map.height * TILE_SIZE;
	game->mlx_display = mlx_init();
	if (!game->mlx_display)
		exit_with_error(game, "MLX failed to initalize");
	game->win = mlx_new_window(game->mlx_display, scr_w, scr_h, "So Long");
	if (!game->win)
		exit_with_error(game, "MLX failed to create window");
	game->img.img = mlx_new_image(game->mlx_display, scr_w, scr_h);
	if (!game->img.img)
		exit_with_error(game, "MLX failed to create image");
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		exit_with_error(game, "MLX failed to get image data address");
	load_textures(game);
}

