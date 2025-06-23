/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjusta <mjusta@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 00:56:33 by mjusta            #+#    #+#             */
/*   Updated: 2025/06/23 02:52:43 by mjusta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//validate the file exists.
void	init_game(t_game *game, const char *filename)
{
	ft_bzero(game, sizeof(t_game));
	game->map.grid = read_map(filename);
	if (!game->map.grid)
		exit_with_error(game, "Failed to read the map!");
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
	exit(0);
}

int	close_game(t_game *game)
{
	exit_game(game);
	return (0);
}

void	exit_with_error(t_game *game, char *message)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit_game(game);
}
