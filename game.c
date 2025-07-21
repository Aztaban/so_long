/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:33 by mjusta            #+#    #+#             */
/*   Updated: 2025/07/21 02:10:01 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_ber_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len > 4)
		return (ft_strncmp(filename + len - 4, ".ber", 4) == 0);
	return (0);
}

void	init_game(t_game *game, const char *filename)
{
	if (!is_ber_file(filename))
		exit_with_error(NULL, "Map is not .ber file");
	ft_bzero(game, sizeof(t_game));
	game->map.grid = read_map(filename);
	if (!game->map.grid)
		exit_with_error(game, "Map file could not be open or read");
	validate_map(game);
	init_graphics(game);
	draw_map(game);
}

void	exit_game(t_game *game)
{
	if (game->textures.wall)
		mlx_destroy_image(game->mlx_display, game->textures.wall);
	if (game->textures.floor)
		mlx_destroy_image(game->mlx_display, game->textures.floor);
	if (game->textures.collectible)
		mlx_destroy_image(game->mlx_display, game->textures.collectible);
	if (game->textures.exit)
		mlx_destroy_image(game->mlx_display, game->textures.exit);
	// TODO make function to load sprite textures for player, collectible and enemy later.
	if (game->textures.player)
		mlx_destroy_image(game->mlx_display, game->textures.player);
	if (game->img.img)
		mlx_destroy_image(game->mlx_display, game->img.img);
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

int	close_game(t_game *game)
{
	exit_game(game);
	return (EXIT_SUCCESS);
}

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
