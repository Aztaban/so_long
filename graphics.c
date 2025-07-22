/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 21:31:21 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/22 01:32:06 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_sprite(t_game *game, t_sprite *sprite, const char *base)
{
	int		w;
	int		h;
	char	*path;

	path = ft_strjoin(base, "/up.xpm");
	sprite->frame[SPR_UP] = mlx_xpm_file_to_image(game->mlx_display,
			path, &w, &h);
	free(path);
	path = ft_strjoin(base, "/down.xpm");
	sprite->frame[SPR_DOWN] = mlx_xpm_file_to_image(game->mlx_display,
			path, &w, &h);
	free(path);
	path = ft_strjoin(base, "/left.xpm");
	sprite->frame[SPR_LEFT] = mlx_xpm_file_to_image(game->mlx_display,
			path, &w, &h);
	free(path);
	path = ft_strjoin(base, "/right.xpm");
	sprite->frame[SPR_RIGHT] = mlx_xpm_file_to_image(game->mlx_display,
			path, &w, &h);
	free(path);
	if (!sprite->frame[SPR_UP] || !sprite->frame[SPR_DOWN]
		|| !sprite->frame[SPR_LEFT] || !sprite->frame[SPR_RIGHT])
		exit_with_error(game, "Failed to load sprites.");
}

static void	load_textures(t_game *game)
{
	int	width;
	int	height;

	load_sprite(game, &game->textures.player, "textures/sprites/player");
	load_sprite(game, &game->textures.collectible,
		"textures/sprites/collectible");
	game->textures.wall = mlx_xpm_file_to_image(game->mlx_display,
			"textures/bush.xpm", &width, &height);
	game->textures.floor = mlx_xpm_file_to_image(game->mlx_display,
			"textures/floor.xpm", &width, &height);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx_display,
			"textures/exit.xpm", &width, &height);
	game->textures.exit_open = mlx_xpm_file_to_image(game->mlx_display,
			"textures/exit_opened.xpm", &width, &height);
	if (!game->textures.wall || !game->textures.floor
		|| !game->textures.exit || !game->textures.exit_open)
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
