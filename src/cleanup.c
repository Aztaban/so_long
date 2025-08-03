/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 23:39:07 by mjusta            #+#    #+#             */
/*   Updated: 2025/08/04 00:51:43 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// Frees all frames in a sprite's animation set using MLX.
static void	free_sprite(t_game *game, t_sprite *sprite)
{
	int	i;

	i = 0;
	while (i < FRAME_COUNT)
	{
		if (sprite->frame[i])
			mlx_destroy_image(game->mlx_display, sprite->frame[i]);
		i++;
	}
}

// Frees all game textures including floor, walls, sprites, and exit variants.
static void	free_textures(t_game *game)
{
	free_sprite(game, &game->textures.player);
	free_sprite(game, &game->textures.collectible);
	free_sprite(game, &game->textures.enemy);
	if (game->textures.wall)
		mlx_destroy_image(game->mlx_display, game->textures.wall);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx_display, game->textures.floor);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx_display, game->textures.exit);
	if (game->textures.exit_open)
		mlx_destroy_image(game->mlx_display, game->textures.exit_open);
	if (game->img.img)
		mlx_destroy_image(game->mlx_display, game->img.img);
}

// Frees all allocated resources and exits the game cleanly.
void	exit_game(t_game *game)
{
	free_textures(game);
	if (game->win)
		mlx_destroy_window(game->mlx_display, game->win);
	if (game->mlx_display)
	{
		mlx_destroy_display(game->mlx_display);
		free(game->mlx_display);
	}
	if (game->map.grid)
		free_map(game->map.grid);
	exit(EXIT_SUCCESS);
}

// Hook-compatible wrapper to trigger clean exit on window close event.
int	close_game(t_game *game)
{
	exit_game(game);
	return (EXIT_SUCCESS);
}

// Displays an error message and exits the game cleanly if game pointer exists.
// If no game pointer, exits with failure.
void	exit_with_error(t_game *game, char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message)
	{
		ft_putstr_fd(message, STDERR_FILENO);
		if (errno)
		{
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
		}
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (game)
		exit_game(game);
	else
		exit(EXIT_FAILURE);
}
